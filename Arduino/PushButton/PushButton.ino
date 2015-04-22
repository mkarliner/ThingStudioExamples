const int ledPin = 13;
const int inputPin = 2;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int val = digitalRead(inputPin);
  if (val == HIGH) {
    digitalWrite(ledPin, HIGH);
    Serial.println("publish:kitchenLight:on");
  } else {
    digitalWrite(ledPin, LOW);
    Serial.println("publish:kitchenLight:off");
  }
  delay(1000);
}