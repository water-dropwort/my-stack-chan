#include <M5Unified.h>
#include <Avatar.h>
#include <ColorPalette.h>
#include "CustomFace.h"
#include "StackChanRemoteReceiver.hpp"
#include <ServoEasing.hpp>

#define SERVO_PIN_X 33
#define SERVO_PIN_Y 32
#define SERVO_X_OFFSET -13
#define SERVO_Y_OFFSET 4
#define SERVO_X_MIN 0
#define SERVO_X_MAX 180
#define SERVO_Y_MIN 60
#define SERVO_Y_MAX 100
#define SERVO_X_DEG_PER_SEC 30
#define SERVO_Y_DEG_PER_SEC 30

using namespace m5avatar;
using namespace MyStackChan;

Avatar avatar;
ServoEasing g_servoX;
ServoEasing g_servoY;
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

  if(false == g_servoX.attach(SERVO_PIN_X, 
                              90 + SERVO_X_OFFSET, 
                              DEFAULT_MICROSECONDS_FOR_0_DEGREE,
                              DEFAULT_MICROSECONDS_FOR_180_DEGREE)) {
    Serial.println("Fail:ServoX attach");
  }
  if(false == g_servoY.attach(SERVO_PIN_Y,
                              90 + SERVO_Y_OFFSET,
                              DEFAULT_MICROSECONDS_FOR_0_DEGREE,
                              DEFAULT_MICROSECONDS_FOR_180_DEGREE)) {
    Serial.println("Fail:ServoY attach");
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
    if(1 == (command & 0x1)) {
      avatar.setMouthOpenRatio(1.0f);
    }
    else {
      avatar.setMouthOpenRatio(0.0f);
    }

    int x = (command & 0x6) >> 1;
    if(x != g_pre_servoX_command) {
      if(x == 1) {
        g_servoX.setEaseTo(SERVO_X_MIN + SERVO_X_OFFSET, SERVO_X_DEG_PER_SEC);
      }
      else if(x == 2) {
        g_servoX.setEaseTo(SERVO_X_MAX + SERVO_X_OFFSET, SERVO_X_DEG_PER_SEC);
      }
      else {
        g_servoX.stop();
      }
    }
    g_pre_servoX_command = x;

    int y = (command & 0b00011000) >> 3;
    if(y != g_pre_servoY_command) {
      if(y == 1) {
        g_servoY.setEaseTo(SERVO_Y_MIN + SERVO_Y_OFFSET, SERVO_Y_DEG_PER_SEC);
      }
      else if(y == 2) {
        g_servoY.setEaseTo(SERVO_Y_MAX + SERVO_Y_OFFSET, SERVO_Y_DEG_PER_SEC);
      }
      else {
        g_servoY.stop();
      }
    }
    g_pre_servoY_command = y;
    synchronizeAllServosAndStartInterrupt();
  }

  delay(30);
  M5.update();
}

