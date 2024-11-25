#ifndef GETQRCODE_H
#define GETQRCODE_H
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Config.h"

String getQRCode(SoftwareSerial qrcodeSerial);

#endif