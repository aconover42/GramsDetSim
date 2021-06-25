#include <cmath>       /* log */
#include <iostream>
#include <fstream>    /* read in data */
#include <algorithm>  
#include <string>
#include <iomanip>
#include <sstream>

float recombination (float E, float F, float rho)
//Takes input of change in ionized energy (E), electric field (F), and argon density (rho)
{
  float value;
  float numer;
  float total;
  //The following calculations are based off of the modified box model used in the ICARUS experiment, with constant values taken from the brookhaven page on liquid argon TPCs
  value = (0.930 + (0.212/(F * rho))*(E));
  numer = log(value);
  total = numer / (0.212 / ( F * rho));
  //returns the amount of ionized energy that survived recombination
  return total;
}


//Main GramsDetSim

int main () {
//This version of the program will require the user to externally save and prepare the output from Grams G4 Sim. Future versions will imbed this functionality.
//Grams G4 Sim ntuple output must be saved as GramsG4Data.txt
   
  std::ifstream testFile("GramsG4Data.txt");    
  std::string line;

  while(getline(testFile, line)){

      float posa;
      float posb;
      float posc;
      float posd;
      float pose;
      float posf;
      float posg;
      float posh;
      float posi;
      float posj;
      float posk;
      float posl;

      std::replace(line.begin(), line.end(), '*', ' ');

      std::stringstream ss(line);

      ss >> posa;
      ss >> posb;
      ss >> posc;
      ss >> posd;
      ss >> pose;
      ss >> posf;
      ss >> posg;
      ss >> posh;
      ss >> posi;
      ss >> posj;
      ss >> posk;
      ss >> posl;

      std::cout << "posa: "  << posa << " ";
      std::cout << "posb: "  << posb << " ";
      std::cout << "posc: "  << posc << " ";
      std::cout << "posd: "  << posd << " ";
      std::cout << "pose: "  << pose << " ";
      std::cout << "posf: "  << posf << " ";
      std::cout << "posg: "  << posg << " ";
      std::cout << "posh: "  << posh << " ";
      std::cout << "posi: "  << posi << " ";
      std::cout << "posj: "  << posj << " ";
      std::cout << "posk: "  << posk << " ";
      std::cout << "posl: "  << posl << " ";

      std::cout << '\n';
  }   
}
//END
