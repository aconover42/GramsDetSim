//Function
#include <cmath>       /* log */
#include <iostream>

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
//a quick program to test our calculation
{
  float z;
  z = recombination (1, 1, 1);
  std::cout << "The result is " << z;
}
//END
