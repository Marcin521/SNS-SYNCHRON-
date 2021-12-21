#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#define ENA_ON 	  PORTG |= (1<<3)
#define ENA_OFF   PORTG &= ~(1<<3)

#define M1_Prawo   PORTA |= (1<<4); PORTA &= ~(1<<3) //zamieni�em M1_Lewo na M1_Prawo
#define M1_Lewo  PORTA |= (1<<3); PORTA &= ~(1<<4) //zamieni�em M1_Prawo na M1_Lewo
#define M1_Stop   PORTA &= ~0b00011000

#define M2_Lewo   PORTA |= (1<<6); PORTA &= ~(1<<5)
#define M2_Prawo  PORTA |= (1<<5); PORTA &= ~(1<<6)
#define M2_Stop   PORTA &= ~0b01100000


volatile uint8_t odebrano;

ISR (USART0_RX_vect)
{
     uint8_t tmp=0;
     while (UCSR0A & (1<<RXC0))    // odczytaj ostatni znak (jesli wi�cej znak�w w buforze to go opr�nij)

    	 tmp = UDR0;
     if (!(UCSR0A & 0b00011100))    // jesli nie ma b��du do dana poprawna
     {
         odebrano=tmp;
         //PORTC ^= 128;
     }
}

int main(void)
{

		DDRG = 0b00001000;	//PG3 OUT
		DDRA = 0b01111000;
		DDRE = 0b00011000;

		PORTE = 0b00000000;

		DDRC = (1<<7);

		TCCR3A = 0b11110010;
		TCCR3B = 0b00011010;	//CLK 1/64
		ICR3 = 2000;
		OCR3A = 500;
		OCR3B = 500;

		ENA_ON;

		//Ustawienia UARTa

		UCSR0B = 0x98;	//Receiver enable, Transmitter enable, RX_Interrupt enable
		UCSR0C = 0x06;
		UBRR0L = 102;	//9600 bps (kwarc 16MHz)

		sei();






     while(1)
     {

    	/* if (odebrano==0)//do przodu
    	          {
    		 	 	 PORTC |= 128;
    		 	 	 _delay_ms(500);
    		 	 	 PORTC &= ~128;

    		 	 	 M1_Lewo;
    	             M1_Prawo;
    	             OCR3B = 700;
    	             OCR3A = 5000;
    	             _delay_ms(1000);

    	          }

    	          if (odebrano==1)//lewo
    	          {
    	              M1_Lewo;
    	              M2_Stop;
    	              OCR3B = 500;
    	              OCR3A = 500;
    	              _delay_ms(1000);
    	          }

    	         if (odebrano==2)//prawo
    	          {
    	          */
    	        	 /*PORTC |= 128;
    	        	 _delay_ms(500);
    	        	 PORTC &= ~128;
    	        	 _delay_ms(500);
    	        	 PORTC |= 128;
    	        	 _delay_ms(500);
    	        	 PORTC &= ~128;
    	        	 _delay_ms(500);
		 */
    	 /*
    	              M1_Stop;
    	              M2_Lewo;
    	              OCR3B = 500;
    	              OCR3A = 500;
    	              _delay_ms(1000);
    	          }
    	  */
    	 switch(odebrano)
    	 	{
    	 		case 0: //bling led

    	 			PORTC |= 128;
    		 	 	_delay_ms(500);
    		 	 	PORTC &= ~128;
    		        break;

    	 		case 1: //lewo

    	 			M1_Lewo;
    	            M1_Prawo;
    	            OCR3B = 1000;
    	            OCR3A = 5000;
    	            _delay_ms(1000);
    	            break;


    	        case 2: //prawo

    	        	M1_Stop;
    	            M2_Lewo;
    	            OCR3B = 700;
    	            OCR3A = 700;
    	            _delay_ms(1000);
    	            break;


    	        case 3: //prawo

    	        	M1_Prawo;
    	            M2_Stop;
    	            OCR3B = 700;
    	        	OCR3A = 500;
    	            _delay_ms(1000);
    	            break;


    	        case 4: //zatrzymanie
    	 			M1_Stop;
    	            M2_Stop;
    	            _delay_ms(1000);
    	            break;

    	 			}
     }
}
