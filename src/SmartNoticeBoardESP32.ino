#include <LiquidCrystal.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// LCD Pins: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(14, 27, 26, 25, 33, 32);

String message = "Welcome";
int scrollIndex = 0;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("SmartNoticeBoard");

  lcd.begin(16, 2);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Smart Notice");
  lcd.setCursor(0, 1);
  lcd.print("Board Ready");

  delay(2000);
  lcd.clear();
}

void loop() {

  if (SerialBT.available()) {
    message = SerialBT.readStringUntil('\n');
    message.trim();
    scrollIndex = 0;
  }

  displayMessage();

  delay(300);
}

void displayMessage() {

  lcd.clear();

  if (message.length() <= 16) {
    lcd.setCursor(0, 0);
    lcd.print(message);
  } else {

    String text = message.substring(scrollIndex);

    while (text.length() < 16)
      text += " ";

    lcd.setCursor(0, 0);
    lcd.print(text.substring(0, 16));

    scrollIndex++;

    if (scrollIndex >= message.length())
      scrollIndex = 0;
  }

  lcd.setCursor(0, 1);
  lcd.print("ESP32 Notice");
}
