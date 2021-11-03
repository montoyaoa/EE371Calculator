#include "region.hpp"

using namespace std;

//Region constructor
Region::Region(int newId, double newDielectricConstant, double newMagneticPermeability, double newConductivity, double newWidth, double newFrequency){
   id = newId;
   dielectric_constant = newDielectricConstant;
   magnetic_permeability = newMagneticPermeability;
   conductivity = newConductivity;
   width = newWidth;
   frequency = newFrequency;

   //define the internal values that we'll need later
   angular_frequency = 2*PI*frequency;
   permitivity = dielectric_constant*PERMITIVITY_OF_FREE_SPACE;
   permeability = magnetic_permeability*PERMEABILITY_OF_FREE_SPACE;

   prop_constant = complex<double>((((angular_frequency*sqrt(permitivity*permeability))/sqrt(2))*(sqrt(1 + pow((conductivity/angular_frequency*permitivity), 2)) - 1)) , (((angular_frequency*sqrt(permitivity*permeability))/sqrt(2))*(sqrt(1 + pow((conductivity/angular_frequency*permitivity), 2)) + 1)));

   complex<double> theta = (0, (1/2)*atan(conductivity/(angular_frequency*permitivity)));

   char_impedance = ((sqrt(permeability/permitivity))/(sqrt(sqrt(1 + pow((conductivity/(angular_frequency*permitivity)) , 2)))))*exp(theta);
   //calculate the characteristic impedance at object creation
   //calculate propagation constant at object creation
}

void Region::displayProperties(){
   cout << "Region " << id << " properties " << endl;
   cout << "dielectric constant: " << dielectric_constant << endl;
   cout << "magnetic permeability: " << magnetic_permeability << endl;
   cout << "conductivity: " << conductivity << endl;
   cout << "width: " << width << endl;
   cout << endl;
   cout << "electric field properties" << endl;
   cout << "frequency: " << frequency << endl;
   cout << endl;
   cout << "angular frequency: " << angular_frequency << endl;
   cout << "permitvity: " << permitivity << endl;
   cout << "permeability: " << permeability << endl;
   cout << "characteristic impedance: " << char_impedance << endl;
   cout << "propagation constant: " << prop_constant << endl;

}
