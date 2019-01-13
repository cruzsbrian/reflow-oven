#define N_MODES 8

#define USE_SERIAL

bool running = false;
unsigned long start_time = 0;

int selectedMode = 0;
int scrollPos = 0;

float setpoint = 95;

int c = 0;

String modes[] = {
    "Mode1",
    "Mode2",
    "Mode3",
    "Mode4",
    "Mode5",
    "Mode6",
    "Mode7",
    "Mode8",
};

void setup() {
    //setupDisplay();
    //setupButtons();
    Serial.begin(9600);
    setupThermo();
    setupHeaters();
}

void loop() {
    /*
    if (running) {
        showRunning((millis() - start_time) / 1000, 25.0);

        //TODO control logic


        if (getBtnStop()) {
            running = false;
        }

    } else {
        showIdle(modes, N_MODES, selectedMode, scrollPos);

        // scrolling
        if (getBtnMode()) {
            selectedMode = (selectedMode + 1) % N_MODES;
            
            scrollPos = (selectedMode / 3) * 3;
        }

        //TODO set heating elements off

        if (getBtnStart()) {
            running = true;
            start_time = millis();
        }
    }
    */

    checkThermoFlt();
    float temp = getThermoTemp();

    if (c == 5) {
        Serial.println(temp);
        c = 0;
    } else {
        c++;
    }

    if (temp > setpoint + 0.25) {
        setHeater1(false);
        setHeater2(false);
    }

    if (temp < setpoint - 0.25) {
        setHeater1(true);
        setHeater2(true);
    }

    delay(10);
}
