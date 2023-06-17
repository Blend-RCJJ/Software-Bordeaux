#ifndef _FLOOR_SENSOR_H_
#define _FLOOR_SENSOR_H_

#include <Adafruit_NeoPixel.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <EEPROM.h>
#include <SPI.h>
#include <Wire.h>

class FLOOR_SENSOR {
   public:
    const int brightness = 255;
    int redVal;
    int greenVal;
    int blueVal;

    unsigned long colorRGB(int red, int green, int blue);
    unsigned long colorHSV(int hue, int saturation, int brightness);

    unsigned long red   = colorHSV(0, 255, 255);
    unsigned long green = colorHSV(90, 255, 255);
    unsigned long blue  = colorHSV(180, 255, 255);
    unsigned long white = colorRGB(255, 255, 255);
    unsigned long blank = colorRGB(0, 0, 0);

    bool isRed   = false;
    bool isGreen = false;
    bool isBlue  = false;
    bool isBlack = false;
    bool isWhite = false;

    void init(void);

    void read(void) {
        redVal   = analogRead(PC0);
        greenVal = analogRead(PC0);
        blueVal  = analogRead(PC0);
        // FIXME: 未実装
    };

    void setFloorColor(unsigned long color);
    void colorJudgment(void);

   private:
};

#endif