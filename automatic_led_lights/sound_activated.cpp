#include <Adafruit_NeoPixel.h>

// Define pins
#define LED_PIN 6     // LED strip data pin
#define LED_COUNT 150 // Number of LEDs in the strip
#define SOUND_SENSOR_PIN 2 // KY-038 Digital Output pin

// LED strip object
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// State variables
bool is_on = false;   // Track LED state
unsigned long lastClapTime = 0;
const int clapInterval = 500; // 500ms debounce

void setup() {
    pinMode(SOUND_SENSOR_PIN, INPUT);
    Serial.begin(9600);
    
    strip.begin();
    strip.show(); // Initialize all LEDs to off
    strip.setBrightness(50); // Adjust brightness (0-255)
}

void loop() {
    int soundDetected = digitalRead(SOUND_SENSOR_PIN);

    if (soundDetected == HIGH) { // Loud sound detected
        unsigned long currentTime = millis();
        
        if (currentTime - lastClapTime > clapInterval) { // Debounce
            is_on = !is_on; // Toggle LED state
            
            if (is_on) {
                Serial.println("Clap detected: Turning ON LEDs");
                rainbowCycle(10);
            } else {
                Serial.println("Clap detected: Turning OFF LEDs");
                strip.clear();
                strip.show();
            }
            
            lastClapTime = currentTime; // Update last clap time
        }
    }
}

// Rainbow effect function
void rainbowCycle(int wait) {
    for (int j = 0; j <= 225; j += 15) {
        for (int i = 0; i < LED_COUNT; i++) {  
            strip.setPixelColor(i, Wheel(((i + j) * 256 / LED_COUNT) & 255)); 
        }
        strip.show();
        delay(wait);
    }
}

// Function to generate rainbow colors
uint32_t Wheel(byte WheelPos) {
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85) {
        return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    } else if (WheelPos < 170) {
        WheelPos -= 85;
        return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    } else {
        WheelPos -= 170;
        return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    }
}
 
