#include <SPI.h> 
#include <MFRC522.h> 
 
#define RST_PIN         9  
#define SS_PIN          10  
 
MFRC522 mfrc522(SS_PIN, RST_PIN); 
 
void setup() { 
  //Initialisierung des RFID-Moduls 
 Serial.begin(9600); 
 while (!Serial); 
 SPI.begin();  
 mfrc522.PCD_Init();  
 mfrc522.PCD_DumpVersionToSerial(); //Details des Lesegerätes ausgeben 
 Serial.println(F("Scan PICC to see UID, type, and data blocks...")); 
} 
 
void loop() { 
 //Suche nach neuen Karten 
 if ( ! mfrc522.PICC_IsNewCardPresent()) { 
  return; 
 } 
 
 if ( ! mfrc522.PICC_ReadCardSerial()) { 
  return; 
 } 
 
 //Informationsabruf des RFID-Gerätes 
 mfrc522.PICC_DumpToSerial(&(mfrc522.uid)); 
 
}