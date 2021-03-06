# Projet Capteur Lecteur RFID (rapport_préliminaire)  -  CAUSSE Axel  -  MARCEAU Axel
<br  />

## Informations sur le capteur :

### Liste des documentations consultées (avec adresses web + description succincte du contenu) :
  ```
  - https://www.electronique-mixte.fr/microcontrolleurs/rfid-controle-dacces-par-badge-avec-arduino
  - https://www.gotronic.fr/art-module-rfid-13-56-mhz-tag-rc522-25651.htm
  - https://www.aranacorp.com/fr/utilisation-dun-module-rfid-avec-arduino/
  - http://les-electroniciens.com/videos/arduino-ep14-comment-utiliser-le-module-rfid-rc522
  ```
 
### Fonction du capteur : 
  ```
  Détection et lecture d'informations de supports adaptés (carte, badge, etc ...) grâce à la technologie RFID 
  ```
 
### Exemples d'utilisations :
  ```
  Utilisation pour à des fins de sécurité 
  ex : contrôle d'identité à l'entrée de zones à accès restreint.
  ```
 
### tension d'alimentation du capteur :
  ```
  Alimentation nominale : 3.3 V - DC
  ```
 
### Tension admissible pour les entrées/sorties :
  ```
  3.3 V - DC
  ```
 
### Distance minimum/maximum pour que le capteur puisse mesurer :
  ```
  Distance MIN de détection : 0 cm 
  Distance MAX de détection : 10 cm
  Distance Optimale de détection du modèle de la datasheet : 10 mm
  ```
 
### Cadence maximum des mesures :
  ```
  La cadence des mesures n'étant donnée dans aucune datasheet, nous effectuerons des essais directement sur la carte 
  afin d'essayer de la définir
  ```
 
### Latence pour la mesure:
  ```
  Tout comme la cadence maximum, nous effectuerons des tests afin de pouvoir la définir 
  ```
 
### Communication via:
  ```
  La communication entre le capteur et l'Arduino s'effectue grâce à un bus de données SPI
  ```
 
### Librairie disponible pour Arduino:
  ```
  La librairie utilisée dans le logiciel arduino conçue spécialement pour ce capteur est la librairie "MFRC522"
  ```
 
### Programme d'exemple disponible pour Arduino:
  ```
  La programme d'exemple fourni dans une des datasheet :
  
  #include <SPI.h> 
  #include <MFRC522.h> 
  #define RST_PIN 9 
  #define SS_PIN 10 

  MFRC522 mfrc522(SS_PIN, RST_PIN);

  void setup() {
    /Serial.begin(9600);
    wile (!serial);
    SPI.begin();
    mfrc522.PCD_Init();
    mfrc522.PCD_DumpVersionToSerial();
    Serial.println(F("Scan PICC to see UID, type, and data blocks ..."));

 }

 void loop() {
  if(!mfrc522.PICC_IsNewCardPresent()){
    return;
  }
  if(!mfrc522.PICC_IsNewCardSerial()){
    return;
  }
  
  mfrc522.PICC_DumpToSerial(&'mfrc522.uid));
 }
  ```
 
### Tarifs et fournisseurs:
  ```
  Prix de 11,90€ chez le fournisseur "Joy-It", seul dont nous avons trouvé le nom, ou 1€ chez des revendeurs chinois 
  tiers
  ```
