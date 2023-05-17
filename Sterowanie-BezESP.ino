#include <RemoteXY.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <SPI.h>

//  Przyciski
#define PIN_WEJDZ 5
#define PIN_WYJDZ 8
#define PIN_ZMNIEJSZ 6
#define PIN_ZWIEKSZ 7
#define PIN_DALEJ 4

//  DHT11
#define DHT11_PIN 2

//  OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET
#define SCREEN_ADDRESS 0x3C
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//  Poziomy
int select = 10;
int poziom_wilgo = 50;
int poziom_swia = 50;
int poziom_wody = 50;
DHT dht;


void setup() {
  Serial.begin(9600);

  pinMode (PIN_WEJDZ, INPUT_PULLUP);
  pinMode (PIN_WYJDZ, INPUT_PULLUP);
  pinMode (PIN_ZMNIEJSZ, INPUT_PULLUP);
  pinMode (PIN_DALEJ, INPUT_PULLUP);
  pinMode (PIN_ZWIEKSZ, INPUT_PULLUP);
  
  //  DHT11
  dht.setup(DHT11_PIN);

  //  OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(40, 30);
  display.println("Projekt");
  display.display(); 
  delay(1000);

}

void loop() {
  //  Dane
  display.clearDisplay();
  int wilgo = dht.getHumidity();
  int temp = dht.getTemperature();
  int S = analogRead(A1);
  int S1 = (1024-S)/10;

  //  Menu
  int STAN1 = digitalRead(PIN_DALEJ);
  int STAN2 = digitalRead(PIN_WEJDZ);
//  Główna
  if(STAN1 == LOW) {
  display.setTextColor(BLACK);
  display.setCursor(0, (select));
  display.println(">");
  select = select+10;
  delay(500);
  }
  if(select > 40){
    select = 10;
  }
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Wybierz opcje:");
  display.setCursor(10, 10);
  display.println("Temperatura");
  display.setCursor(10, 20);
  display.println("Wilgotnosc");
  display.setCursor(10, 30);
  display.println("Swiatlo");
  display.setCursor(10, 40);
  display.println("Poziom wody");
  display.setCursor(0, (select));
  display.println(">");
  display.display();
  
  //  Wybory
  if(STAN2 == LOW) {
  display.clearDisplay();
  
  while(select == 10) {
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Temperatura gleby to:");
    display.setTextSize(2);
    display.setCursor(40, 30);
    display.println(temp);
    display.setTextSize(1);
    display.setCursor(59, 25);
    display.println(" o");
    display.setTextSize(2);
    display.setCursor(60, 30);
    display.println(" C");
    display.display();
    int STAN5 = digitalRead(PIN_WYJDZ);
    if(STAN5 == LOW) {
      break;
    }
  }
  
  while(select == 20) {
    int STAN3 = digitalRead(PIN_ZMNIEJSZ);
    int STAN4 = digitalRead(PIN_ZWIEKSZ);
    if(STAN3 == LOW) {
      display.setCursor(112, 54);
      display.setTextColor(BLACK);
      display.println(poziom_wilgo);
      display.fillRect(7, 55, (poziom_wilgo), 6, SSD1306_BLACK);
      poziom_wilgo--;
      delay(200);
    }
    if(STAN4 == LOW) {
      display.setCursor(112, 54);
      display.setTextColor(BLACK);
      display.println(poziom_wilgo);
      poziom_wilgo++;
      delay(200);
    }
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Wilgotnosc gleby to");
    display.setTextSize(2);
    display.setCursor(40, 15);
    display.println(wilgo);
    display.setCursor(60, 15);
    display.println(" %");
    display.setTextSize(1);
    display.setCursor(0, 35);
    display.println("Automatyczne nawodnienie ponizej:");
    display.drawRect(5, 53, 104, 10, SSD1306_WHITE);
    display.setCursor(112, 54);
    display.println(poziom_wilgo);
    display.fillRect(7, 55, (poziom_wilgo), 6, SSD1306_WHITE);
    display.display();
    int STAN5 = digitalRead(PIN_WYJDZ);
    if(STAN5 == LOW) {
      break;
    }   
  }
  
while(select == 30) {
    int STAN3 = digitalRead(PIN_ZMNIEJSZ);
    int STAN4 = digitalRead(PIN_ZWIEKSZ);
    if(STAN3 == LOW) {
      display.setCursor(112, 54);
      display.setTextColor(BLACK);
      display.println(poziom_swia);
      display.fillRect(7, 55, (poziom_swia), 6, SSD1306_BLACK);
      poziom_swia--;
      delay(200);
    }
    if(STAN4 == LOW) {
      display.setCursor(112, 54);
      display.setTextColor(BLACK);
      display.println(poziom_swia);
      poziom_swia++;
      delay(200);
    }
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Poziom swiatla to");
    display.setTextSize(2);
    display.setCursor(40, 15);
    display.println(S1);
    display.setCursor(60, 15);
    display.println(" %");
    display.setTextSize(1);
    display.setCursor(0, 35);
    display.println("Automatyczne naswietlenie ponizej:");
    display.drawRect(5, 53, 104, 10, SSD1306_WHITE);
    display.setCursor(112, 54);
    display.println(poziom_swia);
    display.fillRect(7, 55, (poziom_swia), 6, SSD1306_WHITE);
    display.display();
    int STAN5 = digitalRead(PIN_WYJDZ);
    if(STAN5 == LOW) {
      break;
    }   
  }
  
while(select == 40) {
    int STAN3 = digitalRead(PIN_ZMNIEJSZ);
    int STAN4 = digitalRead(PIN_ZWIEKSZ);
    if(STAN3 == LOW) {
      display.setCursor(112, 54);
      display.setTextColor(BLACK);
      display.println(poziom_wody);
      display.fillRect(7, 55, (poziom_wody), 6, SSD1306_BLACK);
      poziom_wody--;
      delay(200);
    }
    if(STAN4 == LOW) {
      display.setCursor(112, 54);
      display.setTextColor(BLACK);
      display.println(poziom_wody);
      poziom_wody++;
      delay(200);
    }
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Poziom wody to");
    display.setTextSize(2);
    display.setCursor(40, 15);
    display.println("NA");
    display.setCursor(60, 15);
    display.println(" %");
    display.setTextSize(1);
    display.setCursor(0, 35);
    display.println("Automatyczne dolanie ponizej:");
    display.drawRect(5, 53, 104, 10, SSD1306_WHITE);
    display.setCursor(112, 54);
    display.println(poziom_wody);
    display.fillRect(7, 55, (poziom_wody), 6, SSD1306_WHITE);
    display.display();
    int STAN5 = digitalRead(PIN_WYJDZ);
    if(STAN5 == LOW) {
      break;
    }   
  }
} 

}
