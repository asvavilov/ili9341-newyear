# ili9341-newyear
Programmer's new year tree. #arduino #tft #spi #ili9341

![Programmer's new year tree](https://lh3.googleusercontent.com/8qTfGrDSoEfEybgf1mEX7VETTUTImvcofhVE-DJ7NfCxfkrJqhA2hLhRzttEYxen5Mdjpg=w2400-h1350-no)

Required libs:
- https://github.com/adafruit/Adafruit_ILI9341
- https://github.com/adafruit/Adafruit-GFX-Library

# Connect

See code

VCC, LED - 5/3.3v (see display spec.)

3.3v: CS, RESET, MOSI (SDO), SCK

3.3v or compatible with 5v: MISO (SDI)

TODO need check some pins - 3.3v or compatible with 5v (for economy of level shifters)
