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

int main(void) {

    // TODO: insert code here
	/* SystemClockUpdate() updates the SystemFrequency variable */
	  SystemClockUpdate();
	  init_timer(0, TIMER0_INTERVAL);
	  led2_init(); // Setup GPIO for led2 (on GPIO0.22)
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
    		led2_invert();
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

		if(msTicks%2000 == 0){
			led2_invert();
		}

    }

    return 0 ;
}

