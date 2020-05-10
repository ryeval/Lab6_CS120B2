/*	Author: ryan
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include "timer.h"
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{start, zero, one, two} state;
unsigned char lights;
void Tick(){
	switch(state){
		case start:
			state = zero;
			break;
		case zero:
			state = one;
			break;
		case one:
			state = two;
			break;
		case two:
			state = zero;
			break;
	}
	switch(state){
		case start:
			break;
		case zero:
			lights = 0x01;
			break;
		case one:
			lights = 0x02;
			break;
		case two:
			lights = 0x04;
			break;
	}
	PORTB = lights;
}	

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF;	PORTB = 0x00;
	TimerSet(1000);
	TimerOn();

    /* Insert your solution below */
    while (1) {
	Tick();
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
