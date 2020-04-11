/*
 * File:   main.c
 * Author: Hossam Eldeen Altokhy
 *
 * Created on April 4, 2020, 6:24 PM
 */
#define F_CPU 16000000UL


#include <avr/io.h>

#include <util/delay.h>
#include "Config.h"
#include "DIO.h"

#define BUTTON         0
#define LED            3

#define portA           1
#define portB           2
#define portC           3
#define portD           4

int i = 0;

int main(void) {

    int data = 0b00000001;
    PORTCas(OUT);
    PORTDas(OUT);


    while (1) {

        for (i = 0; i < 7; i++) {
            
            setPORTD(data);
            setPORTC(~data);
            data = (data << 1);
            _delay_ms(1000); // 1 second delay

        }
        data = 0x80;
        for (i = 0; i < 7; i++) {
            
            setPORTD(data);
            setPORTC(~data);
            data = (data >> 1);
            _delay_ms(1000); // 1 second delay

        }

        data = 1;
    }
}

