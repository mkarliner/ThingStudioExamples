#include <string.h>

/*

This example shows how to use the MQTT <--> Serial bridge
feature in  ThingDesktop. 

You can get this from http://www.thingstud.io/downloads/ThingDesktop.zip

Usage: flash this to an Arduio, and connect its serial port to the bridge.

This sketch subscribes to a topic called "ledcmds" and expects messages
of 'true' or 'false'. When it receives these it will switch the on-board led
on or off and publish its status back to the topic 'ledstatus'

*/

char inputBuffer[80];

char *readLine(char *buff) {
  while(Serial.available()>0){
    *buff = Serial.read();
    buff++;
  }
  *buff=0;
  return buff;
}

void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Serial.println("subscribe:ledcmds");
}

int old_val;
int diff, val;
// the loop function runs over and over again forever
void loop() {
  char *pch;
  
  if(Serial.available()>0) {
    readLine(inputBuffer);
    pch = strtok (inputBuffer,":\n");
    pch = strtok(NULL, ":\n"); // Message
    if(strcmp(pch, "true") == 0) {
      digitalWrite(13, HIGH);
      Serial.println("publish:ledstatus:on");
    } else {
      digitalWrite(13, LOW);
      Serial.println("publish:ledstatus:off");
    }
  }

}
