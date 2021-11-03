#include "region.hpp"

using namespace std;

//Region constructor
Region::Region(int newId, 
      double newDielectricConstant, 
      double newMagneticPermeability, 
      double newConductivity, 
      double newWidth){
   id = newId;
   dielectric_constant = newDielectricConstant;
   magnetic_permeability = newMagneticPermeability;
   conductivity = newConductivity;
   width = newWidth;

   //calculate the characteristic impedance at object creation
   //calculate propagation constant at object creation
}
