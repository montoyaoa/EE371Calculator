#include <list>

#include "region.hpp"


using namespace std;

int main() {
   list<Region*> regionList;
   list<Region*> regionListAdjusted;

   int numberOfRegions = 0;

   cout << "Enter number of regions (minimum of 3): ";
   cin >> numberOfRegions;
   
   while(numberOfRegions < 3){
      cout  << "Please enter a minimum of 3 regions." << endl;
      cout  << "Enter number of regions (minimum of 3): ";
      cin   >> numberOfRegions;
   }

   double newEFieldAmplitude  = 0.0;
   double newFrequency        = 0.0;

   cout  << endl;
   cout  << "For the plane wave:" << endl;
   cout  << "Enter Electric Field amplitude (V/m): ";
   cin   >> newEFieldAmplitude;
   cout  << "Enter Frequency (Hz): ";
   cin   >> newFrequency;
   cout  << endl;

   for(int i = 1; i <= numberOfRegions; i++){
      double newDielectricConstant     = 0.0;
      double newMagneticPermeability   = 0.0;
      double newConductivity           = 0.0;
      double newWidth                  = 0.0;

      cout  << "For Region " << i << ": " << endl;
      cout  << "Enter Dielectric Constant: ";
      cin   >> newDielectricConstant;
      cout  << "Enter Magnetic Permeability: ";
      cin   >> newMagneticPermeability;
      cout  << "Enter Conductivity: ";
      cin   >> newConductivity;
      cout  << "Enter Width (as a function of wavelength): ";
      cin   >> newWidth;

      Region * newRegion = new Region(i, newDielectricConstant, newMagneticPermeability, newConductivity, newWidth, newFrequency);
      regionList.push_back(newRegion);

      if(i == 1 || i == 2){
         regionListAdjusted.push_back(newRegion);
      }

      cout  << endl;
   }

   regionList.front()->width = 0;
   regionList.back()->width = 0;


  regionList.back()->totalImpedanceAtOrigin = regionList.back()->char_impedance;
  regionList.back()->totalImpedanceAtDepth = regionList.back()->totalImpedanceAtOrigin;
  
  for(auto currentRegion = regionList.rbegin(); currentRegion != regionList.rend(); ++currentRegion){
     auto previousRegion = prev(currentRegion, 1);
     
     if(currentRegion != regionList.rbegin()){
        (*currentRegion)->totalImpedanceAtOrigin = (*previousRegion)->totalImpedanceAtDepth;
        (*currentRegion)->calculateReflectionCoeffecientAtOrigin();
        (*currentRegion)->calculateReflectionCoeffecientAtDepth();
        (*currentRegion)->calculateTotalImpedanceAtDepth();
     }
  }

   regionList.front()->transmittedElectricField = complex<double>(newEFieldAmplitude, 0);
   regionList.front()->reflectedElectricField = regionList.front()->transmittedElectricField * regionList.front()->reflectionCoeffecientAtOrigin;
   regionList.front()->totalElectricFieldAtOrigin = regionList.front()->transmittedElectricField * (complex<double>(1, 0) + regionList.front()->reflectionCoeffecientAtOrigin);
   regionList.front()->calculateTimeAveragePowerDensity();

  for(auto currentRegion = regionList.begin(); currentRegion != regionList.end(); ++currentRegion){
     auto previousRegion = prev(currentRegion, 1);

     if(currentRegion != regionList.begin()){
        (*currentRegion)->totalElectricFieldAtDepth = (*previousRegion)->totalElectricFieldAtOrigin;
        (*currentRegion)->calculateTransmittedElectricField((*previousRegion)->transmittedElectricField, (*previousRegion)->reflectionCoeffecientAtOrigin);
        (*currentRegion)->calculateReflectedElectricField();
        (*currentRegion)->calculateTotalElectricFieldAtOrigin();
        (*currentRegion)->calculateTimeAveragePowerDensity();
     }
  }

   for(Region* region : regionList){
      region->displayProperties();
   }

   for(Region* region : regionList){
      region->displayResults();
   }

   //prompt the user for input

//assign input data to variables inside new objects (use a factory)

//calculate results

//display results

}
