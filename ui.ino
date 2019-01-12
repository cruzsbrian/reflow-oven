#include <SPI.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define TEXT_SIZE 2
#define WIDTH_CHARS (20 / TEXT_SIZE)

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setupDisplay() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }

    display.setTextSize(TEXT_SIZE);
    display.setTextColor(WHITE);

    display.clearDisplay();
    display.display();
}

void printStatus(String text) {
    display.setCursor(0, 0);
    display.print(text);

    int padding = WIDTH_CHARS - text.length();
    for (;padding--;) {
        display.write(' ');
    }

    display.display();
}
