int ledPin = 13; // Declare a variable as ledPin(Digital pin 13)
int ldrPin = A0; // Declare a variable as ldrPin(Analog pin A0)

void setup(){
    Serial.begin(9600);
    pinMode(ledPin,OUTPUT); // Initialize the ledPin as Output
    pinMode(ldrPin,INPUT); // Initialize the ldrPin as Input
}
void loop(){
   int ldrStatus = analogRead(ldrPin); // Read the value of ldr
   if(ldrStatus<=300){
      digitalWrite(ledPin,HIGH); // Turn on LED
      Serial.println("LDR is dark, LED is on....");
    }
    else{
      digitalWrite(ledPin,LOW); // Turn off LED
    }
}
