#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#define REQUEST_DATA 'R'

const int LIGHT_SENSOR = A0;
const int LED = 9;
const int BUZZER = 8;
const int LIGHT_SENSOR_THRESHOLD = 400;
bool toggle = false;
char line1[] = "";
char line2[] = "";
SoftwareSerial BT(2, 3);
LiquidCrystal lcd(4, 6, 10, 11, 12, 13);

void setup() {
  // put your setup code here, to run once:
  //Setup Bluetooth serial connection to android
  BT.begin(115200);
  BT.print("$$$");
  delay(100);
  BT.println("U,9600,N");
  BT.begin(9600);
  Serial.begin(9600);

  lcd.begin(16,2);
  lcd.print("Hack Western 3");

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
      lcd.clear();
      while(BT.available() > 0) {
        char data = BT.read();
        Serial.print(data);
        lcd.print(data);
      }
      lcd.setCursor(0,2);
      lcd.print(" Confirmed");
      Serial.println();
    }
  }
  else {
    digitalWrite(LED, 0);
    digitalWrite(BUZZER, 0); 
    
    toggle = false;
  }
}
