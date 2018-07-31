#include "GLOBALVAR.h"
#include "DMXSerialUno.h"
#include "WORKINGFUNCTIONS.h"
#include "setup.h"

void loop() {
  // getDMX();
  readDMXUniverse();
  
  // ACTIVATOR TO TELL THE AURDUINO TO TAKE CONTROL
  if(activator > 200){
   // UPDATES SENSORES FUNCTION
   updateSensoreValues(); // [GOOD]
   // CONVERTS DISTANCE TO INTENSITY
   trampolineDMX(); // [GOOD]
   // ENCODE NEW DMX
   encodeDMX();     // [GOOD]
  }

  // DMX FUNCTION  
  writeDMXUniverse();
  delay(400);
}




