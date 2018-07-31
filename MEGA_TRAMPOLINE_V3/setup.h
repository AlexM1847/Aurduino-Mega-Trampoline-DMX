void initializeSensors();
void setupDMX();

void delayFoo();

void setup() {
   
  //////////////////
  // PWM Pinout   //
  //////////////////

  // Pin 12 MAX 485 CHIP Direction Control
 
  //////////////////////
  // Digital Pinout   //
  //////////////////////

  // Pin 22     Sensor 1 Trigger
  // Pin 23     Sensor 1 Echo
  // Pin 24     Sensor 2 Trigger
  // Pin 25     Sensor 2 Echo
  // Pin 26     Sensor 3 Trigger
  // Pin 27     Sensor 3 Echo
  // Pin 28     Sensor 4 Trigger
  // Pin 29     Sensor 4 Echo
  // Pin 30     Sensor 5 Trigger
  // Pin 31     Sensor 5 Echo
  // Pin 32     Sensor 6 Trigger
  // Pin 33     Sensor 6 Echo
  // Pin 34     Sensor 7 Trigger
  // Pin 35     Sensor 7 Echo
  // Pin 36     Sensor 8 Trigger
  // Pin 37     Sensor 8 Echo
  // Pin 38     Sensor 9 Trigger
  // Pin 39     Sensor 9 Echo
  // Pin 40     Sensor 10 Trigger
  // Pin 41     Sensor 10 Echo
  // Pin 42     Sensor 11 Trigger
  // Pin 43     Sensor 11 Echo
  // Pin 44     Sensor 12 Trigger
  // Pin 45     Sensor 12 Echo

  ///////////////////////////////////////////////////////////
  //    ETHERNET WIRING CONFIG FOR SENSORS ON MAIN UNIT    //
  ///////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////
  //    BANK 1 : TRAMPOLINES 1 - 3 ::  ETHERNET OUTPUT = BLUE     //
  //    BANK 2 : TRAMPOLINES 4 - 6 ::  ETHERNET OUTPUT = GREEN    //
  //    BANK 3 : TRAMPOLINES 7 - 9 ::  ETHERNET OUTPUT = YELLOW   //
  //    BANK 4 : TRAMPOLINES 4 - 6 ::  ETHERNET OUTPUT = ORANGE   //
  //////////////////////////////////////////////////////////////////

  /////////////////////////////////
  //    ETHERNET SENSOR ORDER    //
  /////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////
  //    BULK CABLE (PLUG / SOCKET ) -> BULK CABLE (DIRECT FEED)             //
  //    ^                                                                   //
  //    ^ *THESE WILL HAVE BOOTS ON THEM TO DETERMIN WICH PLUG GOES WHERE*  //
  //                                                                        //
  ////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////
  //    ETHERNET WIRING ORDER    //
  //    USING CAT6e B CONFIG     //
  /////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////
  //    1)  ORANGE W/ STRIPE    ::    ECHO ON FIRST SENSOR IN BANK    [TREMPOLINES 1, 4, 9, 12] //
  //    2)  ORANGE              ::    PING ON FIRST SENSOR IN BANK    [TREMPOLINES 1, 4, 9, 12] //
  //    3)  GREEN W/ STRIPE     ::    ECHO ON SECOND SENSOR IN BANK   [TREMPOLINES 2, 5, 8, 11] //
  //    4)  BLUE                ::    PING ON THIRD SENSOR IN BANK    [TREMPOLINES 2, 5, 8, 11] //
  //    5)  BLUE W/ STRIPE      ::    ECHO ON THIRD SENSOR IN BANK    [TREMPOLINES 3, 6, 7, 10] //
  //    6)  GREEN               ::    PING ON SECOND SENSOR IN BANK   [TREMPOLINES 3, 6, 7, 10] //
  //    7)  BROWN W/ STRIPE     ::    GRND FOR BANK                                             //
  //    8)  BROWN               ::    +5 VOLTS FOR BANK                                         //
  ////////////////////////////////////////////////////////////////////////////////////////////////

  
  /////////////////   Digital Pin Setup .  ///////////
   setupDMX();
   initializeSensors();
}

//////////////////////////////////
//Function to initialize sensors
///////////////////////////////////
void initializeSensors(){

    // Setting Pin mods (TRIGGER FOR SENSORS)
    counter = 0;
    Serial.println("Sensors Initializing...");
    while(counter < numSensors){
        pinMode(startPin + ((counter * 2)), OUTPUT);
        digitalWrite(startPin + ((counter * 2)), LOW);
        counter ++;
    }
   // Setting Pin mods (ECHO FOR SENSORS)
    counter = 0;
    while(counter < numSensors){
        pinMode(startPin + ((counter * 2) + 1), INPUT);
        counter ++;
    }
    counter = 0;    // Cleanup   
    Serial.println("Sensors Initialized.");
 }

//////////////////////////////////
//Function to initialize DMX
///////////////////////////////////
 void setupDMX(){
  // Set up DMX
  DMXSerial.init(DMXController);

  // SET ALL CHANNELS TO 0
  for(size_t i = 1; i <= DMXSERIAL_MAX; ++i){
    DMXDATA[i] = 0;
  }
  DMXDATA[0] = 100;
  DMXDATA[1] = 150;
  DMXDATA[2] = 200;
  DMXDATA[3] = 250;
  DMXDATA[511] = 255;
}

