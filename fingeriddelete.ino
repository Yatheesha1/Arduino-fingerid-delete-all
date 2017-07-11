
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
uint8_t id = 0;

// Software serial for when you dont have a hardware serial port
// pin #2 is IN from sensor (YELLOW wire)
// pin #3 is OUT from arduino  (BLUE wire)
SoftwareSerial mySerial(2, 3);//rx,tx

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// On Leonardo/Micro or others with hardware serial, use those! #0 is green wire, #1 is white
//Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial1);

void setup()  
{
  Serial.begin(9600);
  Serial.println("Delete Finger");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) 
  {
    Serial.println("Found fingerprint sensor!");
  }
  else 
  {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }
}

void loop()                     // run over and over again
{
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(500);
  while (id<100) 
  {
  Serial.print("deleting ID #");
  Serial.println(id);
  deleteFingerprint(id);
  id++;
  }

}

uint8_t deleteFingerprint(uint8_t id) 
{
  uint8_t p = -1;
  p = finger.deleteModel(id);
  if (p == FINGERPRINT_OK) 
  {
    Serial.println("Deleted!");
  }  
  else 
  {
    Serial.print("Unknown error: 0x"); Serial.println(p, HEX);
    return p;
  }   
}
