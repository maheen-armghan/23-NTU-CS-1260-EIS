/*******************************************************
   Topic: Displaying Custom Emoji on OLED using ESP32
   Name: Maheen
   Reg No: 23-NTU-CS-1260
   Description: This program displays multiple custom 
   emoji icons simultaneously on an OLED screen using ESP32.
*******************************************************/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#ifndef PI
#define PI 3.14159265358979323846
#endif

// Function declarations
void drawCatFace(int16_t x, int16_t y);
void drawFlower(int16_t x, int16_t y);
void drawBell(int16_t x, int16_t y);
void drawFire(int16_t x, int16_t y);
void drawBalloon(int16_t x, int16_t y);
void drawArc(int16_t cx, int16_t cy, int16_t r, float startDeg, float endDeg, uint16_t color);

void setup() {
  Wire.begin(21, 22); // SDA, SCL for ESP32
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    for (;;); // Stop if OLED not found
  }
  display.clearDisplay();
  display.display();
}

void loop() {
  display.clearDisplay();

  // Draw all emojis in different positions
  drawFlower(20, 10);   // 🌸 Top Left
  drawCatFace(64, 10);  // 😺 Top Center
  drawBell(105, 10);    // 🔔 Top Right
  drawFire(20, 45);     // 🔥 Bottom Left
  drawBalloon(105, 45); // 🎈 Bottom Right

  display.display();
  delay(2000);
}

// ---------------- Emoji Drawing Functions ----------------

// 😺 Cat Face
void drawCatFace(int16_t x, int16_t y) {
  display.drawCircle(x, y, 8, SSD1306_WHITE);
  display.fillCircle(x - 3, y - 2, 1, SSD1306_WHITE);
  display.fillCircle(x + 3, y - 2, 1, SSD1306_WHITE);
  drawArc(x, y + 2, 4, 20, 160, SSD1306_WHITE);  // mouth
}

// 🌸 Flower
void drawFlower(int16_t x, int16_t y) {
  display.fillCircle(x - 3, y, 3, SSD1306_WHITE);
  display.fillCircle(x + 3, y, 3, SSD1306_WHITE);
  display.fillCircle(x, y - 3, 3, SSD1306_WHITE);
  display.fillCircle(x, y + 3, 3, SSD1306_WHITE);
  display.fillCircle(x, y, 2, SSD1306_BLACK);  // center
}

// 🔔 Bell
void drawBell(int16_t x, int16_t y) {
  display.drawTriangle(x - 5, y + 5, x + 5, y + 5, x, y - 5, SSD1306_WHITE);
  display.drawLine(x - 5, y + 5, x - 3, y + 8, SSD1306_WHITE);
  display.drawLine(x + 5, y + 5, x + 3, y + 8, SSD1306_WHITE);
  display.fillCircle(x, y + 8, 2, SSD1306_WHITE);
}

// 🔥 Fire
void drawFire(int16_t x, int16_t y) {
  display.fillTriangle(x, y - 6, x - 4, y + 4, x + 4, y + 4, SSD1306_WHITE);
  display.fillTriangle(x, y - 3, x - 2, y + 2, x + 2, y + 2, SSD1306_BLACK);
}

// 🎈 Balloon
void drawBalloon(int16_t x, int16_t y) {
  display.drawCircle(x, y - 3, 6, SSD1306_WHITE);
  display.drawLine(x, y + 3, x, y + 10, SSD1306_WHITE);
  display.drawLine(x - 1, y + 10, x, y + 12, SSD1306_WHITE);
  display.drawLine(x + 1, y + 10, x, y + 12, SSD1306_WHITE);
}

// Helper function to draw arcs
void drawArc(int16_t cx, int16_t cy, int16_t r, float startDeg, float endDeg, uint16_t color) {
  float start = startDeg * PI / 180.0;
  float end = endDeg * PI / 180.0;
  float step = 0.1;
  for (float a = start; a <= end; a += step) {
    int16_t x = cx + (int16_t)(r * cos(a));
    int16_t y = cy + (int16_t)(r * sin(a));
    display.drawPixel(x, y, color);
  }
}
