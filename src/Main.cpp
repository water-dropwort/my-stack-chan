#include <M5Unified.h>
#include <Avatar.h>
#include <ColorPalette.h>
#include "CustomFace.h"
#include "CtrlServoMotor.hpp"
#include "StackChanRemoteReceiver.hpp"

#define SERVO_PIN_X 33
#define SERVO_PIN_Y 32

using namespace m5avatar;
using namespace MyStackChan;

Avatar avatar;
CtrlServoMotor ctrlServoMotor;
int openLevel = 0;
int maxOpenLevel = 4;
int g_pre_servoX_command = 0;
int g_pre_servoY_command = 0;

StackChanRemoteReceiver* g_stackChanRemoteReceiver = nullptr;

void setup()
{
  M5.begin();
  M5.Lcd.setBrightness(50);

  Serial.begin(115200);

  if(!ctrlServoMotor.initialize(SERVO_PIN_X, SERVO_PIN_Y, -13, 4)) {
    Serial.println("ERR: Failed to initialize the motor controller.");
  }

  ColorPalette cp;
  cp.set(COLOR_PRIMARY,          TFT_BLACK);
  cp.set(COLOR_BACKGROUND,       TFT_OLIVE);

  avatar.setColorPalette(cp);
  avatar.setFace(new CustomFace());
  avatar.setMouthOpenRatio(0);

  avatar.init(16);

  g_stackChanRemoteReceiver = new StackChanRemoteReceiver();
  g_stackChanRemoteReceiver->scan();
}

void loop()
{
  if(M5.BtnA.wasPressed() 
     && g_stackChanRemoteReceiver->controllerFound() == false) {
    Serial.println("Button A pressed.");
    g_stackChanRemoteReceiver->scan();
  }

  if(g_stackChanRemoteReceiver->isConnected() == false) {
    if(g_stackChanRemoteReceiver->controllerFound()) {
      g_stackChanRemoteReceiver->connect();
    }
  }
  else {
    uint32_t command = g_stackChanRemoteReceiver->readCommand();
    if(1 == command & 0x1) {
      avatar.setMouthOpenRatio(1.0f);
    }
    else {
      avatar.setMouthOpenRatio(0.0f);
    }

    int x = (command & 0x6) >> 1;
    if(x != g_pre_servoX_command) {
      if(x == 1) {
        ctrlServoMotor.moveX_nonBlocking(0);
      }
      else if(x == 2) {
        ctrlServoMotor.moveX_nonBlocking(180);
      }
      else {
        ctrlServoMotor.stopX();
      }
    }
    g_pre_servoX_command = x;

    int y = (command & 0b00011000) >> 3;
    if(y != g_pre_servoY_command) {
      if(y == 1) {
        ctrlServoMotor.moveY_nonBlocking(0);
      }
      else if(y == 2) {
        ctrlServoMotor.moveY_nonBlocking(180);
      }
      else {
        ctrlServoMotor.stopY();
      }
    }
    g_pre_servoY_command = y;
    synchronizeAllServosAndStartInterrupt();
  }

  delay(30);
  M5.update();
}

