#include <Arduino.h>
#include <NetworkSetting.h>
#include <string.h>

#define BLYNK_PRINT Serial // Defines the object that is used for printing
#define BLYNK_DEBUG        // Optional, this enables more detailed prints

int state_hardware = 0;
int state_software = 0;

void bacaPB(){
  if(digitalRead(5) == 0){
    if(state_hardware != 0){
      state_software = !state_software;
      Blynk.virtualWrite(V0, state_software);
      Blynk.virtualWrite(V4, state_software);
      if(state_software == 1){
        Serial.println("Gate_Terbuka");
      }
      if(state_software == 0){
        Serial.println("Gate_Tertutup");
      }
    }
    state_hardware = 0;
  }
  else{
    state_hardware = 1;
  }
}

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
    // Set incoming value from pin V0 to a variable
    int value = param.asInt();
    if(value == 1){
      Blynk.virtualWrite(V4, value);
      Serial.println("a");
    }
    else{
      Blynk.virtualWrite(V4, value);
      Serial.println("b");
    }
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(5, INPUT_PULLUP);
  Blynk.begin(auth, ssid, pass);

  // Set to 0
  Blynk.virtualWrite(V0,0);
  Blynk.virtualWrite(V1,0);
  Blynk.virtualWrite(V4,0);
}

void loop()
{
  Blynk.run();
  bacaPB();
}