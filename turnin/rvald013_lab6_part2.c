/*	Author: ryan
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #6  Exercise #2
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

enum States{start, zero, one, two, secretOne, catch} state;
unsigned char lights;
unsigned char btn;

void Tick(){
	btn = ~PINA;
	switch(state){
		case start:
			state = zero;
			break;
		case zero:
			state = one;
			break;
		case one:			
			state = btn ? catch : two;
			break;
		case two:
			state = secretOne;
			break;
		case secretOne:
			state = btn ? catch : zero;
			break;
		case catch:
			state = btn ? zero : catch;
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
		case secretOne:
			lights = 0x02;
			break;
		case catch:
			lights = 0x02;
			break;
	}
	PORTB = lights;
}	

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF;
	DDRB = 0xFF;	PORTB = 0x00;
	TimerSet(300);
	TimerOn();
	state = start;
    /* Insert your solution below */
    while (1) {
	Tick();
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
