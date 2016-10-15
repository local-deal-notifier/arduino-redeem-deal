#include <SoftwareSerial.h>
#define REQUEST_DATA 'R'

const int LIGHT_SENSOR = A0;
const int LED = 9;
const int BUZZER = 8;
const int LIGHT_SENSOR_THRESHOLD = 250;
bool toggle = false;
SoftwareSerial BT(10, 11);

void setup() {
  // put your setup code here, to run once:
  //Setup Bluetooth serial connection to android
  BT.begin(115200);
  BT.print("$$$");
  delay(100);
  BT.println("U,9600,N");
  BT.begin(9600);
  Serial.begin(9600);

  pinMode(LIGHT_SENSOR, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int lux = analogRead(LIGHT_SENSOR);

  if (lux < LIGHT_SENSOR_THRESHOLD) {
    digitalWrite(LED, 1);
    digitalWrite(BUZZER, 1);

    if (toggle == false) {
      toggle = true;
      BT.print('R');
      BT.print("\n");

//      while(BT.available() <= 0);
    
      while(BT.available() > 0) {
        char data = BT.read();
        Serial.print(data);
      }
  
      Serial.println();
    }

    
  }
  else {
    digitalWrite(LED, 0);
    digitalWrite(BUZZER, 0);    
    toggle = false;
  }
}
