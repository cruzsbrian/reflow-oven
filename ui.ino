#include <SPI.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DEBOUNCE_DELAY 200 // ms
#define BTN_MODE 2
#define BTN_START 0
#define BTN_STOP 1


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define TEXT_SIZE 2
#define WIDTH_CHARS (20 / TEXT_SIZE)

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


unsigned long last_press_mode = 0;
unsigned long last_press_start = 0;
unsigned long last_press_stop = 0;
bool last_mode = false;
bool last_start = false;
bool last_stop = false;

void (*mode_callback)();
void (*start_callback)();
void (*stop_callback)();


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

void showRunning(int time, float temp) {
    display.setTextColor(WHITE);
    display.clearDisplay();

    display.setCursor(0, 0);
    display.print("RUNNING");

    display.setCursor(0, 25);

    display.print(time / 60);

    display.print(":");

    if (time % 60 < 10) { display.print(0); }
    display.print(time % 60);

    display.setCursor(0, 50);
    display.print(temp);
    display.print("C");

    display.display();
}

void showIdle(String *modes, int nModes, int selectedMode, int scrollPos) {
    display.setTextColor(WHITE);
    display.clearDisplay();

    display.setCursor(0, 0);
    display.println("IDLE");

    for (int i = scrollPos; i < nModes; i++) {
        if (i == selectedMode) {
            display.setTextColor(BLACK, WHITE);
        } else {
            display.setTextColor(WHITE);
        }

        display.print(modes[i]);
        
        for (int i = 0; i < WIDTH_CHARS - modes[i].length(); i++) {
            display.write(' ');
        }
        display.println();
    }

    display.display();
}


void setupButtons() {
    pinMode(BTN_MODE, INPUT_PULLUP);
    pinMode(BTN_START, INPUT_PULLUP);
    pinMode(BTN_STOP, INPUT_PULLUP);
}

bool getBtnMode() {
    bool reading = !digitalRead(BTN_MODE);

    if (reading != last_mode) {
        if (millis() - last_press_mode > DEBOUNCE_DELAY) {
            last_mode = reading;
            return reading;
        }
        last_press_mode = millis();
    }

    return false;
}

bool getBtnStart() {
    return !digitalRead(BTN_START);
}

bool getBtnStop() {
    return !digitalRead(BTN_STOP);
}
