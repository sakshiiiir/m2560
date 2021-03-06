/******************************************************
 |		#########   #########	#########	          |
 |		    #       #       #   #		              |
 | 		    #       #       #   #		              |
 |		    #       #########	######		          |
 |		    #       #  #        #		              |
 |		    #       #     #     #		              |
 |		    #       #       #   #		              |
 *******************************************************/
/*************INDEX******************
*BUG – a known bug that should be corrected.
*FIXME – should be corrected.
*HACK – a workaround.
*TODO – something to be done.
*UNDONE – a reversal or "roll back" of previous code.
*XXX – warn other programmers of problematic or misguiding code
*/


/*
TODO: Add Toggle Mode in pinMode and digitalWrite function
*/
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#ifndef F_CPU
#define F_CPU 16000000UL   //SET CPU CLOCK
#define FOSC 16000000
#endif
#include <util/delay.h>
/**************************************************************************************************************************/
const uint8_t OUTPUT=1,INPUT=0;
const uint8_t HIGH=1,LOW=0;
const uint8_t RISING=2,FALLING=3,CHANGE=4;      

//pinMapping
int c[60]={0,1,4,5,5,3,3,4,5,6,4,5,6,7,1,0,1,0,3,2,1,0,6,7,0,1,2,3,4,5,6,7,7,6,5,4,3,2,1,0,7,2,1,0,7,6,5,4,3,2,1,0,3,2,1,0};

char d[60]={'e','e','e','e','g','e','h','h','h','h','b','b','b','b','j','j','h','h','d','d','a','a','a','a','a','a','a','a','c','c','c','c','c','c','c','c','d','g','g','g','l','l','l','l','l','l','l','l','b','b','b','b'};
	

/**************************************************************************************************************************/

//Function declaration
void analogWrite(uint8_t ,uint8_t);
int analogRead(uint8_t);
void delay(unsigned long);
void delayMicroseconds(long unsigned);
double map(double,double,double,double,double);
double constrain(double,double,double);
void attachIntterupt(int, void *,int);
void (*cAllisr)(void); //function pointer used in ISR()
void softwareInterrupt(void *);
void (*uSerfun(void));
void pinMode(uint8_t , uint8_t );
static void turnOffPWM(uint8_t );
void digitalWrite(uint8_t , uint8_t );
int digitalRead(uint8_t );
long unsigned int microsecondsToInches(long unsigned int);
long unsigned int microsecondsToCentimeters(long unsigned int);
void setup(void);
void loop(void);

/**************************************************************************************************************************/
//Functions:

void pinMode(uint8_t pInno,uint8_t mOde)
{
	int l;
  	if(mOde==0)
    { 
    	switch(d[pInno]){
 
          	case'b':
                  DDRB&=~(1<<c[pInno]);
		           break;
          	case'c':
                 DDRC&=~(1<<c[pInno]);
		          break;
          	case'd':
                 DDRD&=~(1<<c[pInno]);
		          break;
	      	case'e':
                  DDRE&=~(1<<c[pInno]);
		           break;
		    case'g':
                  DDRG&=~(1<<c[pInno]);
		           break;
			case'h':
                  DDRH&=~(1<<c[pInno]);
				  break;
		    case'j':
                  DDRJ&=~(1<<c[pInno]);
		          break;
			case'l':
                  DDRL&=~(1<<c[pInno]);
		          break;	        		   		   	  	  		 		 			 
     	}  
	}
	else{          
			switch(d[pInno])
         	{
	 
	        	case'b':
	            	DDRB|=(1<<c[pInno]);
			    	break;
	          	case'c':
	                DDRC|=(1<<c[pInno]);
			        break;
	          	case'd':
	                DDRD|=(1<<c[pInno]);
			        break;
		      	case'e':
	                DDRE|=(1<<c[pInno]);
			        break;
			    case'g':
	                DDRG|=(1<<c[pInno]);
			        break;
			 	case'h':
	                DDRH|=(1<<c[pInno]);
			        break;
			    case'j':
	                DDRJ|=(1<<c[pInno]);
			        break;
				case'l':
	                DDRL|=(1<<c[pInno]);
			        break;	  		 		 			 
	     }  
	}
}

void digitalWrite (uint8_t pInno ,uint8_t mOde)		 
{
   if(mOde==0)
        { switch(d[pInno])
         {
	 
	          case'b':
	                  PORTB&=~(1<<c[pInno]);
			           break;
	          case'c':
	                 PORTB&=~(1<<c[pInno]);
			          break;
	          case'd':
	                 PORTD&=~(1<<c[pInno]);
			          break;
				
		      case'e':
	                  PORTE&=~(1<<c[pInno]);
			           break;

			     case'g':
	                  PORTG&=~(1<<c[pInno]);
			           break;
			 case'h':
	                  PORTH&=~(1<<c[pInno]);
			           break;
		     
			     case'j':
	                  PORTJ&=~(1<<c[pInno]);
			           break;
				     case'l':
	                  PORTL&=~(1<<c[pInno]);
			           break;	        		   		   	  	  		 		 			 
	     }  }
	else{          switch(d[pInno])
         {
	 
	          case'b':
	                 PORTB|=(1<<c[pInno]);
			           break;
	          case'c':
	                 PORTC|=(1<<c[pInno]);
			          break;
	          case'd':
	                 PORTD|=(1<<c[pInno]);
			          break;
				    
		      case'e':
	                  PORTE|=(1<<c[pInno]);
			           break;

			     case'g':
	                  PORTG|=(1<<c[pInno]);
			           break;
			 case'h':
	                  PORTH|=(1<<c[pInno]);
			           break;
		     /*case'i':
	                  PORTI|=(1<<c[pInno]);
			           break;*/
			     case'j':
	                  PORTJ|=(1<<c[pInno]);
			           break;
				     case'l':
	                  PORTL|=(1<<c[pInno]);
			           break;	  		 		 			 
	     }  
}
		 }
		 

uint8_t digitalRead(int pInno)
{  
	uint8_t z;				//not a good practice
	uint8_t x;				//not a good practice
   switch(d[pInno])
         {
	 
	          case'b':
	                  z=PINB&(1<<c[pInno]);
			           break;
	          case'c':
	                  z=PINC&(1<<c[pInno]);
			          break;
	          case'd':
	                  z=PIND&(1<<c[pInno]);
			          break;
				
		      case'e':
	                   z=PINE&(1<<c[pInno]);
			           break;

			     case'g':
	                   z=PING&(1<<c[pInno]);
			           break;
			 case'h':
	                  z=PINH&(1<<c[pInno]);
			           break;
		     
			     case'j':
	                   z=PINJ&(1<<c[pInno]);
			           break;
				     case'l':
	                   z=PINL&(1<<c[pInno]);
			           break;
					   return z;	        		   		   	  	  		 		 			 
	     }  
}
//FIXM
/*static void turnOffPWM(uint8_t tImer)
{
	switch (tImer)
	{
		#if defined(TCCR1A) && defined(COM1A1)
		case TIMER1A:   cbi(TCCR1A, COM1A1);    break;
		#endif
		#if defined(TCCR1A) && defined(COM1B1)
		case TIMER1B:   cbi(TCCR1A, COM1B1);    break;
		#endif
		#if defined(TCCR1A) && defined(COM1C1)
		case TIMER1C:   cbi(TCCR1A, COM1C1);    break;
		#endif
		
		#if defined(TCCR2) && defined(COM21)
		case  TIMER2:   cbi(TCCR2, COM21);      break;
		#endif
		
		#if defined(TCCR0A) && defined(COM0A1)
		case  TIMER0A:  cbi(TCCR0A, COM0A1);    break;
		#endif
		
		#if defined(TCCR0A) && defined(COM0B1)
		case  TIMER0B:  cbi(TCCR0A, COM0B1);    break;
		#endif
		#if defined(TCCR2A) && defined(COM2A1)
		case  TIMER2A:  cbi(TCCR2A, COM2A1);    break;
		#endif
		#if defined(TCCR2A) && defined(COM2B1)
		case  TIMER2B:  cbi(TCCR2A, COM2B1);    break;
		#endif
		
		#if defined(TCCR3A) && defined(COM3A1)
		case  TIMER3A:  cbi(TCCR3A, COM3A1);    break;
		#endif
		#if defined(TCCR3A) && defined(COM3B1)
		case  TIMER3B:  cbi(TCCR3A, COM3B1);    break;
		#endif
		#if defined(TCCR3A) && defined(COM3C1)
		case  TIMER3C:  cbi(TCCR3A, COM3C1);    break;
		#endif

		#if defined(TCCR4A) && defined(COM4A1)
		case  TIMER4A:  cbi(TCCR4A, COM4A1);    break;
		#endif					
		#if defined(TCCR4A) && defined(COM4B1)
		case  TIMER4B:  cbi(TCCR4A, COM4B1);    break;
		#endif
		#if defined(TCCR4A) && defined(COM4C1)
		case  TIMER4C:  cbi(TCCR4A, COM4C1);    break;
		#endif			
		#if defined(TCCR4C) && defined(COM4D1)
		case TIMER4D:	cbi(TCCR4C, COM4D1);	break;
		#endif			
			
		#if defined(TCCR5A)
		case  TIMER5A:  cbi(TCCR5A, COM5A1);    break;
		case  TIMER5B:  cbi(TCCR5A, COM5B1);    break;
		case  TIMER5C:  cbi(TCCR5A, COM5C1);    break;
		#endif
	}
}
*/
long unsigned int microsecondsToInches(long unsigned int mIcroseconds) 
{
  // According to Parallax's datasheet for the PING))), there are 73.746
  // microseconds per inch (i.e. sound travels at 1130 feet per second).
  // This gives the distance travelled by the ping, outbound and return,
  // so we divide by 2 to get the distance of the obstacle.
  return (mIcroseconds*0.00669/ 2);
}

long unsigned int microsecondsToCentimeters(long unsigned int microseconds) 
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return (microseconds*0.17/ 2);
}

unsigned long pulseIn(volatile uint8_t pInno, uint8_t vAlue)
{ char x;
  TCCR2A = (1 << WGM21) | (1 << COM2A1) | (1 << FOC2A) | (0 << COM2A0) | (0 << WGM20); //initializing in CTC mode
  TCCR2A = (1 << CS20);
  unsigned long mAxloops = 500000;
  unsigned long wIdth = 0;
  // wait for any previous pulse to end
  switch(d[pInno]){
            case'b':
	               { while (((PINB) && ((pInno%8))) == vAlue)
	              {
		          if (--mAxloops == 0)
		            return 0;
	                }
             // wait for the pulse to start  
              while (((PINB) && ((pInno%8))) != vAlue)
	              {
		     if (--mAxloops == 0) 
		          return 0;
	           }
            // wait for the pulse to stop
             while (((PINB) && ((pInno%8))) == vAlue)
	                   {
	               	if (++wIdth == mAxloops)
		          return 0;
	                      }
              return wIdth;
                    }  break;
 case'c':
	                 { while (((PINC) && ((pInno%8))) == vAlue)
	                {
		              if (--mAxloops == 0)
		               return 0;
	                   }
  // wait for the pulse to start  
                  while (((PINC) && ((pInno%8))) != vAlue)
	                  {
		              if (--mAxloops == 0)
		                 return 0;
	                      }
  // wait for the pulse to stop
                while (((PINC) && ((pInno%8))) == vAlue)
	                 {
                 		if (++wIdth == mAxloops)
                  		return 0;
                     	    }
                     return wIdth;
                         }break;
						 
	 case'd':
	     
	                 { while (((PIND) && ((pInno%8))) == vAlue)
	                {
		              if (--mAxloops == 0)
		               return 0;
	                   }
  // wait for the pulse to start  
                  while (((PIND) && ((pInno%8))) != vAlue)
	                  {
		              if (--mAxloops == 0)
		                 return 0;
	                      }
  // wait for the pulse to stop
                while (((PIND) && ((pInno%8))) == vAlue)
	                 {
                 		if (++wIdth == mAxloops)
                  		return 0;
                     	    }
                     return wIdth;
                         } break; 		//case'h':
				  //  DDRH|(0<<c[pInno]);
	case'e':
	                  
	                 { while (((PINE) && ((pInno%8))) == vAlue)
	                {
		              if (--mAxloops == 0)
		               return 0;
	                   }
  // wait for the pulse to start  
                  while (((PINE) && ((pInno%8))) != vAlue)
	                  {
		              if (--mAxloops == 0)
		                 return 0;
	                      }
  // wait for the pulse to stop
                while (((PINE) && ((pInno%8))) == vAlue)
	                 {
                 		if (++wIdth == mAxloops)
                  		return 0;
                     	    }
                     return wIdth;
                         } break; 			    
	                  
case'h':
	                 
	                 { while (((PINH) && ((pInno%8))) == vAlue)
	                {
		              if (--mAxloops == 0)
		               return 0;
	                   }
  // wait for the pulse to start  
                  while (((PINH) && ((pInno%8))) != vAlue)
	                  {
		              if (--mAxloops == 0)
		                 return 0;
	                      }
  // wait for the pulse to stop
                while (((PINH) && ((pInno%8))) == vAlue)
	                 {
                 		if (++wIdth == mAxloops)
                  		return 0;
                     	    }
                     return wIdth;
                         } break;  
case'j':
	                  
	                 { while (((PINJ) && ((pInno%8))) == vAlue)
	                {
		              if (--mAxloops == 0)
		               return 0;
	                   }
  // wait for the pulse to start  
                  while (((PINJ) && ((pInno%8))) != vAlue)
	                  {
		              if (--mAxloops == 0)
		                 return 0;
	                      }
  // wait for the pulse to stop
                while (((PINJ) && ((pInno%8))) == vAlue)
	                 {
                 		if (++wIdth == mAxloops)
                  		return 0;
                     	    }
                     return wIdth;
                         }  
			           break;
case 'l':
	                  
	                 { while (((PINL) && (((pInno%8)%8))) == vAlue)
	                {
		              if (--mAxloops == 0)
		               return 0;
	                   }
  // wait for the pulse to start  
                  while (((PINL) && ((pInno%8))) != vAlue)
	                  {
		              if (--mAxloops == 0)
		                 return 0;
	                      }
  // wait for the pulse to stop
                while (((PINL) && ((pInno%8))) == vAlue)
	                 {
                 		if (++wIdth == mAxloops)
                  		return 0;
                     	    }
                     return wIdth;
                         }  
			           break;	        		   		   	  	  		 		 			 
	     }  
					 }					 	


class Serial
{
	public:
	void start( unsigned int BAUD){
		/*Set baud rate */int uBrr;
		uBrr=FOSC/16/BAUD-1;
		UBRR0H = (unsigned char)(uBrr>>8);
		UBRR0L = (unsigned char)uBrr;
		/*Enable receiver and transmitter */
		UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	}
	/* Set frame format: 8data, 2stop bit */
	void send( unsigned char data ){
		/* Wait for empty transmit buffer */
		while ( !( UCSR0A & (1<<UDRE0)) )
		;
		/* Put data into buffer, sends the data */
		UDR0 = data;
		_delay_ms(100);
	}
	unsigned char get( void ){
		/* Wait for data to be received */
		while ( !(UCSR0A & (1<<RXC0)) )
		;
		/* Get and return received data from buffer */
		return UDR0;
	}
	void flush(void){
		unsigned char dUmmy;
		while ( UCSR0A & (1<<RXC0) ) dUmmy = UDR0;
	}

	void end(void){
		flush();
		UCSR0B&=0xe7;	//disabling RXEN & TXEN
	}

};

class Serial1
{
	public:
	void start( unsigned int BAUD){
int uBrr;		/*Set baud rate */
		uBrr=FOSC/16/BAUD-1;
		UBRR1H = (unsigned char)(uBrr>>8);
		UBRR1L = (unsigned char)uBrr;
		/*Enable receiver and transmitter */
		UCSR1B = (1<<RXEN1)|(1<<TXEN1);
	}
	/* Set frame format: 8data, 2stop bit */
	void send( unsigned char data ){
		/* Wait for empty transmit buffer */
		while ( !( UCSR1A & (1<<UDRE1)) )
		;
		/* Put data into buffer, sends the data */
		UDR1= data;
		_delay_ms(100);
	}
	unsigned char get( void ){
		/* Wait for data to be received */
		while ( !(UCSR1A & (1<<RXC1)) )
		;
		/* Get and return received data from buffer */
		return UDR1;
	}
	void flush(void){
		unsigned char dUmmy;
		while ( UCSR1A & (1<<RXC1) ) dUmmy = UDR1
		;
	}

	void end(void){
		flush();
		UCSR1B&=0xe7;	//disabling RXEN & TXEN
	}

};
class Serial2
{
	public:
	void start( unsigned int BAUD){
		/*Set baud rate */
int uBrr;	  
		uBrr=(FOSC/16/BAUD-1);
		UBRR2H = (unsigned char)(uBrr>>8);
		UBRR2L = (unsigned char)uBrr;
		/*Enable receiver and transmitter */
		UCSR2B = (1<<RXEN2)|(1<<TXEN2);
	}
	/* Set frame format: 8data, 2stop bit */
	void send( unsigned char data ){
		/* Wait for empty transmit buffer */
		while ( !( UCSR2A & (1<<UDRE2)) )
		;
		/* Put data into buffer, sends the data */
		UDR2= data;
		_delay_ms(100);
	}
	unsigned char get( void ){
		/* Wait for data to be received */
		while ( !(UCSR2A & (1<<RXC2)) )
		;
		/* Get and return received data from buffer */
		return UDR2;
	}
	void flush(void){
		unsigned char dUmmy;
		while ( UCSR2A & (1<<RXC2) ) dUmmy = UDR1
		;
	}

	void end(void){
		flush();
		UCSR2B&=0xe7;	//disabling RXEN & TXEN
	}

};
class Serial3
{
	public:
	void start( unsigned int BAUD){
		int uBrr;/*Set baud rate */
		  uBrr=(FOSC/16/BAUD-1);
		UBRR3H = (unsigned char)(uBrr>>8);
		UBRR3L = (unsigned char)uBrr;
		/*Enable receiver and transmitter */
		UCSR3B = (1<<RXEN3)|(1<<TXEN3);
	}
	/* Set frame format: 8data, 2stop bit */
	void send( unsigned char data ){
		/* Wait for empty transmit buffer */
		while ( !( UCSR3A & (1<<UDRE3)) )
		;
		/* Put data into buffer, sends the data */
		UDR3= data;
		_delay_ms(100);
	}
	unsigned char get( void ){
		/* Wait for data to be received */
		while ( !(UCSR3A & (1<<RXC3)) )
		;
		/* Get and return received data from buffer */
		return UDR3;
	}
	void flush(void){
		unsigned char dUmmy;
		while ( UCSR3A & (1<<RXC3) ) dUmmy = UDR1
		;
	}

	void end(void){
		flush();
		UCSR3B&=0xe7;	//disabling RXEN & TXEN
	}

};
void initADC()
{
	ADMUX=(1<<REFS0);				//Aref=AVcc
	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1);		//ADC enabled, Prescaler 64
}

int analogRead(int (pInno))
{
        //prescalar set to default
  	ADMUX=(1<<REFS0)|(0<<REFS1);
  	ADCSRA|=(1<<ADEN);
        ADMUX|=(pInno%8);//chose value from 0 to 7 to chose adc pin accordingly
        ADCSRA|=(1<<ADEN);
        ADCSRA|=(1<<ADSC);
	while(ADCSRA&(1<<ADSC));
	return (ADC);
}

void analogWrite(uint8_t pInno,uint8_t dUtycY)
{
  TCCR1B=(1<<CS11)|(1<<CS10);
  TCCR1A=(1<<WGM10)|(1<<WGM12)|(1<<COM1A1)|(1<<COM1B1);
	if((pInno%8)==1)
	{
	  OCR1A=dUtycY;
	}
	if((pInno%8)==2)
	{
          OCR1B=dUtycY;
	}
}

float x=0;
int millis()
{
	float l;
	l=x*0.16+0.00000625*TCNT0;
        return l;
}

void tinit(void)
{ 
	TCCR0A|=(1<<WGM01);
        TCCR0A|=(1<<CS00);
	TIMSK0|=(1<<TOV0);
        TCNT0=0;
}


ISR(TIMER0_OVF_vect)
{
	x++;	
}	

void delay(unsigned long mIllisec)
{
	int i;
	for(i=0;i<mIllisec;i++)
	{
		_delay_ms(1);
	}
	return;
}

void delayMicroseconds(unsigned long mIcrosec)
{
	int i;
	for(i=0;i<mIcrosec;i++)
	{
		_delay_us(1);
	}
	return;
}

double map(double vAlue, double fromLow, double fromHigh, double toLow, double toHigh)
{
	return ((vAlue-fromLow)/abs(fromHigh-fromLow)*abs(toHigh+toLow));
}

double constrain(double nUm,double uPper,double lOwer)
{
	if(nUm<uPper){
		return uPper;}
	else if(nUm>lOwer){
		return lOwer;}
	else 
	return nUm;	
}
void attachIntterupt(int pIn, void (*iSrfunc)(void), int cOmpare)		//cOmpare:LOW=0,HIGH1,RISING=2,FALLING=3
{
	sei();
	cAllisr=iSrfunc;
	switch(pIn)	  //enabling interrupt pin
	{
		case 0:
		EIMSK|=1<<INT0;
		switch(cOmpare){
			case 2:
			EICRA|=(1<<ISC00)|(1<<ISC01);
			break;
			case 3:
			EICRA|=(0<<ISC00)|(1<<ISC01);
			break;
			case 4:
			EICRA|=(1<<ISC00)|(0<<ISC01);
			break;
			default:
			EICRA|=(0<<ISC00)|(0<<ISC01);
		}
		break;

		case 1:
		EIMSK|=1<<INT1;
                switch(cOmpare)
		{
			case 2:
			EICRA|=(1<<ISC10)|(1<<ISC11);
			break;
			case 3:
			EICRA=(0<<ISC10)|(1<<ISC11);
			break;
			case 4:
			EICRA|=(1<<ISC10)|(0<<ISC11);
			break;
			default:
			EICRA|=(0<<ISC10)|(0<<ISC11);
		}
		break;
		
		case 2:
		EIMSK|=1<<INT2;
		switch(cOmpare)
		{
			case 2:
			EICRA|=(1<<ISC20)|(1<<ISC21);
			break;
			case 3:
			EICRA=(0<<ISC20)|(1<<ISC21);
			break;
			case 4:
			EICRA|=(1<<ISC20)|(0<<ISC21);
			break;
			default:
			EICRA|=(0<<ISC20)|(0<<ISC21);
		}
		break;
		
		case 3:
		EIMSK|=1<<INT3;
		switch(cOmpare)
		{
			case 2:
			EICRA|=(1<<ISC30)|(1<<ISC31);
			break;
			case 3:
			EICRA=(0<<ISC30)|(1<<ISC31);
			break;
			case 4:
			EICRA|=(1<<ISC30)|(0<<ISC31);
			break;
			default:
			EICRA|=(0<<ISC30)|(0<<ISC31);
		}
		break;
		
		case 4:
		EIMSK|=1<<INT4;
                switch(cOmpare)
		{
			case 2:
			EICRB|=(1<<ISC40)|(1<<ISC41);
			break;
			case 3:
			EICRB=(0<<ISC40)|(1<<ISC41);
			break;
			case 4:
			EICRB|=(1<<ISC40)|(0<<ISC41);
			break;
			default:
			EICRB|=(0<<ISC40)|(0<<ISC41);
		}
		break;
		
		case 5:
		EIMSK|=1<<INT5;
		switch(cOmpare)
		{
			case 2:
			EICRB|=(1<<ISC50)|(1<<ISC51);
			break;
			case 3:
			EICRB=(0<<ISC50)|(1<<ISC51);
			break;
			case 4:
			EICRB|=(1<<ISC50)|(0<<ISC51);
			break;
			default:
                 	EICRB|=(0<<ISC40)|(0<<ISC41);
			
		}
		break;
		
		case 6:
		EIMSK|=1<<INT6;
	        switch(cOmpare)
		{
			case 2:
			EICRB|=(1<<ISC60)|(1<<ISC61);
			break;
			case 3:
			EICRB=(0<<ISC60)|(1<<ISC61);
			break;
			case 4:
			EICRB|=(1<<ISC60)|(0<<ISC61);
			break;
			default:
			EICRB|=(0<<ISC60)|(0<<ISC61);
			
		}
		break;
		
		case 7:
		EIMSK|=1<<INT7;
		switch(cOmpare)
		{
			case 2:
			EICRB|=(1<<ISC70)|(1<<ISC71);
			break;
			case 3:
			EICRB=(0<<ISC70)|(1<<ISC71);
			break;
			case 4:
			EICRB|=(1<<ISC70)|(0<<ISC71);
			break;
			default:
			EICRB|=(0<<ISC70)|(0<<ISC71);
		}
		break;
		
	        default:EICRA|=(0<<ISC01)|(0<<ISC00);
	}
}
ISR(INT0_vect)
{
   cAllisr();
}
ISR(INT1_vect)
{
   cAllisr();
}
ISR(INT2_vect)
{
   cAllisr();
}
ISR(INT3_vect)
{
   cAllisr();
}
ISR(INT4_vect)
{
    cAllisr();
}
ISR(INT5_vect)
{
    cAllisr();
}
ISR(INT6_vect)
{
    cAllisr();
}
ISR(INT7_vect)
{ 
    cAllisr();
}

/*void softwareInterrupt(void (*iSrfun(void)))
{
	uSerfun=iSrfun;
        TCCR1A|=(1<<WGM11);
	TCCR1B|=(1<<WGM12)|(1<<WGM13)|(1<<CS10); // fast pwm mode and prescalar is set as 1
	TIMSK1|=(1<<TOIE1); // overflow interrupt flag is set
}

ISR(TIMER1_OVF_vect)
{
	uSerfun(); 
}
*/

int main(){
	setup();
	while(1){
		loop();
	}
}
