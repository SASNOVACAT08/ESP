#include <Arduino.h>
#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
  #error Bluetooth is not enabled! Please run make menuconfig to and enable it
#endif

const int nbL298N = 2;
const int enaL298NPin[2] = {13, 12};
const int rightL298NPin[2] = {25, 14};
const int leftL298NPin[2] = {27, 26};

bool isOn = false;

BluetoothSerial BT;

void forward() {
  digitalWrite(enaL298NPin[0], HIGH);
  digitalWrite(enaL298NPin[1], HIGH);
  analogWrite(rightL298NPin[1], 0);
  analogWrite(leftL298NPin[1], 0);
  for(int i = 0; i < 1000; i++) {
    analogWrite(rightL298NPin[0], i);
    analogWrite(leftL298NPin[0], i);
  }
  
}

void backward() {
  digitalWrite(enaL298NPin[0], HIGH);
  digitalWrite(enaL298NPin[1], HIGH);
  analogWrite(rightL298NPin[0], 0);
  analogWrite(leftL298NPin[0], 0);
  for(int i = 0; i < 100; i++) {
    analogWrite(rightL298NPin[1], i);
    analogWrite(leftL298NPin[1], i);
  }
}

void right() {
  digitalWrite(enaL298NPin[0], HIGH);
  digitalWrite(enaL298NPin[1], HIGH);
  analogWrite(rightL298NPin[0], 0);
  analogWrite(leftL298NPin[1], 0);
  for(int i = 0; i < 100; i++) {
    analogWrite(rightL298NPin[1], i);
    analogWrite(leftL298NPin[0], i);
  }
}

void left() {
  digitalWrite(enaL298NPin[0], HIGH);
  digitalWrite(enaL298NPin[1], HIGH);
  analogWrite(rightL298NPin[1], 0);
  analogWrite(leftL298NPin[0], 0);
  for(int i = 0; i < 100; i++) {
    analogWrite(rightL298NPin[0], i);
    analogWrite(leftL298NPin[1], i);
  }
}

void stop() {
  digitalWrite(enaL298NPin[0], LOW);
  digitalWrite(enaL298NPin[1], LOW);
}

void  setup()  {
  Serial.begin(9600);
  BT.begin("VROUM VROUUUM");
  for (int i = 0; i < nbL298N; i++) {
    pinMode(rightL298NPin[i], OUTPUT);
    pinMode(leftL298NPin[i], OUTPUT);
    pinMode(enaL298NPin[i], OUTPUT);
  }
}

void loop()  {
  // forward();
  if (BT.available()) // Check if we receive anything from Bluetooth
  {
    int incoming = BT.read(); // Read what we recevive 
    Serial.print("Received: ");
    Serial.println(incoming);
    if(incoming == 51){
      backward();
    } else if(incoming == 49){
      forward();
    } else if(incoming == 52){
      left();
    } else if(incoming == 50){
      right();
    } else if(incoming == 48){
      stop();
    }
  }
  delay(20);
}