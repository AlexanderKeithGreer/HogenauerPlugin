# HogenauerPlugin
C++ implementation of a Hogenauer Cascaded Integrator-Comb Filter.

The purpose of this project is 
1) To let me familiarise myself with C++/DSP better
2) To give myself my own code to use for my own simulations

I've tested it to reasonable satisfaction, and it should work properly, although I would like to add more features in future, esp wrt convolving at much higher sampling frequencies.

Individuals who have stumbled across this project is search of similar code are kindly referred to the LiquidSDR library

I would like to leave a reminder here to myself that single stage CIC interpolation is just sample-and-hold, and that no passband distortion will be observed for an up-down operation with no further changes.
