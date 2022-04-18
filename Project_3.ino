#include <LiquidCrystal.h>
#include <Wire.h>
#include <RTClib.h>

RTC_DS1307 RTC;
LiquidCrystal lcd(9, 8, 7, 6, 5, 4);

#define ENABLE 12
#define CC 13
#define C 11
#define button 3
unsigned long button_time = 0;
unsigned long last_button_time = 0;
int Buttondir = LOW;
int but;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  RTC.begin();
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Counter");
  lcd.setCursor(0,1);
  lcd.print("Clockwise");
  pinMode(ENABLE, OUTPUT);
  pinMode(CC, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(button, INPUT);
  attachInterrupt(digitalPinToInterrupt(3), reverse, RISING);
  digitalWrite(ENABLE, HIGH);

  if (!RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  digitalWrite(CC, !Buttondir);
  digitalWrite(C, Buttondir);

  DateTime now = RTC.now();
  lcd.setCursor(0,0);
  lcd.print("TIME: ");
  lcd.print(now.hour());
  lcd.print(":");
  lcd.print(now.minute());
  lcd.print(":");
  lcd.print(now.second());

  lcd.setCursor(0,1);
  lcd.print("DATE: ");
  lcd.print(now.year());
  lcd.print("/");
  lcd.print(now.month());
  lcd.print("/");
  lcd.print(now.day());

  delay(1000);
  
}

void reverse() {
  button_time = millis();
  if (button_time - last_button_time > 250) {
    Buttondir = !Buttondir;
    if (Buttondir == LOW) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Counter");
      lcd.setCursor(0,1);
      lcd.print("Clockwise");
    }
    else {
      lcd.clear();
      lcd.print("Clockwise");
    }
    last_button_time = button_time;
  }
}
