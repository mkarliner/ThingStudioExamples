/*

This example shows how to publish ultrasonic distance measurements via MQTT.

Try out this example with ThingStudio: http://www.thingstud.io/

*/

#define trigPin 10
#define echoPin 11

void setup() {

  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

int duration, distance, old_distance, diff;

void loop() {
  
  // send out a pulse from the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  diff = distance - old_distance;

  delay(100);

  if (abs(diff) > .01) {

    if (distance >= 200 || distance <= 0) {

      Serial.println("Out of range");

    } else {

      Serial.print("publish:ultraDistance:");
      Serial.println(distance);

    }

  }
 
 old_distance = distance;

}