#include <list>

#include "region.hpp"


using namespace std;

int main() {
  // Region* testRegion = new Region(1, 2.0, 3.0, 4.0, 5.0, 6.0);
   //testRegion->displayProperties();


   list<Region*> regionList;

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
      cout  << "Enter Width: ";
      cin   >> newWidth;

      Region * newRegion = new Region(i, newDielectricConstant, newMagneticPermeability, newConductivity, newWidth, newFrequency);
      regionList.push_back(newRegion);
      cout  << endl;
   }


   for(Region* region : regionList){
      region->displayProperties();
   }

   //prompt the user for input

//assign input data to variables inside new objects (use a factory)

//calculate results

//display results

}
