#pragma once
#include <Arduino.h>
#include <stdint.h>

uint16_t Color565(uint8_t r, uint8_t g, uint8_t b){
    r = constrain(r, 0, 255);
    g = constrain(g, 0, 255);
    b = constrain(b, 0, 255);

    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}


