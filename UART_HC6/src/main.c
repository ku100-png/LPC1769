/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

// TODO: insert other include files here
#include "type.h"
#include "uart.h"
#include "leds.h"
#include "timer.h"

// TODO: insert other definitions and declarations here
#define TIMER0_INTERVAL	((SystemFrequency/4) - 1)

extern volatile uint32_t UART0Count;
extern volatile uint8_t UART0Buffer[BUFSIZE];
extern volatile uint32_t UART1Count;
extern volatile uint8_t UART1Buffer[BUFSIZE];

extern volatile uint32_t msTicks; // counter for 1ms SysTicks

uint32_t Recieved_number[10];
static uint8_t i = 0;
uint32_t Time_ms;
uint16_t fl_start_T1;
uint16_t fl_start_T2;

int main(void) {

    // TODO: insert code here
	/* SystemClockUpdate() updates the SystemFrequency variable */
	  SystemClockUpdate();
	  init_timer(0, TIMER0_INTERVAL);
	  led2_init(); // Setup GPIO for led2 (on GPIO0.22)
	  solenoid_init(); // Setup GPIO for solenoid (on GPIO0.21)
	  UARTInit(0, 9600);	/* baud rate setting */
	  UARTInit(1, 9600);	/* baud rate setting */

	  // Setup SysTick Timer to interrupt at 1 msec intervals
	  if (SysTick_Config(SystemFrequency / 1000)) {
		  while (1);  // Capture error
	  }

    // Start Timer0
	//  enable_timer(0);

    // Enter an infinite loop, just incrementing a counter
    while(1)
    {
    	if ( UART0Count != 0 )
		{

    		if(UART0Buffer[0] > 47 && UART0Buffer[0] < 58){
    			Recieved_number[i] = UART0Buffer[0] - 48;
    			i++;
    		}else{
    			if(UART0Buffer[0] == '\n'){	// Enter symbol
    				switch (i){
    				case 5:
    					Time_ms = Recieved_number[0]*10000 + Recieved_number[1]*1000 + Recieved_number[2]*100 + Recieved_number[3]*10 + Recieved_number[4];
    					Recieved_number[0] = 0;
    					Recieved_number[1] = 0;
    					Recieved_number[2] = 0;
    					Recieved_number[3] = 0;
    					Recieved_number[4] = 0;
    					break;
    				case 4:
    					Time_ms = Recieved_number[0]*1000 + Recieved_number[1]*100 + Recieved_number[2]*10 + Recieved_number[3];
    					Recieved_number[0] = 0;
						Recieved_number[1] = 0;
						Recieved_number[2] = 0;
						Recieved_number[3] = 0;
    					break;
    				case 3:
    					Time_ms = Recieved_number[0]*100 + Recieved_number[1]*10 + Recieved_number[2];
    					Recieved_number[0] = 0;
						Recieved_number[1] = 0;
						Recieved_number[2] = 0;
    					break;
    				case 2:
    					Time_ms = Recieved_number[0]*10 + Recieved_number[1];
    					Recieved_number[0] = 0;
    					Recieved_number[1] = 0;
    				    break;
    				case 1:
    					Time_ms = Recieved_number[0];
    					Recieved_number[0] = 0;
    				    break;
    				default:
    					break;
    				}
    			}else{	// Button symbol
    				switch (UART0Buffer[0]){
    				case 'L':
    					fl_start_T1 = 1;
    					break;
    				case 'R':
    					fl_start_T2 = 1;
    					break;
    				default :
    					break;
    				}
    			}

    			i = 0;
    		}

    		//led2_invert();
    		LPC_UART0->IER = IER_THRE | IER_RLS;			/* Disable RBR */
    		UARTSend( 0, (uint8_t *)UART0Buffer, UART0Count );
    		UART0Count = 0;
    		LPC_UART0->IER = IER_THRE | IER_RLS | IER_RBR;	/* Re-enable RBR */
		}
		if ( UART1Count != 0 )
		{
			 LPC_UART1->IER = IER_THRE | IER_RLS;			/* Disable RBR */
			 UARTSend( 1, (uint8_t *)UART1Buffer, UART1Count );
			 UART1Count = 0;
			 LPC_UART1->IER = IER_THRE | IER_RLS | IER_RBR;	/* Re-enable RBR */
		}

		if(msTicks%1000 == 0){
			//led2_invert();
		}

    }

    return 0 ;
}

