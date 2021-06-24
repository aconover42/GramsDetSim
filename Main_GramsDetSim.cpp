#include <cmath>       /* log */
#include <iostream>
#include <fstream>    /* read in data */

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



int main ()
//Main GramsDetSim
{
//This version of the program will require the user to externally save and prepare the output from Grams G4 Sim. Future versions will imbed this functionality.
//Grams G4 Sim ntuple output must be saved as GramsG4Data.txt
  std::ofstream data;
  data.open ("GramsG4Data.txt");
  std::cout << data;
  data.close();
  return data;
}
//END
