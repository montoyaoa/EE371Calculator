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
   cout << endl;
   cout << "Transmitted electric field: " << transmittedElectricField << endl;
   cout << "Reflected electric field: " << reflectedElectricField << endl;
   cout << "total electric field at origin: " << totalElectricFieldAtOrigin << endl;
   cout << "total electric field at depth: " << totalElectricFieldAtDepth << endl;
   cout << endl;
   cout << "time average power density: " << time_avg_power_density << endl;
   cout << "---------------------------------------" << endl;
   cout << endl;
}

void Region::displayResults(){
   cout << "For Region " << id << endl;
   cout << "---------------------------------------" << endl;
   cout << "Transmitted Electric Field: "; 
   rectangularToPolar(transmittedElectricField);
   cout << " V/m" << endl;
   cout << "Reflected Electric Field: ";
   rectangularToPolar(reflectedElectricField); 
   cout << " V/m " << endl;
   cout << "Time Average Power Density: ";
   rectangularToPolar(time_avg_power_density);
   cout << " W/m^2" <<endl;
   cout << "---------------------------------------" << endl;
   cout << endl;
}

void Region::calculateReflectionCoeffecientAtOrigin(){
   reflectionCoeffecientAtOrigin = (totalImpedanceAtOrigin - char_impedance) / (totalImpedanceAtOrigin + char_impedance);
}

void Region::calculateReflectionCoeffecientAtDepth(){
   complex<double> complexWidth(width, 0);
   complex<double> complexExpFactor(-2, 0);

   reflectionCoeffecientAtDepth = (reflectionCoeffecientAtOrigin) * (exp(prop_constant * complexExpFactor * complexWidth));
}

void Region::calculateTotalImpedanceAtDepth(){
   complex<double> complexOne(1, 0);

   totalImpedanceAtDepth = (char_impedance) * ((complexOne + reflectionCoeffecientAtDepth)/(complexOne - reflectionCoeffecientAtDepth));

}

void Region::calculateTransmittedElectricField(complex<double> previousTransmittedElectricField, complex<double> previousReflectionCoeffecientAtOrigin){
   complex<double> complexOne(1, 0);

   transmittedElectricField = (previousTransmittedElectricField * (complexOne + previousReflectionCoeffecientAtOrigin)) / (exp(prop_constant * width) * (complexOne + reflectionCoeffecientAtDepth));
}

void Region::calculateReflectedElectricField(){
   reflectedElectricField = transmittedElectricField * reflectionCoeffecientAtOrigin;
}

void Region::calculateTotalElectricFieldAtOrigin(){
   complex<double> complexOne(1, 0);
   
   totalElectricFieldAtOrigin = transmittedElectricField * (complexOne + reflectionCoeffecientAtOrigin);
}

void Region::calculateTimeAveragePowerDensity(){

   complex<double> numerator = norm(transmittedElectricField) * (1 - norm(reflectionCoeffecientAtOrigin));
   complex<double> denominator = complex<double>(2, 0) * char_impedance;
   
   time_avg_power_density = numerator / denominator;

}

void Region::rectangularToPolar(complex<double> input){
double magnitude = sqrt(pow(input.real(), 2) + pow(input.imag(), 2));
double angle = 0;

if(input.real() == 0 && input.imag() > 0){
   angle = PI/2;
}
else if(input.real() == 0 && input.imag() < 0){
   angle = -1 * PI / 2;
}
else if(input.real() > 0 && input.imag() == 0){
   angle = 0;
}
else if(input.real() < 0 && input.imag() == 0){
   angle = PI;
}
else if(input.real() > 0){
   angle = atan(input.imag() / input.real());
}
else if(input.real() < 0){
   angle = atan(input.imag() / input.real()) + PI;
}

angle = (angle * 180) / PI;

if(angle > 180){
   angle = angle - 360;
}
//euler's formula
else if(angle == 180){
   angle = 0;
   magnitude = magnitude * -1;
}
else if(angle < -180){
   angle = angle + 180;
}
cout << magnitude << "e^j" << angle << " degrees";
}
