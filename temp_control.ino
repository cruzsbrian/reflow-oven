/*******************************************************************************
 * temp_control.ino
 *
 * Description:
 *
 * Interface:
 *
 * Hardware:
 * 
 * Compatibility:
 *      Target          Most every Arduino-esque thing should be compatible
 *                      including 3V3 stuff
 *
 * Notes:
 *
 * Revision History:
 *      1/11/2019       Ray Sun         Initial revision. 
 *
 * Validation:
 *      1/11/2019       Ray Sun         Validated Adafruit sample code
 ******************************************************************************/

#include <Adafruit_MAX31856.h>


#define PIN_HEATER_1 9
#define PIN_HEATER_2 8

// TODO: USE THE HARDWARE SPI

// Use software SPI: CS, DI, DO, CLK
Adafruit_MAX31856 maxthermo = Adafruit_MAX31856(10, 11, 12, 13);
// use hardware SPI, just pass in the CS pin
//Adafruit_MAX31856 maxthermo = Adafruit_MAX31856(10);


/**
 * Instantiates Thermocouple object
 */
void setupThermo() {
    // Thermocouple is type K
    maxthermo.begin();
    maxthermo.setThermocoupleType(MAX31856_TCTYPE_K);
    
    #ifdef      USE_SERIAL
    Serial.print("Thermocouple type: ");
    switch (maxthermo.getThermocoupleType() ) {
        case MAX31856_TCTYPE_B: Serial.println("B Type"); break;
        case MAX31856_TCTYPE_E: Serial.println("E Type"); break;
        case MAX31856_TCTYPE_J: Serial.println("J Type"); break;
        case MAX31856_TCTYPE_K: Serial.println("K Type"); break;
        case MAX31856_TCTYPE_N: Serial.println("N Type"); break;
        case MAX31856_TCTYPE_R: Serial.println("R Type"); break;
        case MAX31856_TCTYPE_S: Serial.println("S Type"); break;
        case MAX31856_TCTYPE_T: Serial.println("T Type"); break;
        case MAX31856_VMODE_G8: Serial.println("Voltage x8 Gain mode"); break;
        case MAX31856_VMODE_G32: Serial.println("Voltage x8 Gain mode"); break;
        default: Serial.println("Unknown"); break;
    }  
    #endif
}


/**
 * Returns the thermocouple temperature reading
 */
float getThermoTemp() {
    return maxthermo.readThermocoupleTemperature();
}

/**
 * Returns the thermocouple cold junction reading 
 */
float getThermoBcg() {
    return maxthermo.readCJTemperature();
}

/**
 * Checks thermocouple amplifier faults and prints to serial. 
 * 
 * USE_SERIAL must be defined.
 */
void checkThermoFlt() {
  uint8_t fault = maxthermo.readFault();
  #ifdef        USE_SERIAL
  if (fault) {
    if (fault & MAX31856_FAULT_CJRANGE) Serial.println("Cold Junction Range Fault");
    if (fault & MAX31856_FAULT_TCRANGE) Serial.println("Thermocouple Range Fault");
    if (fault & MAX31856_FAULT_CJHIGH)  Serial.println("Cold Junction High Fault");
    if (fault & MAX31856_FAULT_CJLOW)   Serial.println("Cold Junction Low Fault");
    if (fault & MAX31856_FAULT_TCHIGH)  Serial.println("Thermocouple High Fault");
    if (fault & MAX31856_FAULT_TCLOW)   Serial.println("Thermocouple Low Fault");
    if (fault & MAX31856_FAULT_OVUV)    Serial.println("Over/Under Voltage Fault");
    if (fault & MAX31856_FAULT_OPEN)    Serial.println("Thermocouple Open Fault");
  }
  #endif
}


void setupHeaters() {
    pinMode(PIN_HEATER_1, OUTPUT);
    pinMode(PIN_HEATER_2, OUTPUT);

    // write HIGH initially to turn heaters off
    digitalWrite(PIN_HEATER_1, HIGH);
    digitalWrite(PIN_HEATER_2, HIGH);
}

void setHeater1(bool on) {
    digitalWrite(PIN_HEATER_1, !on);
}

void setHeater2(bool on) {
    digitalWrite(PIN_HEATER_2, !on);
}
