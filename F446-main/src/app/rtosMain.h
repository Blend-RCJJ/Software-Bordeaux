#ifndef _RTOS_MAIN_H_
#define _RTOS_MAIN_H_

#include "../device/device.h"
#include "../kit/RTOS-Kit.h"
#include "./rtosIO.h"
#include "./rtosLocation.h"
#include "./rtosVictim.h"

extern RTOS_Kit app;

#define SPEED 50
#define WAIT 500
#define FORWARD 2500
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define MAX_DISTANCE 800
#define FEEDBACK 300000  // 帰還開始時間(ms)

const int radius                                 = 20;
bool virtualWall[MAP_ORIGIN * 2][MAP_ORIGIN * 2] = {false};
bool isRightWallApp                              = false;
bool oldstatus                                   = false;
static int oldmillis                             = 0;
int checkPointX                                  = MAP_ORIGIN;
int checkPointY                                  = MAP_ORIGIN;
int checkPointWall[4]                            = {0};

void rightWallApp(App);
void leftWallApp(App);
void monitorApp(App);
void adjustmentApp(App);
void DepthFirstSearchApp(App);
void AstarApp(App);
void adjustmentApp(App);

void mainApp(App) {
    app.start(sensorApp);
    app.start(monitorApp);
    app.start(servoApp);
    app.start(rightWallApp);
    app.start(DepthFirstSearchApp);
    app.start(AstarApp);
    app.start(adjustmentApp);
    stripFloor.setBrightness(255);
    floorSensor.setFloorColor(floorSensor.red);
    stripFloor.show();
    while (1) {
        if (ui.toggle) {
            if (oldstatus) {
                app.start(rightWallApp);
                app.start(locationApp);
                oldstatus = false;
            }
        } else {
            app.stop(rightWallApp);
            app.stop(locationApp);

            servo.suspend = true;
            oldstatus     = true;
        }
        app.delay(period);
    }
}

void rightWallApp(App) {
    static bool DFS = false;
    app.delay(WAIT);
    while (1) {
        servo.velocity = SPEED;
        servo.suspend  = false;
        isRightWallApp = true;
        DFS            = false;
        app.delay(period);

        if (tof.val[0] < 130 && !gyro.slope) {  // 前に壁が来た時の処理
            oldmillis      = millis();
            checkPointX    = location.x;
            checkPointY    = location.y;
            DFS            = true;
            servo.velocity = 0;
            servo.suspend  = true;
            app.delay(WAIT);
            servo.suspend = false;
            servo.angle -= 90;
            app.delay(WAIT);
        }
        if (virtualWall[location.x + MAP_ORIGIN][location.y + MAP_ORIGIN + 1] &&
            gyro.North) {
            if (tof.isNotRight && !location
                                       .mapData[location.x + MAP_ORIGIN + 1]
                                               [location.y + MAP_ORIGIN]
                                       .isPassed) {
                oldmillis      = millis();
                checkPointX    = location.x;
                checkPointY    = location.y;
                DFS            = true;
                servo.velocity = 0;
                servo.suspend  = true;
                app.delay(WAIT);
                servo.suspend = false;
                servo.angle += 90;
                app.delay(WAIT);
                servo.velocity = SPEED;
                app.delay(FORWARD);
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
            } else if (tof.isNotLeft &&
                       !location
                            .mapData[location.x + MAP_ORIGIN - 1]
                                    [location.y + MAP_ORIGIN]
                            .isPassed) {
                oldmillis      = millis();
                checkPointX    = location.x;
                checkPointY    = location.y;
                DFS            = true;
                servo.velocity = 0;
                servo.suspend  = true;
                app.delay(WAIT);
                servo.suspend = false;
                servo.angle -= 90;
                app.delay(WAIT);
                servo.velocity = SPEED;
                app.delay(FORWARD);
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
            } else {
                app.delay(period);
            }
        } else if (virtualWall[location.x + MAP_ORIGIN]
                              [location.y + MAP_ORIGIN - 1] &&
                   gyro.South) {
            if (tof.isNotRight && !location
                                       .mapData[location.x + MAP_ORIGIN - 1]
                                               [location.y + MAP_ORIGIN]
                                       .isPassed) {
                oldmillis      = millis();
                checkPointX    = location.x;
                checkPointY    = location.y;
                DFS            = true;
                servo.velocity = 0;
                servo.suspend  = true;
                app.delay(WAIT);
                servo.suspend = false;
                servo.angle += 90;
                app.delay(WAIT);
                servo.velocity = SPEED;
                app.delay(FORWARD);
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
            } else if (tof.isNotLeft &&
                       !location
                            .mapData[location.x + MAP_ORIGIN + 1]
                                    [location.y + MAP_ORIGIN]
                            .isPassed) {
                oldmillis      = millis();
                checkPointX    = location.x;
                checkPointY    = location.y;
                DFS            = true;
                servo.velocity = 0;
                servo.suspend  = true;
                app.delay(WAIT);
                servo.suspend = false;
                servo.angle -= 90;
                app.delay(WAIT);
                servo.velocity = SPEED;
                app.delay(FORWARD);
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
            } else {
                app.delay(period);
            }
        } else if (virtualWall[location.x + MAP_ORIGIN + 1]
                              [location.y + MAP_ORIGIN] &&
                   gyro.East) {
            if (tof.isNotRight && !location
                                       .mapData[location.x + MAP_ORIGIN]
                                               [location.y + MAP_ORIGIN - 1]
                                       .isPassed) {
                oldmillis      = millis();
                checkPointX    = location.x;
                checkPointY    = location.y;
                DFS            = true;
                servo.velocity = 0;
                servo.suspend  = true;
                app.delay(WAIT);
                servo.suspend = false;
                servo.angle += 90;
                app.delay(WAIT);
                servo.velocity = SPEED;
                app.delay(FORWARD);
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
            } else if (tof.isNotLeft &&
                       !location
                            .mapData[location.x + MAP_ORIGIN]
                                    [location.y + MAP_ORIGIN + 1]
                            .isPassed) {
                oldmillis      = millis();
                checkPointX    = location.x;
                checkPointY    = location.y;
                DFS            = true;
                servo.velocity = 0;
                servo.suspend  = true;
                app.delay(WAIT);
                servo.suspend = false;
                servo.angle -= 90;
                app.delay(WAIT);
                servo.velocity = SPEED;
                app.delay(FORWARD);
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
            } else {
                app.delay(period);
            }
        } else if (virtualWall[location.x + MAP_ORIGIN - 1]
                              [location.y + MAP_ORIGIN] &&
                   gyro.West) {
            if (tof.isNotRight && !location
                                       .mapData[location.x + MAP_ORIGIN]
                                               [location.y + MAP_ORIGIN + 1]
                                       .isPassed) {
                oldmillis      = millis();
                checkPointX    = location.x;
                checkPointY    = location.y;
                DFS            = true;
                servo.velocity = 0;
                servo.suspend  = true;
                app.delay(WAIT);
                servo.suspend = false;
                servo.angle += 90;
                app.delay(WAIT);
                servo.velocity = SPEED;
                app.delay(FORWARD);
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;

            } else if (tof.isNotLeft &&
                       !location
                            .mapData[location.x + MAP_ORIGIN]
                                    [location.y + MAP_ORIGIN - 1]
                            .isPassed) {
                oldmillis      = millis();
                checkPointX    = location.x;
                checkPointY    = location.y;
                DFS            = true;
                servo.velocity = 0;
                servo.suspend  = true;
                app.delay(WAIT);
                servo.suspend = false;
                servo.angle -= 90;
                app.delay(WAIT);
                servo.velocity = SPEED;
                app.delay(FORWARD);
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
            } else {
                app.delay(period);
            }
        } else if (!virtualWall[location.x + MAP_ORIGIN]
                               [location.y + MAP_ORIGIN + 1] &&
                   gyro.North &&
                   (virtualWall[location.x + MAP_ORIGIN - 1]
                               [location.y + MAP_ORIGIN] ||
                    tof.isWestWall) &&
                   (virtualWall[location.x + MAP_ORIGIN + 1]
                               [location.y + MAP_ORIGIN] ||
                    tof.isEastWall) &&
                   (virtualWall[location.x + MAP_ORIGIN]
                               [location.y + MAP_ORIGIN - 1] ||
                    tof.isSouthWall)) {
            if (!tof.isNorthWall) {
                oldmillis      = millis();
                checkPointX    = location.x;
                checkPointY    = location.y;
                DFS            = true;
                servo.velocity = SPEED;
                app.delay(1500);
            }
        } else if (!virtualWall[location.x + MAP_ORIGIN]
                               [location.y + MAP_ORIGIN - 1] &&
                   gyro.South &&
                   (virtualWall[location.x + MAP_ORIGIN + 1]
                               [location.y + MAP_ORIGIN] ||
                    tof.isEastWall) &&
                   (virtualWall[location.x + MAP_ORIGIN - 1]
                               [location.y + MAP_ORIGIN] ||
                    tof.isWestWall) &&
                   (virtualWall[location.x + MAP_ORIGIN]
                               [location.y + MAP_ORIGIN + 1] ||
                    tof.isNorthWall)) {
            if (!tof.isSouthWall) {
                oldmillis      = millis();
                checkPointX    = location.x;
                checkPointY    = location.y;
                DFS            = true;
                servo.velocity = SPEED;
                app.delay(1500);
            }
        } else if (!virtualWall[location.x + MAP_ORIGIN + 1]
                               [location.y + MAP_ORIGIN] &&
                   gyro.East &&
                   (virtualWall[location.x + MAP_ORIGIN]
                               [location.y + MAP_ORIGIN - 1] ||
                    tof.isSouthWall) &&
                   (virtualWall[location.x + MAP_ORIGIN]
                               [location.y + MAP_ORIGIN + 1] ||
                    tof.isNorthWall) &&
                   (virtualWall[location.x + MAP_ORIGIN - 1]
                               [location.y + MAP_ORIGIN] ||
                    tof.isWestWall)) {
            if (!tof.isEastWall) {
                oldmillis      = millis();
                checkPointX    = location.x;
                checkPointY    = location.y;
                DFS            = true;
                servo.velocity = SPEED;
                app.delay(1500);
            }
        } else if (!virtualWall[location.x + MAP_ORIGIN - 1]
                               [location.y + MAP_ORIGIN] &&
                   gyro.West &&
                   (virtualWall[location.x + MAP_ORIGIN]
                               [location.y + MAP_ORIGIN + 1] ||
                    tof.isNorthWall) &&
                   (virtualWall[location.x + MAP_ORIGIN]
                               [location.y + MAP_ORIGIN - 1] ||
                    tof.isSouthWall) &&
                   (virtualWall[location.x + MAP_ORIGIN + 1]
                               [location.y + MAP_ORIGIN] ||
                    tof.isEastWall)) {
            if (!tof.isWestWall) {
                oldmillis      = millis();
                checkPointX    = location.x;
                checkPointY    = location.y;
                DFS            = true;
                servo.velocity = SPEED;
                app.delay(1500);
            }
        } else {
            app.delay(period);
        }

        if (!DFS) {
            if (tof.isNotRight && !gyro.slope) {  // 右壁が消えた時の処理
                servo.velocity = 0;
                servo.suspend  = true;
                app.delay(WAIT);
                servo.suspend = false;
                servo.angle += 90;
                servo.velocity = 0;
                servo.suspend  = true;
                app.delay(WAIT);
                servo.suspend  = false;
                servo.velocity = SPEED;
                app.delay(FORWARD);  // 次のタイルまで前進
            }
        }
    }
}

void leftWallApp(App) {
    while (1) {
        servo.velocity = SPEED;
        servo.suspend  = false;
        isRightWallApp = false;
        app.delay(period);

        if (tof.isNotLeft && !gyro.slope) {  // 左壁が消えた時の処理
            servo.velocity = 0;
            servo.suspend  = true;
            app.delay(WAIT);
            servo.suspend = false;
            servo.angle -= 90;
            servo.velocity = 0;
            servo.suspend  = true;
            app.delay(WAIT);
            servo.suspend  = false;
            servo.velocity = SPEED;
            app.delay(FORWARD);  // 次のタイルまで前進
        }

        if (tof.val[0] < 140 && !gyro.slope) {  // 前に壁が来た時の処理
            servo.velocity = 0;
            servo.suspend  = true;
            app.delay(WAIT);
            servo.suspend = false;
            servo.angle += 90;
            app.delay(WAIT);
        }
    }
}

void adjustmentApp(App) {
    while (1) {
        static bool isHit = false;
        if (isRightWallApp) {
            if (tof.val[3] < 110) {
                servo.isCorrectingAngle -= 1;  // 接近しすぎたら離れる
                app.delay(period * 10);
            } else if (tof.val[3] < 230 && tof.val[2] < 265) {
                if (radius + tof.val[3] + 30 <
                    0.8660254038 *
                        (radius + tof.val[2])) {   // √3/2(tofが30°間隔)
                    servo.isCorrectingAngle += 1;  // 一度ずつ補正
                } else {
                    servo.isCorrectingAngle = 0;
                }
                if (radius + tof.val[3] - 30 >
                    0.8660254038 * (radius + tof.val[2])) {
                    servo.isCorrectingAngle -= 1;
                } else {
                    servo.isCorrectingAngle = 0;
                }
            }
        } else {
            if (tof.val[9] < 110) {
                servo.isCorrectingAngle += 1;  // 接近しすぎたら離れる
                app.delay(period * 10);
            } else if (tof.val[9] < 230 && tof.val[10] < 265) {
                if (radius + tof.val[9] + 25 <
                    0.8660254038 *
                        (radius + tof.val[8])) {  // √3/2　//NOTE
                                                  // 新機体は1/√2(0.7071067812)
                    servo.isCorrectingAngle += 1;  // 一度ずつ補正
                }
                if (radius + tof.val[9] - 25 >
                    0.8660254038 * (radius + tof.val[8])) {
                    servo.isCorrectingAngle -= 1;
                }
            }
        }

        if (loadcell.status == RIGHT) {
            app.stop(servoApp);
            servo.driveAngularVelocity(-30, 45);
            app.delay(300);
            servo.driveAngularVelocity(-30, -45);
            app.delay(300);
            isHit = false;
        }
        if (loadcell.status == LEFT) {
            app.stop(servoApp);
            servo.driveAngularVelocity(-30, -45);
            app.delay(300);
            servo.driveAngularVelocity(-30, 45);
            app.delay(300);
            isHit = false;
        }
        if (!isHit) {
            servo.velocity = SPEED;
            app.start(servoApp);
            isHit = true;
        }
        app.delay(period);
    }
}

void AstarApp(App) {  // NOTE 動いた
    app.delay(WAIT);
    int Ndistance       = MAX_DISTANCE;
    int Edistance       = MAX_DISTANCE;
    int Sdistance       = MAX_DISTANCE;
    int Wdistance       = MAX_DISTANCE;  // 値の初期化(最大値に設定)
    bool virtualWall[4] = {false};
    bool status         = true;
    app.delay(WAIT);
    const int initialWall[4] = {(tof.isNorthWall), (tof.isEastWall),
                                (tof.isSouthWall),
                                (tof.isWestWall)};  //(0,0)の壁の状態を記憶
    while (1) {
        app.delay(100);
        if (millis() > FEEDBACK && servo.velocity == 50) {
            if (status) {
                servo.velocity = 0;
                servo.suspend  = true;
                app.stop(rightWallApp);
                app.stop(leftWallApp);
                app.stop(DepthFirstSearchApp);
                // app.stop(adjustmentApp);
                app.delay(WAIT);
                servo.suspend = false;
                status        = false;
            }
            app.delay(period);
        MEASURE_DISTANCE:  // 最短経路の算出
            if ((-1 <= location.x && location.x <= 1) &&
                (-1 <= location.y && location.y <= 1) &&
                initialWall[NORTH] == tof.isNorthWall &&
                initialWall[EAST] == tof.isEastWall &&
                initialWall[SOUTH] == tof.isSouthWall &&
                initialWall[WEST] ==
                    tof.isWestWall) {  //(0,0)かつスタート時の壁情報と一致+-1まで許容
                servo.velocity = 0;
                servo.suspend  = true;
                app.stop(servoApp);
                app.delay(20000);
            }

            if (!tof.isNorthWall && !virtualWall[NORTH]) {
                Ndistance = location.x * location.x +
                            (location.y + 1) * (location.y + 1);
            } else {
                Ndistance = MAX_DISTANCE;
            }
            if (!tof.isEastWall && !virtualWall[EAST]) {
                Edistance = (location.x + 1) * (location.x + 1) +
                            location.y * location.y;
            } else {
                Edistance = MAX_DISTANCE;
            }
            if (!tof.isSouthWall && !virtualWall[SOUTH]) {
                Sdistance = location.x * location.x +
                            (location.y - 1) * (location.y - 1);
            } else {
                Sdistance = MAX_DISTANCE;
            }
            if (!tof.isWestWall && !virtualWall[WEST]) {
                Wdistance = (location.x - 1) * (location.x - 1) +
                            location.y * location.y;
            } else {
                Wdistance = MAX_DISTANCE;
            }
            for (int i = 0; i < 4; i++) {
                if (virtualWall[i]) {
                    virtualWall[i] = false;
                }
            }
        MOVE_COORDINATE:  // FIXME
            // 1マスぴったり進む方法が確立されていない&坂道来た時どうする？
            if (Ndistance < Edistance && Ndistance < Sdistance &&
                Ndistance < Wdistance) {
                servo.angle    = 0 + servo.isCorrectingAngle;
                servo.velocity = 50;
                app.delay(FORWARD);
                servo.velocity = 0;
                servo.suspend  = true;
                app.delay(WAIT);
                servo.suspend  = false;
                virtualWall[2] = true;  // 後方に仮想壁
                goto MEASURE_DISTANCE;

            } else if (Sdistance < Edistance && Sdistance < Wdistance) {
                servo.angle    = 180 + servo.isCorrectingAngle;
                servo.velocity = 50;
                app.delay(FORWARD);
                servo.velocity = 0;
                servo.suspend  = true;
                app.delay(WAIT);
                servo.suspend  = false;
                virtualWall[0] = true;
                goto MEASURE_DISTANCE;

            } else if (Edistance < Wdistance) {
                servo.angle    = 90 + servo.isCorrectingAngle;
                servo.velocity = 50;
                app.delay(FORWARD);
                servo.velocity = 0;
                servo.suspend  = true;
                app.delay(WAIT);
                servo.suspend  = false;
                virtualWall[3] = true;
                goto MEASURE_DISTANCE;

            } else {
                servo.angle    = 270 + servo.isCorrectingAngle;
                servo.velocity = 50;
                app.delay(FORWARD);
                servo.velocity = 0;
                servo.suspend  = true;
                app.delay(WAIT);
                servo.suspend  = false;
                virtualWall[1] = true;
                goto MEASURE_DISTANCE;
            }
        } else {
            app.delay(period * 5);
        }
    }
}

void monitorApp(App) {
    while (1) {
        floorSensor.colorJudgment();
        if (floorSensor.isRed) {
            uart1.print("red");
            uart1.println("\t");
        }
        if (floorSensor.isGreen) {
            uart1.print("green");
            uart1.println("\t");
        }
        if (floorSensor.isBlue) {
            uart1.print("blue");
            uart1.println("\t");
        }
        if (floorSensor.isWhite) {
            uart1.print("white");
            uart1.println("\t");
        }
        if (floorSensor.isBlack) {
            uart1.print("black");
            uart1.println("\t");
        }
        app.delay(300);
    }
}

void DepthFirstSearchApp(App) {  // NOTE 二方向以上進める座標を記録する変数
                                 // "JCT"
    static bool JCT[MAP_ORIGIN * 2][MAP_ORIGIN * 2] = {false};
    static bool turn                                = false;
    app.delay(WAIT);
    while (1) {
        virtualWall[location.x + MAP_ORIGIN][location.y + MAP_ORIGIN] =
            true;  // 仮想壁
        app.delay(period);

        if (tof.val[0] > 450 && (tof.val[3] > 230 || tof.val[9] > 230)) {
            JCT[location.x + MAP_ORIGIN][location.y + MAP_ORIGIN] = true;
        }
        if (!isRightWallApp &&
            JCT[location.x + MAP_ORIGIN][location.y + MAP_ORIGIN] &&
            (tof.val[3] > 230 || tof.val[9] > 230)) {
            servo.suspend = true;
            app.delay(WAIT);
            servo.suspend = false;
            app.stop(leftWallApp);
            app.start(rightWallApp);
        }

        if (!tof.isNotFront) {
            app.stop(rightWallApp);
            servo.suspend = true;
            app.delay(WAIT);
            servo.suspend = false;
            servo.angle += 90;
            servo.velocity = 0;
            app.delay(WAIT * 2);
            servo.suspend = true;
            app.delay(WAIT);
            servo.suspend = false;
            servo.angle += 90;
            app.delay(WAIT * 2);
            app.start(leftWallApp);

        }  // 前方+左右に壁があったら反転して左壁追従

        if (checkPointX == location.x && checkPointY == location.y &&
            oldmillis + 10000 < millis()) {  // DFS開始地点に戻ってきたら反転
            oldmillis   = millis();
            checkPointX = MAP_ORIGIN;
            checkPointY = MAP_ORIGIN;
            app.delay(period);
            app.stop(rightWallApp);
            servo.angle += 180;
            app.delay(WAIT * 2);
            app.start(rightWallApp);
        }
    }
}
#endif