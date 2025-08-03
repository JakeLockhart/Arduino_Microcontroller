# Arduino Microcontroller
Source code for Arduino Microcontroller projects for the Drew Lab. VSCode - PlatformIO Extension.

## ETL and EOM Controller
- **ETLController_SG**: Control the imaging plane of the electric tuneable lens based on a TTL pulse. Created by S. Garborg.
- **ETLandEOM_Controller**: Control both the electric tuneable lens and electric optic modulator via an Arduino Giga to modulate laser intensity & imaging depth simulataneously. Corrects for hardware limitations present with Arduino Due/Uno. Current script controlling R2P in the Drew Lab. Validation in progress.
- **MScanSignalSimulation**: Simulate the output signals created by the R2P (AO0 and PFI12/P2.4 BNC connections throug National Instrument PCI boards). 