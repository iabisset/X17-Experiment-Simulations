# X17-Experiment-Simulations

This repository contains the simulation code for the UdeM X17 done over the course of my Senior Design project and the summer afterwards. This text document summarizes all the folders contained in this repository, but more information can be found in the individual folders and code comments. Each folder contains a directory for the source code and a directory containing the program compiled from the source code. To run the software, one must have an installation of geant4 on their system with appropriate data libraries for decay physics, gamma levels, etc. If there are any questions, please contact me at iain.bisset1@gmail.com

# Preliminary Simulations

This folder contains some basic simulations done at the beginning of the project to familiarize myself with the basics of generating geometries, setting up particle events, and running the software. I have left this in in case any future individuals who take over the project need familiarizing with Geant. The data from the simulations is sent to a text file which is compiled into a histogram of energy depositions by a mathematica file. If anyone taking over this project is familiar with root or a c++ library for plotting then this could be done more efficiently, but for the sake of saving time learning new software I went with what I knew here. Check out the built in examples included in a standard geant4 installation as well, which are the basis for these simulations.

# Geometry

This folder contains the 
