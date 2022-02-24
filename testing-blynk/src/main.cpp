#include <Arduino.h>
#include <NetworkSetting.h>
#include <string.h>
#include <VescUart.h>

#define BLYNK_PRINT Serial // Defines the object that is used for printing
#define BLYNK_DEBUG        // Optional, this enables more detailed prints
VescUart UART;

#define RX0 9
#define TX0 10

int state_fo = 0;
int state_ho = 0;
int state_po = 0;
int state_fc = 0;

// This function is called to reading IR state
void bacaIR(){
  int state_hardware = 0;
  int state_software = 0;

  if(digitalRead(5) == 0){
    if(state_hardware != 0){
      state_software = !state_software;
      Blynk.virtualWrite(V4, state_software);
      if(state_software == 1){
        Serial.println("Gate_Terbuka");
        digitalWrite(2, HIGH);
        UART.gateOpenFull();
      }
      if(state_software == 0){
        Serial.println("Gate_Tertutup");
        digitalWrite(2, LOW);
        UART.gateClose();
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
    state_fo = !state_fo;
    Blynk.virtualWrite(V4, 1);
    if(state_fo == 1){
      Serial.println("Gate_Full");
      digitalWrite(2, HIGH);
      UART.gateOpenFull();
      state_fo = 0;
    }
  }
}

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V1)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  if(value == 1){
    state_ho = !state_ho;
    Blynk.virtualWrite(V4, 1);
    if(state_ho == 1){
      Serial.println("Gate_Half");
      digitalWrite(2, HIGH);
      UART.gateOpenHalf();
      state_ho = 0;
    }
  }
}

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V2)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  if(value == 1){
    state_po = !state_po;
    Blynk.virtualWrite(V4, 1);
    if(state_po == 1){
      Serial.println("Gate_People");
      digitalWrite(2, HIGH);
      UART.gateOpenPeople();
      state_po = 0;
    }
  }
}

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V3)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  if(value == 1){
    state_fc = !state_fc;
    Blynk.virtualWrite(V4, 0);
    if(state_fc == 1){
      Serial.println("Gate_Close");
      digitalWrite(2, LOW);
      UART.gateClose();
      state_fc = 0;
    }
  }
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, RX0, TX0);
  
  // IR
  pinMode(5, INPUT_PULLUP);
  
  // Push Button
  pinMode(23, INPUT_PULLUP);
  pinMode(22, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  
  // LED Log
  pinMode(2, OUTPUT);

  // Set UART Vesc
  UART.setSerialPort(&Serial1);

  Blynk.begin(auth, ssid, pass);

  // Set to 0
  Blynk.virtualWrite(V0,0);
  Blynk.virtualWrite(V1,0);
  Blynk.virtualWrite(V4,0);
}

void loop()
{
  Blynk.run();
  bacaIR();
  // bacaPB();
}