// SƠ ĐỒ CHÂN
// LED  ESP32
// 1,7  3.3V
// 2,8  GND
// 3    17
// 4    16
// 5    15
// 6    14

#include <Arduino.h>
#include <LovyanGFX.hpp>
#include "all_frames.h"

// --- CẤU HÌNH PHẦN CỨNG (GIỮ NGUYÊN CODE CŨ CỦA BẠN ĐOẠN NÀY) ---
class LGFX : public lgfx::LGFX_Device {
  lgfx::Panel_ST7735S _panel_instance;
  lgfx::Bus_SPI       _bus_instance;

public:
  LGFX(void) {
    {
      auto cfg = _bus_instance.config();
      cfg.spi_host = SPI2_HOST;
      cfg.spi_mode = 0;
      cfg.freq_write = 10000000; // 10MHz
      cfg.freq_read  = 10000000;
      
      cfg.pin_mosi = 15;
      cfg.pin_miso = -1;
      cfg.pin_sclk = 14;
      cfg.pin_dc   = 16; //21
      
      _bus_instance.config(cfg);
      _panel_instance.setBus(&_bus_instance);
    }

    {
      auto cfg = _panel_instance.config();
      cfg.pin_cs   = 13;
      cfg.pin_rst  = 17; //48
      cfg.pin_busy = -1;
      cfg.panel_width  = 80;
      cfg.panel_height = 160;
      
      // OFFSET CHUẨN CỦA BẠN ĐÂY
      cfg.offset_x     = 26; 
      cfg.offset_y     = 1;

      cfg.offset_rotation = 0;
      cfg.dummy_read_pixel = 8;
      cfg.dummy_read_bits  = 1;
      cfg.readable         = true;
      cfg.invert           = true; 
      cfg.rgb_order        = false; 

      _panel_instance.config(cfg);
    }
    setPanel(&_panel_instance);
  }
};

LGFX tft;
LGFX_Sprite sprite(&tft); // Tạo Sprite

// --- HÀM TẠO MÀU CẦU VỒNG (Fix lỗi color565) ---
uint16_t getRainbowColor(uint8_t hue) {
  uint8_t r, g, b;
  uint8_t region = hue / 43;
  uint8_t remainder = (hue - (region * 43)) * 6; 

  uint8_t p = 0;
  uint8_t q = 255 - remainder;
  uint8_t t = remainder;

  switch (region) {
    case 0: r = 255; g = t; b = 0; break;
    case 1: r = q; g = 255; b = 0; break;
    case 2: r = 0; g = 255; b = t; break;
    case 3: r = 0; g = q; b = 255; break;
    case 4: r = t; g = 0; b = 255; break;
    default: r = 255; g = 0; b = q; break;
  }
  
  // Trả về màu 16-bit chuẩn 565
  return tft.color565(r, g, b);
}

void setup() {
  Serial.begin(115200);
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  tft.setSwapBytes(true);

  // Tạo giấy nháp 128x64
  sprite.createSprite(128, 64);
  
  Serial.println("Rainbow Dasai Mochi Started!");
}

void loop() {
  static int currentFrame = 0;
  static uint8_t hue = 0; 

  // 1. Lấy màu cầu vồng (Fix lỗi 1)
  uint16_t rainbowColor = getRainbowColor(hue);

  // 2. Vẽ lên Sprite (Fix lỗi 2: Ép kiểu TFT_BLACK thành uint16_t)
  sprite.drawBitmap(0, 0, (const uint8_t*)frames[currentFrame], 128, 64, rainbowColor, (uint16_t)TFT_BLACK);

  // 3. Phóng to ra màn hình
  sprite.pushRotateZoom(80, 40, 0, 1.25, 1.25);

  currentFrame++;
  if (currentFrame >= TOTAL_FRAMES) {
    currentFrame = 0;
  }
  
  hue += 2; // Tăng tốc độ đổi màu
  delay(30); 
}