#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <Servo.h>


#define SS_PIN D4
#define RST_PIN D3
bool ledOn;
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
Servo myservo; 
int pos = 0;  
const int ledPin = D1;

void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  myservo.attach(D0);
  pinMode(ledPin, OUTPUT);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "43 09 4C 63") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    digitalWrite(ledPin, LOW);
     ledOn = false; 
    Serial.println();
    for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);    // tell servo to go to position in variable 'pos'   
            
}
  }
 
 else   {
    Serial.println(" Access denied");
    digitalWrite(ledPin, HIGH);
     ledOn = true; 
    delay(3000);
  }
} 
