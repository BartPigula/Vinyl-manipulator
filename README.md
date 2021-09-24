# Vinyl-manipulator
Engineering thesis on construction of manipulator for vinyl disk flipping.  
Aim of the project is construction of 4 DOF manipulator. It should catch vinyl disk after 1 side had been played, rotate the disk and then put it back on it's desired position. The manipulator has 4 rotating links. At first, simple kinematics is used to program path in small steps so servomotors don't break due to too big torque. As the path is set, list of angles is being read to arduino from txt file from sd card.
In the future the man may consider adding reversed kinematics.
