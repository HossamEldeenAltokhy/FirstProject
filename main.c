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

void ADC_init() {
    ADMUX = 0x00; // Channel 0
    SFIOR |= (1<<ADTS1);
    ADCSRA |= (1 << ADEN) | (1<<ADATE)|(1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    
}

void selectChannel(unsigned int channelNo) { // 0~7
    if (channelNo < 8) { // 00000001| 00000000
        ADMUX &= ~(7 << 0); // 00000111  11111000
        ADMUX |= channelNo;
    } else {
        //# warning ""
    }
}

void startConv() {
    ADCSRA |= (1 << ADSC);
}

int getADCdata() {
    int data = 0;
    data = ADCL;
    data |= (ADCH << 8);

    return data;
}

int getADCdataL() {
    int data = 0;
    data = (ADCH << 2);
    return data;
}

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


int main(void) {

    PORTCas(OUT);
    PORTDas(OUT);
    
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













