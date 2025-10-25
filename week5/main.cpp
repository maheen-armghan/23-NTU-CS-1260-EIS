/****************************************************
 * Project: LED Fade and Buzzer Tone Demo using PWM
 * Description:
 * This program demonstrates how to control two LEDs 
 * and a buzzer using PWM on an ESP32. The LEDs fade 
 * in opposite directions, and the buzzer generates 
 * periodic beeps synchronized with the LED brightness.
 ****************************************************/

#include <Arduino.h>

// --- Pin definitions ---
#define LED1_PIN 18      // LED 1 connected to GPIO 18
#define LED2_PIN 19      // LED 2 connected to GPIO 19
#define BUZZER_PIN 27    // Buzzer connected to GPIO 27

// --- PWM channel assignments ---
#define LED1_CH 0        // PWM channel for LED 1
#define LED2_CH 1        // PWM channel for LED 2
#define BUZZER_CH 2      // PWM channel for Buzzer

// --- PWM configuration settings ---
#define LED_FREQ 5000    // PWM frequency for LEDs
#define LED_RES 8        // 8-bit resolution (0–255)
#define BUZZER_FREQ 2000 // PWM frequency for buzzer
#define BUZZER_RES 10    // 10-bit resolution (0–1023)

void setup() {
  // --- Initialize PWM for LEDs ---
  ledcSetup(LED1_CH, LED_FREQ, LED_RES);
  ledcAttachPin(LED1_PIN, LED1_CH);

  ledcSetup(LED2_CH, LED_FREQ, LED_RES);
  ledcAttachPin(LED2_PIN, LED2_CH);

  // --- Initialize PWM for Buzzer ---
  ledcSetup(BUZZER_CH, BUZZER_FREQ, BUZZER_RES);
  ledcAttachPin(BUZZER_PIN, BUZZER_CH);
  ledcWrite(BUZZER_CH, 512);  // Set initial 50% duty cycle for passive buzzer

  // --- Start Serial Monitor ---
  Serial.begin(115200);
  Serial.println("Starting LED Fade + Buzzer Demo...");
}

void loop() {
  // --- Fade LEDs UP and beep buzzer during fade ---
  for (int brightness = 0; brightness <= 255; brightness++) {
    ledcWrite(LED1_CH, brightness);          // LED1 fades up
    ledcWrite(LED2_CH, 255 - brightness);    // LED2 fades down (opposite effect)

    // Trigger buzzer beep at every 50 step brightness
    if (brightness % 50 == 0) {
      ledcWriteTone(BUZZER_CH, 1500);  // Play buzzer tone
      delay(100);
      ledcWrite(BUZZER_CH, 0);         // Stop tone
    }

    delay(10);
  }

  // --- Fade LEDs DOWN and beep buzzer during fade ---
  for (int brightness = 255; brightness >= 0; brightness--) {
    ledcWrite(LED1_CH, brightness);
    ledcWrite(LED2_CH, 255 - brightness);

    if (brightness % 50 == 0) {
      ledcWriteTone(BUZZER_CH, 1200);
      delay(100);
      ledcWrite(BUZZER_CH, 0);
    }

    delay(10);
  }
}
