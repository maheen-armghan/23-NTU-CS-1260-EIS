
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup()
{
  Wire.begin(21, 22); // SDA, SCL pins for ESP32

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR))
  {
    for (;;)
      ; // Halt if display not found
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.display();
}

void loop()
{
  display.clearDisplay();

  // Draw border box
  display.drawRect(10, 10, 108, 44, SSD1306_WHITE);

  // Display name
  display.setTextSize(1);
  display.setCursor(25, 22);
  display.println("Maheen Saqib");

  // Display ID below the name
  display.setTextSize(2);
  display.setCursor(40, 36);
  display.println("ID: 1260");

  display.display();
  delay(3000);

  // Optional: draw cross lines for 2 seconds
  display.clearDisplay();
  display.drawLine(0, 0, 127, 63, SSD1306_WHITE);
  display.drawLine(0, 63, 127, 0, SSD1306_WHITE);
  display.display();
  delay(2000);
}
