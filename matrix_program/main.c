/*
 * Pierwszy.c
 *
 * Created: 20.10.2021 11:33:27
 * Author : marcin
 */
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

	#define W1_ON PORTA &=~(1<<4) //zaświecenie cyfry1 na PC0
	#define W1_OFF PORTA |=(1<<4) //zgaszenie cyfry1 na PC0


char a_p[]={
		1, 2, 8, 16, 32, 64, 128};

char a_n[][8]={
		{0b10101010,0b01010101,0b10101010,0b11100001,0b11100001,0b00100010,0b01000100,0b10001000}
		//{0x18,0x3c,0x3c,0x18,0x18,0x18,0x18,0x18}
		//{0x00,0x02,0x0c,0x1c,0x38,0x70,0x70,0x80},
		//{0x00,0x18,0x24,0x42,0x70,0x42,0x42,0x00}

};


int main(void){

//    DDRA |= 0xff; //ustawiamy na wyjsice
//    PORTA |= 0xff;//stan wysoki wyjście PA0


//    DDRC |= 0xff; //ustawiamy na wyjsice
//    PORTC &= ~0xff;//stan niski wyjście PC7






    DDRA = 0xFF; // ustaw wyjście
    DDRC = 0xFF; //kierynek wyjście

	int i=0;

	while(1){
		PORTC = a_p[i];
		PORTA = ~a_n[0][i];
		_delay_ms(2);
		i+=1;

		if(i>7) i=0;
	}


}



//zrobic sterowanie przez multipleksowanie
//kwestja podłacznia
