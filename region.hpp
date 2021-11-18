#pragma once
#include <complex> 
#include <iostream>

#define PI 3.141592654 
#define PERMEABILITY_OF_FREE_SPACE (PI * 4E-7)
#define PERMITIVITY_OF_FREE_SPACE  8.854E-12
#define SPEED_OF_LIGHT 3E8

class Region {
   public:
      Region(int, double, double, double, double, double);
      ~Region();

      //inputs: properties of the medium
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
      std::complex<double> time_avg_power_density;

      //methods
      void displayProperties();
      void displayResults();
      void calculateReflectionCoeffecientAtOrigin();
      void calculateReflectionCoeffecientAtDepth();
      void calculateTotalImpedanceAtDepth();
      void calculateTransmittedElectricField(std::complex<double>, std::complex<double>);
      void calculateReflectedElectricField();
      void calculateTotalElectricFieldAtOrigin();
      void calculateTimeAveragePowerDensity();

   //used internally only
      double cond_displace_ratio;
      double permitivity;
      double permeability;
      double angular_frequency;

      std::complex<double> char_impedance;
      std::complex<double> prop_constant;

      std::complex<double> totalImpedanceAtOrigin;
      std::complex<double> totalImpedanceAtDepth;
      
      std::complex<double> reflectionCoeffecientAtOrigin;
      std::complex<double> reflectionCoeffecientAtDepth;

      std::complex<double> transmittedElectricField;
      std::complex<double> reflectedElectricField;

      std::complex<double> totalElectricFieldAtOrigin;
      std::complex<double> totalElectricFieldAtDepth;

};
