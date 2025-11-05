const int ledPin = 11;
//const int photoPin = A0; THIS CODE IS COMPLETELY AND UTTERLY REDUNDANT YOU FOOOOOOLS!!!! -Vivi 

void setup() {
  //sets up used components
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT); //testhbdajhbcjhbc
}

void loop() {
  analogWrite(ledPin, map(analogRead(photoPin), 0, 1023, 0, 255)); //Maps photoreceptor data to 8-byte, then sends to LED.

} // test from Oz!! Hello!!!
