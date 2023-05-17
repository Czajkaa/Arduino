#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define BLYNK_AUTH_TOKEN ""
#define ONE_WIRE_BUS 9
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int Woda = 0;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "";
char pass[] = "";

BLYNK_WRITE(V0) {
  digitalWrite(4, param.asInt());
}


void setup() {
  sensors.begin();
  
  pinMode(4, OUTPUT);
  pinMode(10, INPUT_PULLUP);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void loop() {
  sensors.requestTemperatures();
  int Czujnik_Switala = analogRead(A0);
  int Czujnik_wody = digitalRead(10);
  int Swiatlo = (1024-Czujnik_Switala)/10;
  Blynk.virtualWrite(V1, sensors.getTempCByIndex(0));
  //Blynk.virtualWrite(V2, Wilgotnosc);
  Blynk.virtualWrite(V3, Swiatlo);
  Blynk.virtualWrite(V4, Czujnik_wody);

  Blynk.run();
  delay(10);
}
