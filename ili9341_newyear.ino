#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

// Other shields:
#define TFT_MISO 12
#define TFT_MOSI 11
#define TFT_CLK 13
#define TFT_RST 8

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  Serial.println("ILI9341 - New Year Tree!");
  tft.begin();
  drawTree();
  drawText();
}


void loop(void) {
  drawDecor();
}

void drawTree() {
  tft.fillScreen(ILI9341_BLACK);
  int w = tft.width(), h = tft.height();
  uint16_t woodColor = 0x8208;
  uint16_t treeColor = ILI9341_GREEN;
  uint16_t starColor = ILI9341_WHITE;
  uint8_t t_count = 3;

  // wood
  tft.fillTriangle(w / 2, 0, w / 3, h, 2 * w / 3, h, woodColor);

  // tree
  uint8_t t_height = h / (t_count + 2); // 2 - top and bottom margins
  for (uint8_t ts = 0; ts < t_count; ts++) {
    uint16_t t_top = t_height * (ts + 1);
    uint8_t t_hmargin = (t_count - (ts + 1)) * (w / 6);
    tft.fillTriangle(
      w / 2, t_top,
      t_hmargin, t_top + t_height,
      w - t_hmargin, t_top + t_height,
      treeColor
    );
  }

  // star
  uint8_t s_width = t_height;
  uint8_t s_height = t_height / 3;
  tft.fillTriangle(
    w / 2, 0,
    w / 2 - s_height, s_width,
    w / 2, s_width / 2,
    starColor
  );
  tft.fillTriangle(
    w / 2, 0,
    w / 2 + s_height, s_width,
    w / 2, s_width / 2,
    starColor
  );
  tft.fillTriangle(
    w / 2 - s_width / 2, s_width / 3,
    w / 2 + s_width / 2, s_width / 3,
    w / 2, s_width / 2,
    starColor
  );
}

void drawText() {
  uint8_t font1_width = 6;
  uint8_t font1_height = 7;
  uint8_t font3_width = 6 * 3;

  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.println("Programmer's\nnew year tree");

  String year = "2016";
  tft.setCursor(tft.width() - year.length() * font3_width, 0);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(3);
  tft.println(year);

  String profi = "Profi";
  tft.setCursor(tft.width() / 2 - (font1_width * profi.length() / 2), tft.height() - font1_height);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.println(profi);
}

void drawDecor() {
  uint16_t colors[] = {
    0x001F,
    0xF800,
    0x07FF,
    0xF81F,
    0xFFE0
  };
  long level = random(0, 3);
  long side = random(0, 2);
  long color = random(0, 5);

  uint8_t b_r = 5 * (level + 1);
  uint16_t b_x = (tft.width() / 6) * (2 - level) + b_r * 1.3;
  if (side == 1) {
    b_x = tft.width() - b_x;
  }
  uint16_t b_y = (tft.height() / 5) * (2 + level) + b_r;

  for (uint8_t r = 0; r <= b_r; r++) {
    tft.drawCircle(b_x, b_y, r, colors[color]);
    delay(100);
  }
  //delay(1000);
}
