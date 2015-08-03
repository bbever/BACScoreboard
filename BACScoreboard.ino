#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

/*-----( Declare Constants )-----*/
#define I2C_ADDR    0x3F
#define BACKLIGHT_PIN  3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

#define  LED_OFF  0
#define  LED_ON  1

int Alc_Sensor = A0;
int sensorValue = 0;
int hScore = 0;
int cOffset = 0;

LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

void setup() {
  lcd.begin(16,2);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(LED_ON);
  
  initialize_display();
  display_welcome();
  delay(3000);
  sensor_warmup();
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Current reading:");
  lcd.setCursor(5,1);
  lcd.print("High:");
  lcd.print(hScore);
  cOffset = analogRead(Alc_Sensor);
}

void loop() {
  lcd.setCursor(0,1);
  lcd.print("     ");
  lcd.setCursor(0,1);
  sensorValue = read_alc_sensor();
  lcd.print(sensorValue);
  if (sensorValue > hScore) {
    hScore = sensorValue;
    lcd.setCursor(10,1);
    lcd.print(hScore);
  }
   
  delay(1500);
  
}

int read_alc_sensor() {
  int tV = 0;
  tV = analogRead(Alc_Sensor);
  if (tV < cOffset) {
    cOffset = tV;
  }
  return tV-cOffset;
}

void initialize_display() {
  lcd.clear();
  delay(1000);
  lcd.home();
  lcd.backlight();
}

void display_welcome() {
  lcd.setCursor(0,0);
  //lcd.autoscroll();
  lcd.print("Welcome to the");
  lcd.setCursor(0,1);
  lcd.print("BAC Scoreboard");
  //lcd.noautoscroll();
}

void sensor_warmup() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Sensor heating...");
  lcd.setCursor(0,1);
  lcd.print("60 Secs left");
  for (int countdown = 60; countdown >= 0; countdown--) {
    lcd.setCursor(0,1);
    if (countdown < 10) {
      lcd.print("0");
    }
    lcd.print(countdown);
    delay(1000);
  }
  lcd.setCursor(0,1);
  lcd.print("Finished        ");
}
