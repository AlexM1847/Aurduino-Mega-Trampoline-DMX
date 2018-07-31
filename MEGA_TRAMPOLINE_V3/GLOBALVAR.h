////////////////////////////
//    GLOBAL VARIAABLES   //
////////////////////////////

  // TOTAL NUMBER OF SENSORS
  const int numSensors = 9;

  // START PIN OF SENSORS
  int startPin = 22;
  
  // Holds the  adress of lights in corispondence to trampolines
  int lightAdress[12] = {32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43};

  // VARIABLE TO ACTIVATE SENSORS
  int activator = 0;

  // DISTANCE OF SENSORS IN CM
  float sensorDistance[numSensors];

  // MIN INTENSITY DATA FROM BOARD (ADRESS 2 IN UNIVERSE)
  int minIntensity = 40;

  // MAX INTENSITY DATA FROM BOARD (ADRESS # IN UNIVERSE)
  int maxIntensity = 240;

  // MIN DISTANCE THE TRAMPOLINE GETS TO THE SENSOR
  float minDistance = 40;

  // MAX DISTANCE THE TRAMPOLINE GETS TO THE SENSOR
  float maxDistance = 240;

  // MAX DISTANCE FOR SENSOR OUT OF RANGE
  const unsigned int MAX_DIST = 23200;
  
  // INCOMING DMX DATA WITH STARTCODE
  uint8_t DMXDATA[512];

  // DATA TO SEND OUT TO LIGHTS
  byte lightIntensities[12];    // HOLDS NEW VALUES for lights
  
  // COUNTER
  int counter = 0;

    
