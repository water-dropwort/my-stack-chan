#ifndef CUSTOMFACE_H_
#define CUSTOMFACE_H_

#include <Face.h>
#include <Mouth.h>
#include <BoundingRect.h>
#include <Eyeblow.h>
#include "EllipseEye.h"
#include "TarakoMouth.h"

namespace MyStackChan {
  using namespace m5avatar;
  
  class CustomFace : public Face {
    public:
      CustomFace()
        : Face(new TarakoMouth(TFT_VIOLET, TFT_SKYBLUE), 
               new BoundingRect(120, 80, 160, 96),
               new EllipseEye(20, 8, false, TFT_WHITE, TFT_BLACK),
               new BoundingRect(93, 90), 
               new EllipseEye(20, 8, true , TFT_WHITE, TFT_BLACK),
               new BoundingRect(96, 230), 
               new Eyeblow(32, 0, false),
               new BoundingRect(67, 96), 
               new Eyeblow(32, 0, true),
               new BoundingRect(72, 230)) {}

  }; // end of CustomFace class
} // end of namespace

#endif
