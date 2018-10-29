int echoPin = 9;
int trigPin = 10;
int ledPin = 13;
void setup(){
  Serial.begin(9600);
  pinMode(echoPin,INPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(ledPin,OUTPUT);
}

void loop(){
  long duration, distance;
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration=pulseIn(echoPin, HIGH);
  distance =(duration/2)/29.1; // Duration converted into Distance
  Serial.print(distance);
  Serial.println("CM");
  delay(10);
  
 if((distance<=10)){
  digitalWrite(ledPin, HIGH);
}
else if(distance>10){
  digitalWrite(ledPin, LOW);
}
}
