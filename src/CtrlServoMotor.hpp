#ifndef CTRLSERVOMOTOR_H_
#define CTRLSERVOMOTOR_H_

#include <ServoEasing.hpp>

namespace MyStackChan {
  class CtrlServoMotor {
    private:
      ServoEasing m_servoX;
      ServoEasing m_servoY;
      int m_offsetX;
      int m_offsetY;
    public:
      CtrlServoMotor(){ 
        m_servoX = ServoEasing();
        m_servoY = ServoEasing();
      }

      bool initialize(int pinX, int pinY, int offsetX, int offsetY){
        m_offsetX = offsetX;
        m_offsetY = offsetY;
        if(m_servoX.attach(pinX,
                           90 + m_offsetX, 
                           DEFAULT_MICROSECONDS_FOR_0_DEGREE,
                           DEFAULT_MICROSECONDS_FOR_180_DEGREE) == false) {
          Serial.println("Fail:ServoX Attach");
          return false;
        }
        if(m_servoY.attach(pinY,
                           90 + m_offsetY,
                           DEFAULT_MICROSECONDS_FOR_0_DEGREE,
                           DEFAULT_MICROSECONDS_FOR_180_DEGREE) == false) {
          Serial.println("Fail:ServoY Attach");
          return false;
        }

        return true;
      }

      void moveX_nonBlocking(int x, uint32_t deg_per_sec = 30) {
        m_servoX.setEaseTo(x + m_offsetX, deg_per_sec);
      }

      void moveY_nonBlocking(int y, uint32_t deg_per_sec = 30) {
        m_servoY.setEaseTo(y + m_offsetY, deg_per_sec);
      }

      void stopX() {
        m_servoX.stop();
      }

      void stopY() {
        m_servoY.stop();
      }
  };
}

#endif
