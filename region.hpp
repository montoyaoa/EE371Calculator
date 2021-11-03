#pragma once
#include <complex> 

class Region {
   public:
      Region();
      ~Region();

      //inputs
      int id;
      double dielectric_constant;
      double magnetic_permeability;
      double conductivity;
      double width;

      //outputs
      double reflection_coeffecient;
      double e_field_pos_amplitude;
      double e_field_neg_amplitude;
      double time_avg_power_density;

   private:
      double char_impedance;
      std::complex<double> prop_constant;
};
