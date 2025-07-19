#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN PB0 
#define SS_PIN PA4  //SDA

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() 
{
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();
  Serial.println("RFID reader initialized.");
}

void loop() {
  // Check if a new RFID card is present
  if (!rfid.PICC_IsNewCardPresent()) 
  {
    return;
  }

  // Check if we can read the RFID card serial number
  if (!rfid.PICC_ReadCardSerial()) 
  {
    return;
  }

  // Send the UID to the computer via serial
  Serial.print(rfid.uid.uidByte[0], HEX);
  Serial.print(" ");
  Serial.print(rfid.uid.uidByte[1], HEX);
  Serial.print(" ");
  Serial.print(rfid.uid.uidByte[2], HEX);
  Serial.print(" ");
  Serial.println(rfid.uid.uidByte[3], HEX);

  // Wait for the response from the computer (Python script)
  while (Serial.available() == 0) {
    // Wait for incoming serial data
  }

  // Read and print the response from the Python script
  String productInfo = Serial.readStringUntil('\n');
  Serial.println(productInfo);

  // Halt the card so it can be read again later
  rfid.PICC_HaltA();
}
