// I2C interface by default
//
#include "Wire.h"
#include "SparkFunIMU.h"
#include "SparkFunLSM303C.h"
#include "LSM303CTypes.h"
#include <Adafruit_NeoPixel.h>

#define PIN 8
#define NUM_LEDS 1

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

// #define DEBUG 1 in SparkFunLSM303C.h turns on debugging statements.
// Redefine to 0 to turn them off.

LSM303C myIMU;

float x; 
float y; 
float z; 
float w;
int steps, flag;// , flag_movement;
float threshold = 1200;
unsigned long startTime = millis();
int interval = 10000;//600000;
int flag_movement = 0;


void setup()
{
  Serial.begin(115200);
  if (myIMU.begin() != IMU_SUCCESS)
  {
    Serial.println("Failed setup.");
    while(1);
  }
  strip.begin();
  strip.show();
  //pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
Serial.print(flag_movement);
Serial.print("\t");
  
x = float((myIMU.readAccelX()));
y = float((myIMU.readAccelY()));
z = float((myIMU.readAccelZ()));
w = sqrt(sq(x)+sq(y)+sq(z));


  //Serial.print("\t");
  //x = 1;

//  Serial.print(myIMU.readAccelX(), 4);
//Serial.print("\t");
//
//  Serial.print(myIMU.readAccelY(), 4);
//  Serial.print("\t");
 
 Serial.print(x);
Serial.print("\t");
 Serial.print(y);
Serial.print("\t");
 Serial.print(z);
Serial.print("\t");
  Serial.println(w);

if(w<threshold)
  {
    if (flag_movement == 0)
    {
      if (millis() - startTime > interval)
      {
        strip.setPixelColor(0, 255, 0, 0);                 // HP : Curly braces around code after if statement
        strip.show();
       }
     }
  
     else
     {
      flag_movement = 0;
     }
  }

else
  {
    flag_movement = 1;
    startTime = millis();
    strip.setPixelColor(0, 0, 0, 0);                   // HP : Curly braces around code after if statement
    strip.show(); // if the light turns on, the person is in danger.  // HP: Use // for comments
  }
  delay(100);
}
