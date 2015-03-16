#include <string.h>

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

// the setup function runs once when you press reset or power the board
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
  
  val = analogRead(A0);
  diff = val-old_val;
  //Serial.println(diff);
  delay(50);
  if(abs(diff) >3) {
   
    Serial.print("publish:sparkpot:");
    Serial.println(val);
  }
  old_val = val;
  

}
