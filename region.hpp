#pragma once
#include <complex> 
#include <iostream>

#define PI 3.14159 
#define PERMEABILITY_OF_FREE_SPACE 8.854E-12
#define PERMITIVITY_OF_FREE_SPACE (PI*4E-7)

class Region {
   public:
      Region(int, double, double, double, double, double);
      ~Region();

      //inputs
      int id;
      double dielectric_constant;
      double magnetic_permeability;
      double conductivity;
      double width;

      double frequency;

      //outputs
      double reflection_coeffecient;
      double e_field_pos_amplitude;
      double e_field_neg_amplitude;
      double time_avg_power_density;

      //methods
      void displayProperties();

   //used internally only
   private:
      double permitivity;
      double permeability;
      double angular_frequency;
      std::complex<double> char_impedance;
      std::complex<double> prop_constant;
};
