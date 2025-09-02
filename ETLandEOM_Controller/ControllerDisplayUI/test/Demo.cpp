#include <Arduino.h>
#include <Arduino_GigaDisplay_GFX.h>
#include <ArduinoGraphics.h>
#include <Arduino_GigaDisplayTouch.h>

GigaDisplay_GFX gfx;
Arduino_GigaDisplayTouch touch;

// Button struct
struct Button {
  int x, y, w, h;
  const char* label;
  uint16_t color;  // background color when pressed
};

// Three buttons at bottom
Button btn1 = {50, 300, 150, 80, "Button 1", 0xF800}; // Red
Button btn2 = {220, 300, 150, 80, "Button 2", 0x07E0}; // Green
Button btn3 = {390, 300, 150, 80, "Button 3", 0x001F}; // Blue

Button* buttons[] = {&btn1, &btn2, &btn3};

// Draw a button
void drawButton(Button &btn) {
  gfx.fillRect(btn.x, btn.y, btn.w, btn.h, btn.color);
  gfx.drawRect(btn.x, btn.y, btn.w, btn.h, 0xFFFF); // white border
  gfx.setCursor(btn.x + 10, btn.y + btn.h / 2 - 10);
  gfx.setTextSize(2);
  gfx.setTextColor(0xFFFF); // white text
  gfx.print(btn.label);
}

// Draw title and letters
void drawTitleAndLetters() {
  gfx.setCursor(50, 20);
  gfx.setTextSize(5);
  gfx.setTextColor(0xFFFF);
  gfx.print("DEMO");

  gfx.setCursor(50, 120);
  gfx.setTextSize(2);
  gfx.print("ABCD EFGH IJKL");
  gfx.setCursor(50, 150);
  gfx.print("MNOP QRST UVWX");
  gfx.setCursor(50, 180);
  gfx.print("YZ 1234 5678");
}

// Check if touch is inside button
bool isTouched(Button &btn, int tx, int ty) {
  return (tx > btn.x && tx < btn.x + btn.w &&
          ty > btn.y && ty < btn.y + btn.h);
}

void setup() {
  gfx.begin();
  gfx.fillScreen(0x0000); // black

  touch.begin();

  // Draw title and buttons initially
  drawTitleAndLetters();
  for (Button* b : buttons) drawButton(*b);
}

void loop() {
  uint8_t contacts;
  GDTpoint_t points[5];

  contacts = touch.getTouchPoints(points); // get touch points

  if (contacts > 0) {
    int tx = points[0].x;
    int ty = points[0].y;

    for (Button* b : buttons) {
      if (isTouched(*b, tx, ty)) {
        gfx.fillScreen(b->color);
        drawTitleAndLetters();
        for (Button* btn : buttons) drawButton(*btn);
        delay(200); // simple debounce
        break;
      }
    }
  }

  delay(10); // small delay to reduce CPU load
}
