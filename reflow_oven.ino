#define N_MODES 8

bool running = false;
unsigned long start_time = 0;

int selectedMode = 0;
int scrollPos = 0;

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
    setupDisplay();
    setupButtons();
}

void loop() {
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

    delay(10);
}
