#include <string.h>

/* This example shows how to use the MQTT <--> Serial bridge
feature in  ThingDesktop. 
You can get this from http://www.thingstud.io/downloads/ThingDesktop.zip

Usage: flash this to an Arduio, and connect its serial port to the bridge.

This sketch continuously reads values from a potentiometer connected to
A0. If two measurements are more than a value of 3 different, publish
the value to the 'arduinopot' topic.


*/

char inputBuffer[80];


char *readLine(char *buff) {
  delay(100);
  while(Serial.available()>0){
    *buff = Serial.read();
    buff++;
  }
  buff++;
  *buff=0;
  return buff;
}


void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}


int old_val;
int diff, val;
// the loop function runs over and over again forever
void loop() {
 
  val = analogRead(A0);
  diff = val-old_val;
  //Serial.println(diff);
  delay(50);
  if(abs(diff) >3) {
   
    Serial.print("publish:arduinopot:");
    Serial.println(val);
  }
  old_val = val;
  

}
