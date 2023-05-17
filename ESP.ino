#define REMOTEXY_MODE__ESP8266_HARDSERIAL_POINT

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 115200
#define REMOTEXY_WIFI_SSID ""
#define REMOTEXY_WIFI_PASSWORD ""
#define REMOTEXY_SERVER_PORT 6377


#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 55 bytes
  { 255,5,0,0,0,48,0,16,31,1,1,0,30,11,12,12,2,31,0,1,
  0,44,11,12,12,2,31,0,1,0,18,35,12,12,2,31,0,1,0,8,
  7,12,12,2,31,0,1,0,31,35,12,12,2,31,0 };
  
struct {
  uint8_t Wejdz; // =1 if button pressed, else =0 
  uint8_t Wyjdz; // =1 if button pressed, else =0 
  uint8_t Zmniejsz; // =1 if button pressed, else =0 
  uint8_t Dalej; // =1 if button pressed, else =0 
  uint8_t Zwieksz; // =1 if button pressed, else =0 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

#define PIN_WEJDZ 5
#define PIN_WYJDZ 8
#define PIN_ZMNIEJSZ 6
#define PIN_DALEJ 4
#define PIN_ZWIEKSZ 7


void setup() 
{
  RemoteXY_Init (); 
  
  pinMode (PIN_WEJDZ, OUTPUT);
  pinMode (PIN_WYJDZ, OUTPUT);
  pinMode (PIN_ZMNIEJSZ, OUTPUT);
  pinMode (PIN_DALEJ, OUTPUT);
  pinMode (PIN_ZWIEKSZ, OUTPUT);  
}

void loop() 
{ 
  RemoteXY_Handler ();
  
  digitalWrite(PIN_WEJDZ, (RemoteXY.Wejdz==0)?LOW:HIGH);
  digitalWrite(PIN_WYJDZ, (RemoteXY.Wyjdz==0)?LOW:HIGH);
  digitalWrite(PIN_ZMNIEJSZ, (RemoteXY.Zmniejsz==0)?LOW:HIGH);
  digitalWrite(PIN_DALEJ, (RemoteXY.Dalej==0)?LOW:HIGH);
  digitalWrite(PIN_ZWIEKSZ, (RemoteXY.Zwieksz==0)?LOW:HIGH);
}
