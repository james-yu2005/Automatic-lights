#include <Adafruit_NeoPixel.h>
#include <NewPing.h>

// Define the LED strip parameters
#define LED_PIN     6    // The digital pin connected to the DIN of the LED strip
#define LED_COUNT  150   // Number of LEDs in the strip
#define TRIG_PIN 12     // Pin for the TRIG pin on the ultrasonic sensor
#define ECHO_PIN 11     // Pin for the ECHO pin on the ultrasonic sensor
#define MAX_DISTANCE 50 // Maximum distance to detect (in cm)
#define POT_PIN     A0   // Pin where the potentiometer is connected

// Create a NewPing object
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

bool light = false;
bool light_show = false;

// Create a NeoPixel object
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
    Serial.begin(9600);      // Start serial communication
    strip.begin();           // Initialize the strip
    strip.show();            // Turn off all LEDs at startup
    strip.setBrightness(50); // Set initial brightness (0-255)
}

void loop() {
    // Measure distance in cm
    long a = sonar.ping_cm();
    Serial.println(a);  // Print the distance in cm to the serial monitor

    // If distance is less than 50 cm and light is off, turn on the light
    if (a > 0 && a < 50 && !light) {
        light = true;
        light_show = true;
        rainbowCycle(10);  // Show rainbow effect
        delay(1000);       // Wait for a second before checking again
    }

    // If distance is less than 50 cm and light is on, turn off the light
    else if (a > 0 && a < 50 && light) {
        light = false;
        light_show = false;
        strip.clear();      // Clear the LEDs
        strip.show();       // Update the LEDs
        delay(1000);        // Wait for a second before checking again
    }

    // // Control brightness with potentiometer
    // int potValue = analogRead(POT_PIN);  // Read potentiometer value (0 to 1023)
    // int brightness = map(potValue, 0, 1023, 0, 255);  // Map to brightness range (0 to 255)
    // strip.setBrightness(brightness);   // Set the brightness
}

void rainbowCycle(int wait) {
  for (int j = 0; j <= 225; j += 15) {
    for (int i = 30; i < LED_COUNT; i++) {  // Loop through each LED one at a time
        strip.setPixelColor(i, Wheel(((i+j)* 256 / LED_COUNT) & 255));  // Set color for this LED
        strip.show();  // Update the LED strip
        delay(wait);   // Delay to create sequential effect
    }
  }
    
}


// Function to generate rainbow colors based on the position
uint32_t Wheel(byte WheelPos) {
    WheelPos = 255 - WheelPos;  // Reverse color wheel to make rainbow direction more natural
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
