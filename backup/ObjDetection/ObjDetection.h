#ifndef OBJDETECTION_H
#define OBJDETECTION_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include "Config.h"

void objDetection(SoftwareSerial espSerial, Servo servo1);
void lidMotor(String trash_type, Servo servo1);

#endif // OBJDETECTION_H
