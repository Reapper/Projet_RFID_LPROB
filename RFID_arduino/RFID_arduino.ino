#include <SPI.h>     // SPI
#include <MFRC522.h> // RFID

#define NewEntryBT 4
#define SS_PIN 10
#define RST_PIN 9

#define IDArraySize 100
#define NumBytesCard 4

// Déclaration
MFRC522 rfid(SS_PIN, RST_PIN);

byte IDArray[IDArraySize];

int lastCardIndex = 0;

// Etapes du programme
char step = 0;

/*
void displayArray()
{
  for (byte j = 0; j <= IDArraySize; j += 4)
  {

    for (byte i = 0; i < NumBytesCard; i++)
    {
      Serial.print(IDArray[j + i]);
      Serial.print(" ");
    }
    Serial.println("");
  }
}
*/

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

  switch (step)
  {

  // Badge inconnu
  case -1:
    Serial.println("BADGE UNKNOW");
    Serial.println("CASE -1");
    step = 0;
    delay(1000);
    break;

  //Attente de badge
  case 0:

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

    for (byte j = 0; j < IDArraySize; j += 4)
    {

      for (byte i = 0; i < NumBytesCard; i++)
      {

        if (IDArray[j + i] == rfid.uid.uidByte[i])
        {
          step = 2;
        }
      }
    }

    if (step != 2)
      step = -1;

    Serial.println("READING");
    Serial.println("CASE 1");
    break;

  // Ouverture porte
  case 2:
    step = 0;
    Serial.println("ACCESS GRANTED");
    Serial.println("CASE 2");

    delay(1000);
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
    Serial.print("lastCardIndex = ");
    Serial.println(lastCardIndex);

    for (byte i = 0; i < NumBytesCard; i++)
    {
      IDArray[i + lastCardIndex] = rfid.uid.uidByte[i];
    }
    //displayArray();
    lastCardIndex += 4;

    step = 0;
    Serial.println("BADGE SAVED");
    Serial.println("CASE 10");
    delay(1000);
    break;
  }
}