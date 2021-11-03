# EE371Calculator
A calculator that determines how an electric field reflects and transmits over multiple interfaces.

Accepts the following inputs:
* Electric Field
  * Amplitude
  * Frequency
* Number of Regions
* For each region:
  * Dielectric constant  	&#1013;<sub>r</sub>
  * Magnetic Permeability &mu;<sub>r</sub>
  * Conductivity &sigma;
  * Width

Determines the following outputs:
* The reflection coeffecient 	&Gamma;&#770; for region 1
* The difference between the reflection coeffecient for region 1 and the reflection coeffecient for region 1 **taking into consideration only regions 1 and 2**
* For each region:
  * Amplitude of electric field in the +z direction E<sup>+</sup>
  * Amplitude of electric field in the -z direction E<sup>-</sup>
  * Time-Average Power Density
