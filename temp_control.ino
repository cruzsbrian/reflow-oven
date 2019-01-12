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
    
    #IFDEF      USE_SERIAL
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
    #ENDIF
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
  #IFDEF        USE_SERIAL
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
  #ENDIF
}
