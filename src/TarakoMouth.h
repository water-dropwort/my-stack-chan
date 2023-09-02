#ifndef TARAKOMOUTH_H_
#define TARAKOMOUTH_H_

#include <Drawable.h>
#include <BoundingRect.h>
#include <DrawContext.h>
#include <M5Unified.h>

namespace MyStackChan {
  using namespace m5avatar;

  class TarakoMouth : public Drawable {
    private:
      bool m_isSpecifiedColor;
      uint16_t m_c_lip;
      uint16_t m_c_mouth;

    public:
      TarakoMouth() { m_isSpecifiedColor = false; }

      TarakoMouth(uint16_t c_lip, uint16_t c_mouth) {
        m_isSpecifiedColor = true;
        m_c_lip = c_lip;
        m_c_mouth = c_mouth;
      }

      void draw(M5Canvas *spi, BoundingRect rect, DrawContext *ctx) {
        uint32_t l = rect.getLeft();
        uint32_t t = rect.getTop();
        uint32_t w = rect.getWidth();
        uint32_t h = rect.getHeight();
        uint32_t cx = rect.getCenterX();
        uint32_t cy = rect.getCenterY();
        uint16_t c_lip = 1;
        uint16_t c_mouth = 0;
        float openRatio = ctx->getMouthOpenRatio();
        
        if(ctx->getColorDepth() != 1) {
          c_lip   = m_isSpecifiedColor ? m_c_lip   : ctx->getColorPalette()->get(COLOR_SECONDARY);
          c_mouth = m_isSpecifiedColor ? m_c_mouth : ctx->getColorPalette()->get(COLOR_SECONDARY);
        }
        
        uint32_t lip_h = h * 0.2;
        uint32_t lip_r = lip_h * 0.5;
        uint32_t rect_h = (h - 2 * lip_h) * openRatio + lip_h;
        uint32_t rect_w = w * 0.95;
        uint32_t rect_x = l + w * 0.025;
        uint32_t rect_y = cy - 0.5 * rect_h;
        spi->fillRect(rect_x, rect_y, rect_w, rect_h, c_mouth);
        uint32_t lip_yu = cy - 0.5 * rect_h - 0.5 * lip_h;
        uint32_t lip_yl = cy + 0.5 * rect_h - 0.5 * lip_h;
        spi->fillRoundRect(l, lip_yu, w, lip_h, lip_r, c_lip);
        spi->fillRoundRect(l, lip_yl, w, lip_h, lip_r, c_lip);
      }
  };
}

#endif
