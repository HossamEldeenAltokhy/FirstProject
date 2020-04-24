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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// User-defined Headers
#include "Config.h"
#include "DIO.h"
#include "lcd.h"
#include "ADC.h"


#define BUTTON2        2
#define LED            3
#define Buzzer         3

#define portA           1
#define portB           2
#define portC           3
#define portD           4

//#define stepValue      48828125?

char message[] = "Welcome";
char str1[] = "Volt = ";
char str2[] = " mV";
char cl[] = "    ";


ISR(INT0_vect){
    static int i = 1 ;
    
    if(i){
        startConv();
        i = 0;
    }
}

ISR(ADC_vect) {
    static int switcher = 0;
    char buffer[20];
    int noOfSteps = getADCdata();


    // convert steps to mV
    int data = (5 * noOfSteps) / 1.024;

    // Display
    itoa(data, buffer, 10);
    if (switcher) {
        LCD_String_xy(1, 7, cl);
        LCD_String_xy(1, 7, buffer);
        selectChannel(0);
        switcher = 0;
    } else {
        LCD_String_xy(0, 7, cl);
        LCD_String_xy(0, 7, buffer);
        selectChannel(1);
        switcher = 1;
    }

    _delay_ms(1000);

    //    Restart Conversion every ISR
//    startConv();
}


void INT0_init() {
    MCUCR |= (1 << ISC01) | (1 << ISC00); // Rising Edge
    GICR |= (1 << INT0);
}

void Timer0_init(){
    
    TCCR0 |= (1<<CS02)| (1<<CS00); // CLKio/ 1024 // Normal Mode
    TIMSK |= (1<<TOIE0);
    
}

ISR(TIMER0_OVF_vect){
    static int i = 1;
    if(i){
        setPORTC(0xFF);
        i=0;
    }
    else{
        setPORTC(0x00);
        i=1;
    }
}

int main(void) {

    PORTCas(OUT);
    PORTDas(OUT);
    Timer0_init();
    INT0_init();
    LCD_Init();
    ADC_init(); // Sensor on ADC0


    sei();
    LCD_String_xy(0, 0, str1);
    LCD_String_xy(0, 13, str2);
    LCD_String_xy(1, 0, str1);
    LCD_String_xy(1, 13, str2);
    startConv();

    while (1) {



    }
}













