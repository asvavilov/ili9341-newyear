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
  /*for(uint8_t rotation=0; rotation<4; rotation++) {
    tft.setRotation(rotation);
    testText();
    delay(1000);
    }*/
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

unsigned long testText() {
  tft.fillScreen(ILI9341_BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 0);

  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(3);
  tft.println("Hello World!");

  tft.setTextSize(5);
  tft.println();

  tft.setTextColor(ILI9341_BLUE);
  tft.setTextSize(2);
  tft.println("Test display.");

  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(1);
  tft.println("SPI, ILI9341");

  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println();
  tft.print("Size: ");
  tft.print(tft.width());
  tft.print("x");
  tft.print(tft.height());
  tft.println();

  tft.setTextSize(5);
  tft.println();

  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(3);
  tft.println("asvavilov");
  tft.setTextSize(2);
  tft.println("2015-12-12");

  return micros() - start;
}

unsigned long testLines(uint16_t color) {
  unsigned long start, t;
  int           x1, y1, x2, y2,
                w = tft.width(),
                h = tft.height();

  tft.fillScreen(ILI9341_BLACK);

  x1 = y1 = 0;
  y2    = h - 1;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  t     = micros() - start; // fillScreen doesn't count against timing

  tft.fillScreen(ILI9341_BLACK);

  x1    = w - 1;
  y1    = 0;
  y2    = h - 1;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  tft.fillScreen(ILI9341_BLACK);

  x1    = 0;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  tft.fillScreen(ILI9341_BLACK);

  x1    = w - 1;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);

  return micros() - start;
}

unsigned long testFastLines(uint16_t color1, uint16_t color2) {
  unsigned long start;
  int           x, y, w = tft.width(), h = tft.height();

  tft.fillScreen(ILI9341_BLACK);
  start = micros();
  for (y = 0; y < h; y += 5) tft.drawFastHLine(0, y, w, color1);
  for (x = 0; x < w; x += 5) tft.drawFastVLine(x, 0, h, color2);

  return micros() - start;
}

unsigned long testRects(uint16_t color) {
  unsigned long start;
  int           n, i, i2,
                cx = tft.width()  / 2,
                cy = tft.height() / 2;

  tft.fillScreen(ILI9341_BLACK);
  n     = min(tft.width(), tft.height());
  start = micros();
  for (i = 2; i < n; i += 6) {
    i2 = i / 2;
    tft.drawRect(cx - i2, cy - i2, i, i, color);
  }

  return micros() - start;
}

unsigned long testFilledRects(uint16_t color1, uint16_t color2) {
  unsigned long start, t = 0;
  int           n, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  n = min(tft.width(), tft.height());
  for (i = n; i > 0; i -= 6) {
    i2    = i / 2;
    start = micros();
    tft.fillRect(cx - i2, cy - i2, i, i, color1);
    t    += micros() - start;
    // Outlines are not included in timing results
    tft.drawRect(cx - i2, cy - i2, i, i, color2);
  }

  return t;
}

unsigned long testFilledCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int x, y, w = tft.width(), h = tft.height(), r2 = radius * 2;

  tft.fillScreen(ILI9341_BLACK);
  start = micros();
  for (x = radius; x < w; x += r2) {
    for (y = radius; y < h; y += r2) {
      tft.fillCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int           x, y, r2 = radius * 2,
                      w = tft.width()  + radius,
                      h = tft.height() + radius;

  // Screen is not cleared for this one -- this is
  // intentional and does not affect the reported time.
  start = micros();
  for (x = 0; x < w; x += r2) {
    for (y = 0; y < h; y += r2) {
      tft.drawCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testTriangles() {
  unsigned long start;
  int           n, i, cx = tft.width()  / 2 - 1,
                      cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  n     = min(cx, cy);
  start = micros();
  for (i = 0; i < n; i += 5) {
    tft.drawTriangle(
      cx    , cy - i, // peak
      cx - i, cy + i, // bottom left
      cx + i, cy + i, // bottom right
      tft.color565(0, 0, i));
  }

  return micros() - start;
}

unsigned long testFilledTriangles() {
  unsigned long start, t = 0;
  int           i, cx = tft.width()  / 2 - 1,
                   cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  start = micros();
  for (i = min(cx, cy); i > 10; i -= 5) {
    start = micros();
    tft.fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
                     tft.color565(0, i, i));
    t += micros() - start;
    tft.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
                     tft.color565(i, i, 0));
  }

  return t;
}

unsigned long testRoundRects() {
  unsigned long start;
  int           w, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  w     = min(tft.width(), tft.height());
  start = micros();
  for (i = 0; i < w; i += 6) {
    i2 = i / 2;
    tft.drawRoundRect(cx - i2, cy - i2, i, i, i / 8, tft.color565(i, 0, 0));
  }

  return micros() - start;
}

unsigned long testFilledRoundRects() {
  unsigned long start;
  int           i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  start = micros();
  for (i = min(tft.width(), tft.height()); i > 20; i -= 6) {
    i2 = i / 2;
    tft.fillRoundRect(cx - i2, cy - i2, i, i, i / 8, tft.color565(0, i, 0));
  }

  return micros() - start;
}
