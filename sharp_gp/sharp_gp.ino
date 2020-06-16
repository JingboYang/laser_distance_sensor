/*SHARP GP2Y0A710K0F IR distance sensor with Arduino and SharpIR library example code. More info: https://www.makerguides.com */

// Include the library:
#include "src/sharp_lib/SharpIR.h"

// Define model and input pin:
#define IRPin A0
#define model 100500

const int SERIAL_PLOTTER = 0; // Change to 1 to use Arduino IDE's Serial Plotter

// Create variable to store the distance:
int distance_cm;

/* Model :
  GP2Y0A02YK0F --> 20150
  GP2Y0A21YK0F --> 1080
  GP2Y0A710K0F --> 100500
  GP2YA41SK0F --> 430
*/

// Create a new instance of the SharpIR class:
SharpIR mySensor = SharpIR(IRPin, model);

void setup() {
  // Begin serial communication at a baud rate of 9600:
  Serial.begin(115200);
}

void loop() {
  // Get a distance measurement and store it as distance_cm:
  distance_cm = mySensor.distance();

  if (SERIAL_PLOTTER == 0){
    Serial.print("Dist= ");
    Serial.println(distance_cm);
  }
  else {
    Serial.println(distance_cm); // print measurement to serial terminal
  }

  // delay(1000);
}
