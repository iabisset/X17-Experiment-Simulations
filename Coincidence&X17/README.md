This folder contains the simulation code and post-processing code for the X17 and coincidence simulation. The x17events and RoseIPCEvents notebooks generate angles
and energy divisions for boson decays and pair creation events and store the data in text files to be imported by the geant4 code. The graphing notebook takes
simulation results and graphs angular distributions. The epcFraction notebook calculates what fraction of detections are from external pair creation. This directory also contains an image showing a comparison between angular distribution with X17 decays (blue) and without (yellow).

Note that the graphing notebook needs a text file from a run with X17 decays enabled (hits) and a run with them disabled (hitswithout) for comparison.
