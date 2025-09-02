#pragma once
#include <Arduino.h>

struct RGB {
            uint8_t R;
            uint8_t G; 
            uint8_t B;
};

struct Button {
                int X = 0;
                int Y = 0;
                int Width = 0;
                int Height = 0;
                const char* Label = "";
                RGB Color = {0,0,0};
};
