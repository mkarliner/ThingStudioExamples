// This #include statement was automatically added by the Spark IDE.
#include "MQTT/MQTT.h"

/* This sketch does various random MQTT actions, but also messures
values from a potentiometer on A0 and sends messages to the topic
'sparkpot' if they change.
*/

void callback(char* topic, byte* payload, unsigned int length);
MQTT client("mqtt-modern-industry.com", 1883, callback);

// recieve message
void callback(char* topic, byte* payload, unsigned int length) {
    char p[length + 1];
    memcpy(p, payload, length);
    p[length] = NULL;
    String message(p);

    if (message.equals("RED"))    
        RGB.color(255, 0, 0);
    else if (message.equals("GREEN"))    
        RGB.color(0, 255, 0);
    else if (message.equals("BLUE"))    
        RGB.color(0, 0, 255);
    else    
        RGB.color(255, 255, 255);
    delay(1000);
}


void setup() {
    RGB.control(true);
    // Serial.begin(9600);
    // Serial.println("Hello Mike");
    pinMode(A0, INPUT);
    
    // connect to the server
    client.connect("sparkclient553425", "sdaf", "asdf");

    // publish/subscribe
    if (client.isConnected()) {
        client.publish("textfeed","hello spark world");
        client.subscribe("inTopic");
    }
}

int oldval =0;

void loop() {
    int val;
    char buf[80];
    
    if (client.isConnected()) {
        client.loop();
        // Serial.println("LOOP");
    }
    
    val = analogRead(A0);
    int diff = abs(val - oldval);
        if(diff > 10) {
            sprintf(buf, "%d", val);
            client.publish("sparkpot", buf);
            oldval = val;
        }
        delay(10);
      
}

