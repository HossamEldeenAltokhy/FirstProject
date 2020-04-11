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

int main(void) {




    LCD_Init();

    resetPIN(Buzzer, portA); // Turn Buzzer OFF
    PINDas(BUTTON2, IN);
    PINDas(LED, OUT);
    resetPIN(LED, portD); // LED2 init OFF

    LCD_String(y);
    while (1) {
        if (isPressedD(BUTTON2)) {
            flag ^= 1;
            togglePIND(LED);

            if (flag) {
                LCD_Clear();
                LCD_String(x);
            } else {
                LCD_Clear();
                LCD_String(y);
            }
            _delay_ms(200);
        }

    }
}

