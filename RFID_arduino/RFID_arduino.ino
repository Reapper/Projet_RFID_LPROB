#include <SPI.h>     // SPI
#include <MFRC522.h> // RFID

// https://github.com/janelia-arduino/Vector
#include <Vector.h>

// https://github.com/janelia-arduino/Array
#include <Array.h>

#define NewEntryBT 4
#define SS_PIN 10
#define RST_PIN 9

// Déclaration
MFRC522 rfid(SS_PIN, RST_PIN);

// Tableaux contenent les IDs
//Vector<Array<byte, 4>> IDArray = {};
Vector<byte> IDArray = {};
Array<byte, 4> CardCode = {};

// Etapes du programme
char step = 0;

void setup()
{
  // Init RS232
  Serial.begin(9600);
  Serial.println("IS ON !");

  // Init SPI bus
  SPI.begin();

  // Init MFRC522
  rfid.PCD_Init();

  pinMode(NewEntryBT, INPUT_PULLUP);
}

void loop()
{

  char testBytes = 0;

  switch (step)
  {

  // Badge inconnu
  case -1:
    Serial.println("CASE -1: Badge unknow...");
    step = 0;
    break;

  //Attente de badge
  case 0:

    CardCode = {};

    //Serial.println(digitalRead(NewEntryBT));

    // Si bouton Nouvelle Entrée est appuyé
    if (!digitalRead(NewEntryBT))
    {
      Serial.println("NEW BADGE");
      step = 10;
      }

    // Initialisé la boucle si aucun badge n'est présent
    if (!rfid.PICC_IsNewCardPresent())
      return;

    // Vérifier la présence d'un nouveau badge
    if (!rfid.PICC_ReadCardSerial())
      return;

    Serial.println("CASE 0");
    step = 1;
    break;

  // Test l'ID du badge (4 octets)
  case 1:

    Serial.print("IDArray size = ");
      Serial.println(IDArray.size());

    Serial.print("CardCode size = ");
      Serial.println(CardCode.size());

    for (byte j = 0; j < IDArray.size(); j++)
    {
      
      for (byte i = 0; i < CardCode.size(); i++)
      {
        
        if (IDArray[j][i] != rfid.uid.uidByte[i])
          testBytes += 1;

        Serial.print(" j = ");
        Serial.print(j);
        Serial.print(" IDArray = ");
        Serial.print(IDArray[j][i]);
      }
      Serial.print("\n TEST BYTES = ");
      Serial.println(testBytes);
    }
    if (testBytes == 0)
      step = 2;
    else
      step = -1;

    Serial.println("CASE 1");
    break;

  // Ouverture porte
  case 2:
    step = 0;
    Serial.println("CASE 2");
    Serial.println("ACCESS GRANTED");
    break;

  // Enregistrement Badge
  case 10:

    // Initialisé la boucle si aucun badge n'est présent
    if (!rfid.PICC_IsNewCardPresent())
      return;

    // Vérifier la présence d'un nouveau badge
    if (!rfid.PICC_ReadCardSerial())
      return;

    // Enregistre le nouveau Badge
    for (byte i = 0; i < 4; i++)
    {
      //CardCode[i] = rfid.uid.uidByte[i];
      CardCode[i] = 23;
      Serial.print(" i = ");
      Serial.print(i);
      Serial.print(" CardCode = ");
      Serial.print(CardCode[i]);
    }

    Serial.println("");

    byte tab[]={24,24,24,24};
    //IDArray.push_back(CardCode);
    IDArray.push_back(tab);
    //IDArray.push_back(rfid.uid.uidByte);
    step = 0;
    Serial.println("CASE 10");
    break;
  }

  /*

for (byte j=0;i<10;j++)
      for (byte i = 0; i < 4; i++) 
      {
        IDArray[j][i] = rfid.uid.uidByte[i];
      }


    break;
  }

  
  // Affichage de l'ID 
  Serial.println("Un badge est détecté");
  Serial.println(" L'UID du tag est:");
  for (byte i = 0; i < 4; i++) 
  {
    Serial.print(nuidPICC[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  // Re-Init RFID
  rfid.PICC_HaltA(); // Halt PICC
  rfid.PCD_StopCrypto1(); // Stop encryption on PCD
  */
}

/*#include <MFRC522.h>
 
#define NewEntryBT      4 
#define RST_PIN         9  
#define SS_PIN          10  
 
 
MFRC522 mfrc522(SS_PIN, RST_PIN); 

unsigned char step = 0; // Etapes du programme

byte nuidPICC[4];
 
void setup() { 
  //Init modules
 Serial.begin(115200); 
 while (!Serial); 
 SPI.begin();  
 mfrc522.PCD_Init();  
 mfrc522.PCD_DumpVersionToSerial(); //Détails de sortie du lecteur 
 Serial.println(F("Scan PICC to see UID, type, and data blocks...")); 
} 
 
void loop() { 

  // Vérifier la présence d'un nouveau badge 
  if ( !mfrc522.PICC_ReadCardSerial()) return;

  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid)); 

  // Enregistrer l'ID du badge (4 octets) 
  /*
  for (byte i = 0; i < 4; i++) 
  {
    nuidPICC[i] = mfrc522.uid.uidByte[i];
  }*/
/*else {

  // Affichage de l'ID 
  Serial.println("Un badge est détecté");
  Serial.println(" L'UID du tag est:");
  for (byte i = 0; i < 4; i++) 
  {
    Serial.print(nuidPICC[i], HEX);
    Serial.print(" ");
  }
  }*/

/*
  switch (step)
  {

  
  
  // Attente de carte
  case 0:


      // Si bouton Nouvelle entrée est appuyé
      if(digitalRead(NewEntryBT)) step = 2; 

      // Initialisé la boucle si aucun badge n'est présent 
      if ( !mfrc522.PICC_IsNewCardPresent()) return;
      else step = 1;

    break;
  
  // Auth + verif de validation d'heure
  case 1:
    
    break;

  // Nouvelle entrée
  case 2:
    //AuthArray.push_back(25);
    
    break;
  
  default:
    break;
  }
  /*
 //Rechercher de nouvelles cartes
 if ( ! mfrc522.PICC_IsNewCardPresent()) { 
  return; 
 } 
 
 if ( ! mfrc522.PICC_ReadCardSerial()) { 
  return; 
 } */

//Récupération d'informations depuis le dispositif RFID

//}