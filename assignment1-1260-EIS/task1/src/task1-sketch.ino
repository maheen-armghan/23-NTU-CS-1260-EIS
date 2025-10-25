/*
  Task A: LED Mode Controller with OLED
  Name: Maheen Saqib
  Reg. No: 23-NTU-CS-1260
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
//these lines set the OLED size to 128×64 pixels and create a display object using the I2C connection,
// so we can send text or graphics to the screen

#define BTN_MODE 12 //this button changes mode
#define BTN_RESET 14 //resets leds
//output pins for leds
#define LED1 18
#define LED2 19

// Variables
int mode = 1;  // Start with "Both OFF"
//mode keeps track of which LED mode is active.
//lastDebounceTime helps avoid multiple button reads.
//debounceDelay = 250 ms delay to stabilize button presses.
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 250;

void setup() {
  pinMode(BTN_MODE, INPUT_PULLUP);
  pinMode(BTN_RESET, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
//INPUT_PULLUP means the pin reads HIGH normally and LOW when button is pressed.
// OUTPUT means the pin controls things like LEDs

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;); // 0x3C is the unique address of OLED. This 
    //code checks if OLED is in right address.Stop if OLED not found
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  updateOLED();  
}

void loop() {
  //Button 1: Cycle Modes 
  if (digitalRead(BTN_MODE) == LOW && (millis() - lastDebounceTime) > debounceDelay) {
    mode++;
    if (mode > 4) mode = 1;
    lastDebounceTime = millis();
    updateOLED();
  }

  //Button 2: Reset to OFF ---
  if (digitalRead(BTN_RESET) == LOW && (millis() - lastDebounceTime) > debounceDelay) {
    mode = 1;
    lastDebounceTime = millis();
    // Turn off both LEDs immediately
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    updateOLED();
  }

  // --- LED Modes ---
  switch (mode) {
    case 1: // Both OFF
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      break;

    case 2: // Alternate Blink
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      delay(300);
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
      delay(300);
      break;

    case 3: // Both ON
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      break;

    case 4: // PWM Fade (Alternate)
      for (int i = 0; i <= 255; i++) {
        analogWrite(LED1, i);
        analogWrite(LED2, 255 - i);
        delay(5);
        // Check if button pressed during fade
        if (digitalRead(BTN_MODE) == LOW || digitalRead(BTN_RESET) == LOW) break;
      }
      for (int i = 255; i >= 0; i--) {
        analogWrite(LED1, i);
        analogWrite(LED2, 255 - i);
        delay(5);
        // Check if button pressed during fade
        if (digitalRead(BTN_MODE) == LOW || digitalRead(BTN_RESET) == LOW) break;
      }
      // Ensure LEDs are fully off at end of fade
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      break;
  }
}

// --- OLED Display Function ---
void updateOLED() {
  display.clearDisplay();
  display.setCursor(0, 10);
  switch (mode) {
    case 1: display.print("Mode 1: Both OFF"); break;
    case 2: display.print("Mode 2: Alternate Blink"); break;
    case 3: display.print("Mode 3: Both ON"); break;
    case 4: display.print("Mode 4: PWM Fade"); break;
  }
  display.display();
}