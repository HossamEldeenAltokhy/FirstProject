/*
 * File:   main.c
 * Author: Hossam Eldeen Altokhy
 *
 * Created on April 4, 2020, 6:24 PM
 */
#define F_CPU 16000000UL

// Built-in headers
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// User-defined Headers
#include "Config.h"
#include "DIO.h"
#include "lcd.h"


#define BUTTON2        2
#define LED            3
#define Buzzer         3

#define portA           1
#define portB           2
#define portC           3
#define portD           4

int i = 0;

char x[] = "LED is ON";
char y[] = "LED is OFF";
char flag = 0;

void INT0_init() {
    MCUCR |= (1 << ISC01) | (1 << ISC00); // Rising Edge
    GICR |= (1 << INT0);
}

void INT1_init() {
    MCUCR |= (1 << ISC11) | (1 << ISC10); // Rising Edge
    GICR |= (1 << INT1);
}

void INT2_init() {
    MCUCSR |= (1 << ISC2); // Rising Edge
    GICR |= (1 << INT2);
}

// _VECTOR(1)
ISR(INT0_vect) {
    // CODE
    flag ^= 1;
    togglePIND(LED);

    if (flag) {
        LCD_Clear();
        LCD_String(x);
    } else {
        LCD_Clear();
        LCD_String(y);
    }
}


int main(void) {

    INT0_init();

    // Enable Global Interrupt
    sei();

    LCD_Init();
    resetPIN(Buzzer, portA); // Turn Buzzer OFF
    PINDas(BUTTON2, IN);
    PINDas(LED, OUT);
    resetPIN(LED, portD); // LED2 init OFF
    LCD_String(y);

    while (1) {


//        _delay_ms(200); // wait till user finger up

    }
}









/*
 
 * 
 * MCUCR:

INT0:

ISC01 -- > 0  , ISC00 -- > 0    (LOW LEVEL)
ISC01 -- > 0  , ISC00 -- > 1	(Toggle)
ISC01 -- > 1  , ISC00 -- > 0	(Falling Edge)
ISC01 -- > 1  , ISC00 -- > 1	(Rising Edge)

INT1:

ISC11 -- > 0  , ISC10 -- > 0    (LOW LEVEL)
ISC11 -- > 0  , ISC10 -- > 1	(Toggle)
ISC11 -- > 1  , ISC10 -- > 0	(Falling Edge)
ISC11 -- > 1  , ISC10 -- > 1	(Rising Edge)
------------------------------------------
MCUCSR:

INT2:

ISC2 -- > 0 (Falling Edge)
ISC2 -- > 1 (Rising Edge)

------------------------------------------
GICR:

INT0:
INT0 -- > 1  Enabled

INT1:
INT1 -- > 1  Enabled

INT2:
INT2 -- > 1  Enabled
------------------------------------------

GIFR:
------------------------------------------
i-bit SREG
sei();
cli();
------------------------------------------

 
 
 */










