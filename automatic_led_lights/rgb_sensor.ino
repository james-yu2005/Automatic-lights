#include <Adafruit_NeoPixel.h>
#include "SR04.h"

// Define the LED strip parameters
#define LED_PIN     6   // The digital pin connected to the DIN of the LED strip
#define LED_COUNT  10  // Number of LEDs in the strip
#define TRIG_PIN 12
#define ECHO_PIN 11
bool light = false;
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;
// Create a NeoPixel object
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
    strip.begin();        // Initialize the strip
    strip.show();         // Turn off all LEDs at startup
    strip.setBrightness(50); // Set brightness (0-255)
}

void loop() {
  a=sr04.Distance();
  if (a < 50 and light == false) {
    light = true;
    rainbowCycle(10);
    delay(1000);
  }
  else if (a < 50 and light == true) {
    light = false;
    strip.clear();
    strip.show();
    delay(1000);
  }
}

// Function to display a continuous rainbow effect on the LED strip
void rainbowCycle(int wait) {
    // Loop forever
    for (int j = 0; j < 256; j++) {
        // Loop through each LED in the strip
        for (int i = 0; i < strip.numPixels(); i++) {
            int pixelIndex = (i + j) & 255;  // Calculate the color based on the position
            strip.setPixelColor(i, Wheel(pixelIndex));  // Set the LED to the current color in the rainbow
        }
        strip.show();  // Update the LED strip with the new colors
        delay(wait);  // Pause for a short delay before changing colors
    }
}

// Function to generate rainbow colors based on the position
uint32_t Wheel(byte WheelPos) {
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85) {
        return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);  // Red to Blue
    } else if (WheelPos < 170) {
        WheelPos -= 85;
        return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);  // Green to Red
    } else {
        WheelPos -= 170;
        return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);  // Blue to Green
    }
}
