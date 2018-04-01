void setup() {
  Serial.begin(9600); //Set the communication serial
}

void loop() {
  int x=analogRead(A0); //Declare a variable to read analog read
  Serial.println(x); //Print the read value
  delay(100); //Delay while reading
}
