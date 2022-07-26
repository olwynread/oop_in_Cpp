// Code submission for assignment 1 of PHYS30762
// The following computes the energy of a photon released when an electron falls from one energy level to another, as well 
// as the energy of the level it ends up in. It requires an input of the atomic number of the atom containing the electron,
// its initial quantum number and final quantum number. 
// Olwyn Read 18/02/2021
#include<iostream>
#include<iomanip>
#include<string>
#include<cmath>
double energy_of_level(int Z,int n) // Finds the energy of a level given atomic number, Z, and quantum number, n
{
    double energy; energy = 13.6*pow(Z,2)*(1/pow(n,2));
    return energy;
}
bool repeat_func() // Asks if the user wishes to run another calculation
{    
    char answer{0};
    while(answer != 'y' && answer != 'n'){
        std::cout<<"Repeat y/n? ";
        std::cin>>answer;
    }
    if(answer == 'y'){
        std::cout<<"repeat"<<std::endl;
        return true;                
    }else{
        std::cout<<"stop"<<std::endl;
        return false;
    }
}
int main()
{
    while(true){
        int atomic_number, quantum_number_initial{0}, quantum_number_final{0};
        std::cout<<"Enter the atomic number, Z: ";    
        std::cin>>atomic_number;
        while(std::cin.fail()){    
            std::cin.clear();
            std::cin.ignore();       
            std::cout<<"Please enter an integer value for Z: ";            
            std::cin>>atomic_number;
        }
        while(quantum_number_initial <= quantum_number_final){
            std::cout<<"Enter the initial quantum number: ";    
            std::cin>>quantum_number_initial;
            while(std::cin.fail()){    
                std::cin.clear();
                std::cin.ignore();       
                std::cout<<"Please enter an integer value: ";            
                std::cin>>quantum_number_initial;
            }
            std::cout<<"Enter the final quantum number: ";
            std::cin>>quantum_number_final;
            while(std::cin.fail()){    
                std::cin.clear();
                std::cin.ignore();       
                std::cout<<"Please enter an integer value: ";            
                std::cin>>quantum_number_final;
            }
            if(quantum_number_initial <= quantum_number_final){ // Electron must drop down energy levels so an error is printed if this is not the case
                std::cout<<"error n_in<=n_fin"<<std::endl;
            }
        }
        char unit{0};
        while(unit != 'J' && unit != 'e'){ // Input for desired unit, repeats until J or e is entered
            std::cout<<"Which unit would you like the energy in, J or e? ";
            std::cin>>unit;
        }
        std::string output_unit("eV");
        double energy_ev, energy_j, output_energy, energy_level;
        const double ev_to_joule{1.602e-19};
        energy_ev = energy_of_level(atomic_number, quantum_number_final) 
                    -energy_of_level(atomic_number, quantum_number_initial); // Finds the energy of the released photn by finding the difference between the initial and final levels of the electron
        energy_level = energy_of_level(atomic_number, quantum_number_final);
        output_energy = energy_ev;
        
        if(unit == 'J'){ // Converts the units from eV to Joules if required
            energy_j = energy_ev*ev_to_joule;
            energy_level = energy_level*ev_to_joule;
            output_energy = energy_j;
            output_unit = "J";
        }
    
        std::cout<<std::setprecision(3)<<output_energy<<" "<<output_unit<<std::endl; // Output of the photon energy in the requested unit
        std::cout<<"The electron is now in an energy level with energy "<<std::setprecision(3)<<energy_level<<" "<<output_unit<<std::endl; // OUtput of the final energy level in the requested unit

        bool repeat; 
        repeat = repeat_func();
        if(repeat == false){ // If the user doesn't wish to repeat the while loop breaks here
            break;
        }                     
    }    
    return 0;    
}