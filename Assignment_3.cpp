// Code submission for Assignment 3 11/03/2021\
The following prints data for galaxies along with any satellites, then automatically changes the galaxies classification\
and prints out the updated data

#include<cmath>
#include<iostream>
#include<string>
#include<vector>

class galaxy
{
        std::string classification; std::vector<galaxy> satellites; double redshift, tot_mass, stellar_mass_fraction;
    public:
        galaxy() = default; // Default constructor
        galaxy(std::string a, double b, double c, double d):  // Parameterized constructor
        classification{a}, redshift{b}, tot_mass{c}, stellar_mass_fraction{d} {};
        ~galaxy(){} // Destructor

        double stellar_mass(double mass, double fraction) {return (mass * fraction);} // Member function which returns stellar mass
        void change_classification(std::string class_in) {classification = class_in;} // Member function which changes the classification
        void add_satellite(galaxy satellite){satellites.push_back(satellite);} // Adds a satellite to the satellites container
        void print_data(); // Member function defined outside the class
        void if_satellites(); // Member function defined outside the class
};

void galaxy::print_data(){ // Member function of galaxy which prints the data related to a given galaxy and its satellites
    std::cout.precision(3);
    std::cout<<"\nGalaxy classification: "<<classification<<"\nGalaxy redshift: "<<redshift<<"\nTotal mass: "<<tot_mass
    <<"\nStellar mass fraction: "<<stellar_mass_fraction<<"\nStellar mass: "<<stellar_mass(tot_mass, stellar_mass_fraction)
    <<std::endl;
    if(satellites.size()>0){ // Only prints the number of satellites of there are any
        std::cout<<"Number of satellite galaxies: "<<satellites.size()<<std::endl;
    }
}

void galaxy::if_satellites(){ // Member funtion of galaxy which checks if a galaxy has satallites and calls print_data() for the satellites if applicable
    auto satellite_it = satellites.begin();
    while(satellite_it < satellites.end()){
        std::cout<<"\nSatellite data:"<<std::endl;
        satellite_it->print_data();
        satellite_it++;
    }
}

int main()
{
    std::vector<galaxy> galaxies;
    galaxy galaxy1("S0", 5, pow(10, 9), 0.02); // Initializes an object in galaxy
    galaxy satellite1("Irr", 5, pow(10, 7), 0.01); // Initializes a satellite galaxy
    galaxy1.add_satellite(satellite1);

    galaxies.push_back(galaxy()); // Initializes a default object or the galaxy class
    galaxies.push_back(galaxy1);

    std::vector<std::string> classification = {"E0","E1","E2","E3","E4","E5","E6","E7","S0","Sa","Sb","Sc","SBa","SBb","SBc","Irr"};
    int random_class_index; srand((unsigned int)time(NULL)); // Changes the seed for rand() to keep it "random"
    for(auto iterator=galaxies.begin(); iterator < galaxies.end(); iterator++){
        iterator->print_data();
        iterator->if_satellites();
        random_class_index = rand() % (classification.size()); // Selects an random classifiaction index
        std::cout<<"\nChanging classification of galaxy to "<<classification.at(random_class_index)<<std::endl; 
        iterator->change_classification(classification.at(random_class_index)); // Randomises a galaxies classification
        iterator->print_data();
        iterator->if_satellites();
    }
}