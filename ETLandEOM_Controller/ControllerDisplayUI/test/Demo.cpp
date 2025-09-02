#include <Arduino.h>
#include <Arduino_GigaDisplay_GFX.h>
#include <ArduinoGraphics.h>
#include <Arduino_GigaDisplayTouch.h>

GigaDisplay_GFX gfx;
Arduino_GigaDisplayTouch touch;

// Convert 8-bit R,G,B into 16-bit 565 color
uint16_t Color565(uint8_t r, uint8_t g, uint8_t b) {
  return ((r & 0xF8) << 8) |   // top 5 bits of red
         ((g & 0xFC) << 3) |   // top 6 bits of green
         (b >> 3);             // top 5 bits of blue
}

// Button struct
struct Button {
  int x, y, w, h;
  const char* label;
  uint16_t color;  // background color when pressed
};

// Three buttons at bottom (using RGB)
Button btn1 = {50 , 300, 150, 80, "Button 1", Color565(255, 0, 0)};   // Red
Button btn2 = {220, 300, 150, 80, "Button 2", Color565(0, 255, 0)};  // Green
Button btn3 = {50 , 400, 150, 80, "Button 3", Color565(0, 0, 255)};  // Blue
Button btn4 = {220, 400, 150, 80, "Button 4", Color565(0, 0, 0)};  // Blue

Button* buttons[] = {&btn1, &btn2, &btn3, &btn4};

// Draw a button
void drawButton(Button &btn) {
  gfx.fillRect(btn.x, btn.y, btn.w, btn.h, btn.color);
  gfx.drawRect(btn.x, btn.y, btn.w, btn.h, Color565(255, 255, 255)); // white border
  gfx.setCursor(btn.x + 10, btn.y + btn.h / 2 - 10);
  gfx.setTextSize(2);
  gfx.setTextColor(Color565(255, 255, 255)); // white text
  gfx.print(btn.label);
}

// Draw title and letters
void drawTitleAndLetters() {
  gfx.setCursor(50, 20);
  gfx.setTextSize(5);
  gfx.setTextColor(Color565(255, 255, 255)); // white
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
  gfx.fillScreen(Color565(0, 0, 0)); // black background

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
        delay(100); // simple debounce
        break;
      }
    }
  }

  delay(10); // small delay to reduce CPU load
}
