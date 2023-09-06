#ifndef ELLIPSEEYE_H_
#define ELLIPSEEYE_H_

#include <Drawable.h>
#include <BoundingRect.h>
#include <DrawContext.h>
#include <M5Unified.h>

namespace MyStackChan {
  using namespace m5avatar;

  class EllipseEye : public Drawable {
    private:
      uint32_t m_rx;
      uint32_t m_ry;
      bool m_isLeft;
      bool m_isSpecifiedColor;
      uint16_t m_c_eye;
      uint16_t m_c_frame;
      
    public:
      EllipseEye(uint32_t rx, uint32_t ry, bool isLeft) {
        m_rx = rx;
        m_ry = ry;
        m_isLeft = isLeft;
        m_isSpecifiedColor = false;
      }

      EllipseEye(uint32_t rx, uint32_t ry, bool isLeft, uint16_t c_eye, uint16_t c_frame) {
        m_rx = rx;
        m_ry = ry;
        m_isLeft = isLeft;
        m_isSpecifiedColor = true;
        m_c_eye = c_eye;
        m_c_frame = c_frame;
      }

      void draw(M5Canvas *spi, BoundingRect rect, DrawContext *ctx) {
        uint32_t x = rect.getCenterX();
        uint32_t y = rect.getCenterY();
        uint16_t c_eye = 1;
        uint16_t c_frame = 0;
        if(ctx->getColorDepth() != 1) {
          c_eye   = m_isSpecifiedColor ? m_c_eye   : ctx->getColorPalette()->get(COLOR_PRIMARY);
          c_frame = m_isSpecifiedColor ? m_c_frame : ctx->getColorPalette()->get(COLOR_BACKGROUND);
        } 
        
        if(ctx->getEyeOpenRatio() > 0.5) {
          spi->fillEllipse(x, y, m_rx, m_ry, c_eye);
          spi->drawEllipse(x, y, m_rx, m_ry, c_frame);
        }
        else {
          spi->fillRect(x - m_rx, y, m_rx * 2, 2, c_frame);
        }
      }
  }; // end of EllipseEye class
} // end of namespace

#endif
