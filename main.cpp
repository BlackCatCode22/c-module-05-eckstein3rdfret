#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

//Forward declarations of existing species
class bear;
class hyena;
class lion;
class tiger;

//Function prototypes, all might not be used
void file_reading_func();
void file_output_func(const map<string, int>&, const vector<class Animal> &);

//global map to store animal counts
//stores {{"hyena",0},{"bear",0},{"lion",0},{"tiger",0}}
map<string, int> Animals;

class Animal {
public:
    map<string, string>Animal_transport;

    Animal(const string &name, const string &age, const string &Season_born, const string &color, const string &sex, const string &species, const string &weight, const string &origin) {
        Animal_transport["name"] = name;
        Animal_transport["age"] = age;
        Animal_transport["season"] = Season_born;
        Animal_transport["color"] = color;
        Animal_transport["sex"] = sex;
        Animal_transport["species"] = species;
        Animal_transport["weight"] = weight;
        Animal_transport["origin"] = origin;
        updateAnimalCount();
        genUniqueID();
    }
    void updateAnimalCount(){
        if (!Animals.contains(Animal_transport["species"])) {
            Animals[Animal_transport["species"]] = 1;
        }
        else
            Animals[Animal_transport["species"]]++;
    }
    void genUniqueID() {
        if (Animals[Animal_transport["species"]] <= 9)
            Animal_transport["ID"] =string(1, toupper(Animal_transport["species"][0])) + string(1, Animal_transport["species"][1]) + "0" + to_string(Animals[Animal_transport["species"]]);
        else
            Animal_transport["ID"] =string(1, toupper(Animal_transport["species"][0])) + string(1, Animal_transport["species"][1]) + to_string(Animals[Animal_transport["species"]]);
    }
};

//I don't like the idea of coding out each subclass for the animal, maybe I can find a workaround eventually
class bear: public Animal {
    public:
        using Animal::Animal;
        static map<string, Animal*> bear_habitat;

        map<string,Animal*> getbear_habitat() const {
            return bear_habitat;
        }
};
map<string, Animal*> bear::bear_habitat;

class hyena: public Animal {
    public:
        using Animal::Animal;
        static map<string, Animal*> hyena_habitat;

        map<string,Animal*> gethyena_habitat() {
        return hyena_habitat;
    }
};
map<string, Animal*> hyena::hyena_habitat;

class lion: public Animal {
    public:
        using Animal::Animal;
        static map<string, Animal*> lion_habitat;
    map<string, Animal*> getlion_habitat() {
        return lion_habitat;
    }
};
map<string, Animal*> lion::lion_habitat;

class tiger: public Animal {
    public:
        using Animal::Animal;
    static map<string, Animal*> tiger_habitat;
    map<string,Animal*> gettiger_habitat() {
        return tiger_habitat;
    }
};
map<string, Animal*> tiger::tiger_habitat;

int main() {

    //The Goal of the reading function is the following:
    //Read arrivingAnimals.txt line by line, Create a new Animal object, store object in Zoo_Animals Vector...
    //Then update Map of Animal counts
    file_reading_func();

    //The Goal of the output function is the following:
    //Take Map of Animal Counts and Zoo_Animals Vector as input
    //Use Map to dictate which Species to search in Zoo_Animals Vector, Print Animal count
    //When Correct Species is found, Print new line using object methods to call object data

    //file_output_func(Animals, Zoo_Animals);

    return 0;
}

void file_reading_func() {
    //TODO
    fstream myFile;
    //Below opens a file to READ from it
    myFile.open("C:/Users/eckst/Desktop/arrivingAnimals.txt", ios::in);//read mode

    //need to check if the file opened successfully
    if (myFile.is_open()) {
        string line_of_txt;
        string no_punct;
        vector<string> parse_by_comma;
        //getline(A,B) reads a line of data from A and stores it in variable B

        //For every line in file
        while (getline(myFile,line_of_txt)) {
            parse_by_comma.clear();
            cout << line_of_txt << '\n';
            stringstream line(line_of_txt);

            //for this line
            while (getline(line, no_punct, ',')) {

                //for every comma section, if there is a space at start, erase
                if (no_punct[0] == ' ') {
                    no_punct.erase(0, 1);
                }

                //add section to vector without space at start
                parse_by_comma.push_back(no_punct);
            }

            //declare variables with known indexes for line
            string Animal_Age(1, parse_by_comma[0][0]);
            string Season_born;
            string color = parse_by_comma[2];
            string weight = parse_by_comma[3];
            string name = "dummy name" ; //generate from file io and custom function
            string origin = parse_by_comma[4] + ", " + parse_by_comma[5];
            string sex;
            string species;

            //for each comma separated section
            for (string i : parse_by_comma) {
                stringstream ss(i);
                string word;
                while (ss >> word) {
                    if (word == "spring" || word == "summer" || word == "fall" || word == "winter") {
                        Season_born = word;
                    }
                    if ( word == "season") {
                        Season_born = "unknown";
                    }
                    if (word == "lion" || word == "hyena" || word == "tiger" || word == "bear") {
                        species = word;
                    }
                    if (word == "male" || word == "female") {
                        sex = word;
                    }
                }
            }
            Animal AnimalObj(name, Animal_Age, Season_born, color, sex, species, weight, origin);

            //Once the animal object is created then a pointer is saved
            Animal* ptr_AnimalObj = &AnimalObj;
            //store the animal object in the correct habitat with the new name
            if (species == "bear") {
                bear::bear_habitat[name] = ptr_AnimalObj;
            }
            else if (species == "hyena") {
                hyena::hyena_habitat[name] = ptr_AnimalObj;
            }
            else if (species == "lion") {
                lion::lion_habitat[name] = ptr_AnimalObj;
            }
            else
                tiger::tiger_habitat[name] = ptr_AnimalObj;
            //The pointer is then saved into the appropriate subclass "habitat" or map
        }

        //Don't forget to close the file you opened when finished.
        myFile.close();
    }
}

void file_output_func(const map<string, int>& Animals) {
    //TODO
    //This function at some point will need to take into account the age of the animal
    //Once the age is accounted for and the season the animal was born in
    //Arrival will be todays date and birth date will be a random month from the season and age - 2025

    fstream myFile;

    //Below opens a file to APPEND to it
    myFile.open("C:/Users/eckst/Desktop/newAnimals.txt", ios::app);//Appends to the end of existing file content)

    //need to check if the file opened successfully
    if (myFile.is_open()) {
        //This loops through the Animal MAP
        //It prints Animal type and #
        for (const auto&[fst, snd] : Animals) {
            myFile << "Number of " << fst << "s " << "Value: " << snd << "\n";
            myFile << "\n";
        //This will eventually call each "species_habitat" loops through each object
        //Each object's contents will print to file newAnimals.txt
        }
        //close file when done
        myFile.close();
    }
}



