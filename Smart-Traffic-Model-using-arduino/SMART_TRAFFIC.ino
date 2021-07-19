#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
#define LED_G2 2 //define green LED pin
#define LED_G3 3
#define LED_G4 4
#define LED_G5 5 //define green LED pin
#define LED_G6 6
#define LED_G7 7
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

void setup()
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  pinMode(LED_G2, OUTPUT);
  pinMode(LED_G3, OUTPUT);
  pinMode(LED_G4, OUTPUT);
  pinMode(LED_G5, OUTPUT);
  pinMode(LED_G6, OUTPUT);
  pinMode(LED_G7, OUTPUT);
  pinMode(8,OUTPUT);
  Serial.println("Put your card to the reader...");
  Serial.println();

}
void loop()
{
 
  digitalWrite(LED_G2, HIGH);
  digitalWrite(LED_G3, LOW);
  digitalWrite(LED_G4, LOW);
  digitalWrite(LED_G5, LOW);
  digitalWrite(LED_G6, HIGH);
  digitalWrite(LED_G7, HIGH);
  timer();
  digitalWrite(LED_G2, LOW);
  digitalWrite(LED_G3, HIGH);
  digitalWrite(LED_G4, LOW);
  digitalWrite(LED_G5, HIGH);
  digitalWrite(LED_G6, LOW);
  digitalWrite(LED_G7, HIGH);
  timer();
  digitalWrite(LED_G2, LOW);
  digitalWrite(LED_G3, LOW);
  digitalWrite(LED_G4, HIGH);
  digitalWrite(LED_G5, HIGH);
  digitalWrite(LED_G6, HIGH);
  digitalWrite(LED_G7, LOW);
  timer();
}

void timer(){
  int  i;
  for(i=0;i<500;i++)
  {
   
    scan_1();
    delay(1);
  }
  return;
}
void blink()

{
  for(int m=0;m<150;m++)
  {
   digitalWrite(8, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(8, LOW);    // turn the LED off by making the voltage LOW
  delay(100);  
  }
  
}

void scan_1()
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
  if (content.substring(1) == "CA 8A F1 80") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("AMBULANCE ON THE WAY");
    Serial.println();
    digitalWrite(LED_G2, HIGH);
    digitalWrite(LED_G3, LOW);
    digitalWrite(LED_G4, LOW);
    digitalWrite(LED_G5, LOW);
    digitalWrite(LED_G6, HIGH);
    digitalWrite(LED_G7, HIGH);
    blink();
    delay(100);
    return;
  }
 
 else   {
    Serial.println(" Access denied");
    return;
  }
}
