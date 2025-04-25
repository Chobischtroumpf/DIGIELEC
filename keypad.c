
#include "keypad.h"


/*
 * Function to initialize the keypad.
 * The function sets all columns to high impedance (input) mode.
*/
void keypadInit(void) {

    // Set all columns to high impedance (input) mode
    COL1_Write(1);
    COL2_Write(1);
    COL3_Write(1);

}

/*
 * Function to scan the keypad and return the key pressed.
 * The function returns a character corresponding to the key pressed.
 * The function returns 'z' if no key is pressed.
*/
uint8_t keypadScan(void) {
    
    COL1_Write(0);
    CyDelay(KBD_DELAY);
    if (!ROW0_Read()) {
        COL1_Write(1);
        return('#');
    }
    if (!ROW1_Read()) {
        COL1_Write(1);
        return('9');
    }
    if (!ROW2_Read()) {
        COL1_Write(1);
        return('6');
    }
    if (!ROW3_Read()) {
        COL1_Write(1);
        return('3');
    }
    COL1_Write(1);
    
    COL2_Write(0);
    CyDelay(KBD_DELAY);
    if (!ROW0_Read()) {
        COL2_Write(1);
        return('0');
    }
    if (!ROW1_Read()) {
        COL2_Write(1);
        return('8');
    }
    if (!ROW2_Read()) {
        COL2_Write(1);
        return('5');
    }
    if (!ROW3_Read()) {
        COL2_Write(1);
        return('2');
    }
    COL2_Write(1);

    COL3_Write(0);
    CyDelay(KBD_DELAY);
    if (!ROW0_Read()) {
        COL3_Write(1);
        return('*');
    }
    if (!ROW1_Read()) {
        COL3_Write(1);
        return('7');
    }
    if (!ROW2_Read()) {
        COL3_Write(1);
        return('4');
    }
    if (!ROW3_Read()) {
        COL3_Write(1);
        return('1');
    }
    COL3_Write(1);
    
    return('z');
}

/*
 * Function to get some message from the keypad tiles.
 * The function returns a string corresponding to the key pressed.
*/
const char *getMessageFromKey(char key) {

    switch (key) {
        case '1': return "SOS";
        case '2': return "BEAMS";
        case '3': return "PLEASE";
        case '4': return "HELP ME";
        case '5': return "HELP";
        case '6': return "OUT OF FOOD";
        case '7': return "IN DANGER";
        case '8': return "LOST";
        case '9': return "KICKER LOVE";
        case '0': return "YVES DE SHMET";
        default:  return NULL;
    }

}

