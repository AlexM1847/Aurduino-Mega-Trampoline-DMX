// https://www.element14.com/community/groups/open-source-hardware/blog/2017/08/24/dmx-explained-dmx512-and-rs-485-protocol-detail-for-lighting-applications

////////////////////////
//    Function header //
////////////////////////

// Prototypes

// Sensor Functions
void updateSensoreValues(bool);
float pingSensor(int sensNumber, bool debug);

// TRAMPOLIN INTERFACE
void trampolineDMX();
byte valuesToIntensity(float numberToConvert);

// DMX Functions
void encodeDMX(bool debuger);
void writeDMXUniverse(bool);
void readDMXUniverse(bool debug);

///////////////////////////
//  update values        //
///////////////////////////
void updateSensoreValues(bool debug = false){
  // THIS FUNCTION SHOULD TAKE ABOUT 360,000 MICROSECONDS TO RUN
  //    WITH 12 SENSORS
  if(debug){
    Serial.println("Updateing sensors ...");
  }
  counter = 0;
  while(counter < numSensors){
    sensorDistance[counter] = pingSensor(counter, debug);
    
    if(debug){
      Serial.print("Sensor ");
      Serial.print(counter + 1);
      Serial.print(" = ");
      Serial.print(sensorDistance[counter]);
      Serial.println("cm");
    }
    counter ++;
  }
  if (debug){
      Serial.println("Update complete.");
  }
 }

/////////////////////
//   PingSensor   //
////////////////////
float pingSensor(int sensNumber, bool debug){
  int trigPin = startPin + ((sensNumber * 2)) ;
  int echoPin = startPin + ((sensNumber * 2) + 1);
    
  unsigned long t1;
  unsigned long t2;
  unsigned long pulse_width;
  float cm;
  float inches;

  // Hold the trigger pin high for at least 10 us
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Wait for pulse on echo pin
  while ( digitalRead(echoPin) == 0 );

  // Measure how long the echo pin was held high (pulse width)
  // Note: the micros() counter will overflow after ~70 min
  t1 = micros();
  while ( digitalRead(echoPin) == 1);
  t2 = micros();
  pulse_width = t2 - t1;

  // Calculate distance in centimeters and inches. The constants
  // are found in the datasheet, and calculated from the assumed speed 
  //of sound in air at sea level (~340 m/s).
  cm = pulse_width / 58.0;
  inches = pulse_width / 148.0;

  // OUT OF RANGE CONDITIOn GOES TO 0
  if ( pulse_width > MAX_DIST ) {
    pulse_width = 0;
  }
  
  delay(10);


  // Calculate distance in centimeters and inches. The constants
  // are found in the datasheet, and calculated from the assumed speed 
  //of sound in air at sea level (~340 m/s).
  return pulse_width / 58.0;
}

/////////////////////
//   PingSensor   //
////////////////////
void trampolineDMX(){
  counter = 0;
  
  while(counter < numSensors){
    // CHECKS IF OUT OF RANGE WAS DETECTED AND WILL LEAVE THE PREVIOUS VALUE
    // AND CONTIUNE TO THE NEXT VALUE
    if(sensorDistance[counter] == 0){
      counter ++;
    }
    if(sensorDistance[counter] < minDistance){
      // SETS DISTANCE TO MIN DISTANCE IN CASE OF ERROR
      sensorDistance[counter] = minDistance;
      Serial.print("Sensor ");
      Serial.print(counter + 1);
      Serial.print(" was to low and was set to the minimum allowable distance.");
      Serial.println();
      } else if (sensorDistance[counter]  > maxDistance){
      // SETS DISTANCE TO MAX DISTANCE IN CASE OF ERROR
      sensorDistance[counter] = maxDistance;
      Serial.print("Sensor ");
      Serial.print(counter + 1);
      Serial.print(" was to high and was set to the maximum allowable distance.");
      Serial.println();
        }
      lightIntensities[counter] = valuesToIntensity(sensorDistance[counter]);
      Serial.println(lightIntensities[counter]);
  }
}

///////////////////////////
//   valuesToIntensity   //
///////////////////////////
byte valuesToIntensity(float numberToConvert){
  // THIS FUNCTION CHANGES THE DISTANC INTO A DMX VALUE AND TYPE CASTS IT
  return (byte) ((numberToConvert - minDistance) * ((maxIntensity - minIntensity) / (maxDistance - minDistance)));
}

////////////////////////////////////////
//    Function to read DMX Universe   //
////////////////////////////////////////
void readDMXUniverse(bool debug = false){
  for(size_t i = 1; i <= DMXSERIAL_MAX; ++i)
    {
      if(DMXSerial.read(DMXDATA[i]));
    }
    // Set ACTIVATOR
    activator = DMXDATA[0];

    // Set minVal
    minIntensity = DMXDATA[1];

    // Set maxVal
    maxIntensity = DMXDATA[2];
}


///////////////////////////
//   encodeDMXToBUFFER   //
///////////////////////////
void encodeDMX(bool debuger =false) {
  counter = 0;
  while(counter < numSensors){
    DMXDATA[(lightAdress[counter]) - 1] = lightIntensities[counter];
  }
}

////////////////////////////////////////
//    Function to write DMX Universe  //
////////////////////////////////////////
void writeDMXUniverse(bool debug = false){
  for(size_t i = 1; i <= DMXSERIAL_MAX; ++i)
    {
      DMXSerial.write(i,DMXDATA[i - 1]);
    }
}





