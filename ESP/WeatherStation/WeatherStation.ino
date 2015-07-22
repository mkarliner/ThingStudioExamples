#include <PubSubClient.h>



#include <ArduinoJson.h>
#include <stdio.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SFE_BMP180.h>
#include <Wire.h>



const char *ssid =	"xxxx";		// cannot be longer than 32 characters!
const char *pass =	"xxxx";		//

// Update these with values suitable for your network.
IPAddress server(192, 168, 1, 2);


int delayCnt = 0;


void callback(const MQTT::Publish& pub) {
  delayCnt = 99999;
  Serial.println("Message for you sir!");
}

WiFiClient wclient;
PubSubClient client(wclient, server);


void setup()
{
  // Setup console
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();

  client.set_callback(callback);

  WiFi.begin(ssid, pass);
  dht_init();

  int retries = 0;
  while ((WiFi.status() != WL_CONNECTED) && (retries < 30)) {
    retries++;
    delay(1000);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connected");
  }

  int mqttStatus = 0 ;
  while (!mqttStatus) {
    mqttStatus = client.connect(MQTT::Connect("ESP12")
                                .set_clean_session()
                                .set_will("status", "down")
                                .set_auth("guest", "guest")
                                .set_keepalive(30)
                               );
    Serial.println(mqttStatus);
//    if (mqttStatus) {
//      client.subscribe("/weather/london/cmds");
//      client.publish(MQTT::Publish("outTopic", "payload")
//                     .set_retain()
//                     .set_qos(1)
//                     .set_dup()
//                    );
//    }
  }
  initBmp();
}

void loop()
{

  char outbuf[200];
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  if (delayCnt > 200) {
    readBmp(root);
    readDht(root);
    delayCnt = 0;
    root.printTo(outbuf, sizeof outbuf);
    client.publish(MQTT::Publish("/weather/london", outbuf )
                   .set_retain()
                   .set_qos(1)
                   .set_dup()
                  );

  }

  delay(10);
  delayCnt++;
  client.loop();
}

