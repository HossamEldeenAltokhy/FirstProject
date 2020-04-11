/*
 * File:   main.c
 * Author: Hossam Eldeen Altokhy
 *
 * Created on April 4, 2020, 6:24 PM
 */

#include <avr/io.h>
//#include <util/delay.h>
#include "Config.h"
#include "DIO.h"

#define BUTTON         0
#define LED            3

#define portA           1
#define portB           2
#define portC           3
#define portD           4

int main(void) {

    // Data Direction Register
//    DDRA = 0xFF; // OUTPUT PORT
    PORTAas(OUT);
    PORTA = 0x00; // setPORTA(HIGH);
    PORTCas(OUT);
    PORTC = 0x00;
    PINBas(BUTTON, IN);
    PINDas(LED0, OUT);
    
    setPIN(LED0, portC);
    while (1) {
        // Loop until power OFF
        if (isPressedB(BUTTON)) { //PINA & (1<<PIN_number)
            //True Condition
            //            PORTA |= (1<<LED); // Turn LED ON
            setPIN(LED, portD);
        } else {
            // False Condition
            //            PORTA &= ~(1<<LED);// Turn LED OFF
            resetPIN(LED, portD);
        }
    }
}

