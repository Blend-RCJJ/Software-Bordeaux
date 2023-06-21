#ifndef _RTOS_IO_H_
#define _RTOS_IO_H_

#include "../device/device.h"
#include "../kit/RTOS-Kit.h"

#include "./algorithm/victim.h"
#include "../device/device.h"

extern RTOS_Kit app;

const int period = 10;  // 制御周期

extern int robotStatus;

void sensorApp(App) {
    while (1) {
        ui.read();
        gyro.read();
        tof.read();
        tof.calc(gyro.deg);
        // camera.read(); //FIXME: ポインタの設定違う
        loadcell.read();
        floorSensor.read();

        app.delay(period);
    }
}

void servoApp(App) {
    while (1) {
        if (!servo.suspend) {
            if (servo.isAngleCorrectionEnabled) {
                servo.drive(servo.velocity,
                            servo.angle + servo.isCorrectingAngle);
            } else {
                servo.driveAngularVelocity(servo.velocity,
                                           servo.angularVelocity);
            }
        } else {
            servo.stop();
        }

        app.delay(period);
    }
}

double mapDouble(double x, double in_min, double in_max, double out_min,
                 double out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void ledApp(App) {
    unsigned long startTime = millis();
    while (1) {
        if (victim.isDetected) {
            unsigned long color = victim.color[victim.id];
            unsigned long victimTime = millis();

            while (victim.isDetected) {
                int brightness = 255 - ((millis() - victimTime) / 4) % 255;

                for (int i = 0; i < 4; i++) {
                    led.setColor(i, color);
                    led.setBrightness(i, brightness);
                }
                led.showAll();
                app.delay(15);
            }
        } else {
            int amplitude = 100;
            int period = 5000;

            int brightness =
                mapDouble(cos((millis() - startTime) * 2 * PI / period), -1, 1,
                          255 - amplitude, 255);

            for (int i = 0; i < 4; i++) {
                led.setColor(i, led.cyan);
                led.setBrightness(i, brightness);
            }
            if (loadcell.status != 0) {
                led.setColorBar(loadcell.moment, led.white);
            }
            led.showAll();
        }
        app.delay(10);
    }
}

#endif