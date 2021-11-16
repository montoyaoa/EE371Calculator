#include "region.hpp"

using namespace std;

//Region constructor
Region::Region(int newId, double newDielectricConstant, double newMagneticPermeability, double newConductivity, double newWidth, double newFrequency){
   id = newId;
   dielectric_constant = newDielectricConstant;
   magnetic_permeability = newMagneticPermeability;
   conductivity = newConductivity;
   //width = newWidth;
   frequency = newFrequency;

   width = (newWidth) * (SPEED_OF_LIGHT/(frequency * sqrt(dielectric_constant)));

   //define the internal values that we'll need later
   angular_frequency = 2*PI*frequency;
   permitivity = dielectric_constant*PERMITIVITY_OF_FREE_SPACE;
   permeability = magnetic_permeability*PERMEABILITY_OF_FREE_SPACE;
   cond_displace_ratio = (conductivity)/(angular_frequency*permitivity);
   //theta is the angle between the electric and magnetic fields. we only need to use it here
   complex<double> theta = (0, (1/2)*atan(cond_displace_ratio));
   double alpha = ((angular_frequency*sqrt(permitivity*permeability))/sqrt(2))*(sqrt(sqrt(1 + pow(cond_displace_ratio, 2)) - 1));
   double beta = ((angular_frequency*sqrt(permitivity*permeability))/sqrt(2))*(sqrt(sqrt(1 + pow(cond_displace_ratio, 2)) + 1));

   //assemble propagation constant y = a+jb
   prop_constant = complex<double>(alpha, beta);

   //calculate the characteristic impedance at object creation
   //char_impedance = ((sqrt(permeability/permitivity))/(sqrt(sqrt(1 + pow(cond_displace_ratio , 2)))))*exp(theta);
   char_impedance = sqrt(permeability / (permitivity - complex<double>(0, (conductivity / angular_frequency))));
}

void Region::displayProperties(){
   cout << "Region " << id << " properties " << endl;
   cout << "---------------------------------------" << endl;
   cout << "dielectric constant: " << dielectric_constant << endl;
   cout << "magnetic permeability: " << magnetic_permeability << endl;
   cout << "conductivity: " << conductivity << endl;
   cout << "width: " << width << endl;
   cout << endl;
   cout << "angular frequency: " << angular_frequency << endl;
   cout << "permitvity: " << permitivity << endl;
   cout << "permeability: " << permeability << endl;
   cout << "characteristic impedance: " << char_impedance << endl;
   cout << "propagation constant: " << prop_constant << endl;
   cout << "total impedance at origin: " << totalImpedanceAtOrigin << endl;
   cout << "total impedance at depth: " << totalImpedanceAtDepth << endl;
   cout << "reflection coeffecient at origin: " << reflectionCoeffecientAtOrigin << endl;
   cout << "reflection coeffecient at depth: " << reflectionCoeffecientAtDepth << endl;
   cout << "---------------------------------------" << endl;
   cout << endl;
}

void Region::calculateReflectionCoeffecientAtOrigin(){
   reflectionCoeffecientAtOrigin = (totalImpedanceAtOrigin - char_impedance) / (totalImpedanceAtOrigin + char_impedance);
}

//this is correct
void Region::calculateReflectionCoeffecientAtDepth(){
   complex<double> complexWidth(width, 0);
   complex<double> complexExpFactor(-2, 0);

   reflectionCoeffecientAtDepth = (reflectionCoeffecientAtOrigin) * (exp(prop_constant * complexExpFactor * complexWidth));
}

void Region::calculateTotalImpedanceAtDepth(){
   complex<double> complexOne(1, 0);

   totalImpedanceAtDepth = (char_impedance) * ((complexOne + reflectionCoeffecientAtOrigin)/(complexOne - reflectionCoeffecientAtOrigin));

}

