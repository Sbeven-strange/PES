#include <MD_Parola.h>
#include <MD_MAX72XX.h>
#include <SPI.h>

// Define hardware type and number of modules
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 5  // Adjust based on your module count

// Pin connections for ESP8266 (Wemos D1 Mini)
#define DATA_PIN 13  // D7
#define CLK_PIN  14  // D5
#define CS_PIN   15  // D8

// Create display object
MD_Parola matrix = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

String scrollText = "Hello!";  // Default text

void setup() {
    Serial.begin(115200);
    matrix.begin();
    matrix.setIntensity(2);  // Adjust brightness (0-15)
    matrix.displayClear();
    //matrix.displayScroll(scrollText.c_str(), PA_CENTER, PA_SCROLL_LEFT, 100);
    matrix.displayText(scrollText.c_str(), PA_CENTER, 100, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
}

void loop() {
    if (matrix.displayAnimate()) {
        matrix.displayReset();
    }

    // Check for new input from Serial Monitor
    if (Serial.available()) {
        scrollText = Serial.readStringUntil('\n');  // Read input text
        Serial.println("Displaying: " + scrollText);
        matrix.displayClear();
        //matrix.displayScroll(scrollText.c_str(), PA_CENTER, PA_SCROLL_LEFT, 100);
        matrix.displayText(scrollText.c_str(), PA_CENTER, 100, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
    }
}
