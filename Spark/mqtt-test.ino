// This #include statement was automatically added by the Spark IDE.
#include "MQTT/MQTT.h"

Servo myservo;

void callback(char* topic, byte* payload, unsigned int length);
MQTT client("mqtt.modern-industry.com", 1883, callback);

// receive message


    int red=0;
    int blue=0;
    int green=0;

void callback(char* intopic, byte* payload, unsigned int length) {
    //Payloads are JSON strings, so increment past the first 
    //quote to get to the first message character.
    payload++;
    //And now the payload is 1 character shorter, so copy 
    // one less character.
    char p[length + 1];
    memcpy(p, payload, length-1);
    p[length] = NULL;
    
    char t[strlen(intopic)+1];
    memcpy(t, intopic, strlen(intopic));
    t[strlen(intopic)] = NULL;
    

    String message(p);
    String topic(t);
    Serial.println(topic);
    Serial.println(message);
    if(topic.equals("/mike/sparkred")) {
        red = atoi(p);
        Serial.println("red");
    }
        
    else if (topic.equals("/mike/sparkblue"))    
        blue = atoi(p);
    else if (topic.equals("/mike/sparkgreen"))    
        green = atoi(p);
    else if (topic.equals("/mike/sparkservo")) 
        myservo.write(atoi(p));
    else
        RGB.color(255, 255, 255);
    RGB.color(red, green, blue);
}


void setup() {
    RGB.control(true);
     RGB.color(0, 0, 255);
    Serial.begin(9600);
    delay(10000);
    Serial.println("Hello Mike");
    myservo.attach(A1);
    pinMode(A0, INPUT);
    
    // connect to the server
    client.connect("5sparkclient", "guest", "guest");

    // publish/subscribe
    if (client.isConnected()) {
        Serial.println("Connected");
        RGB.color(0, 255, 0);
        client.publish("textfeed","hello spark world");
        client.subscribe("/mike/sparkred");
        client.subscribe("/mike/sparkblue");
        client.subscribe("/mike/sparkgreen");
        client.subscribe("/mike/sparkservo");
    }
}

int oldval =0;

void loop() {
    int val;
    char buf[80];
    
    if (client.isConnected()) {
        client.loop();
        //  Serial.println("LOOP");
    }
    
    val = analogRead(A0);
    int diff = abs(val - oldval);
        if(diff > 10) {
            Serial.println(val);
            sprintf(buf, "%d", val);
            client.publish("/mike/sparkpot", buf);
            oldval = val;
        }
        delay(10);
      
}
