//*****************************************************************************
//   +--+
//   | ++----+
//   +-++    |
//     |     |
//   +-+--+  |
//   | +--+--+
//   +----+    Copyright (c) 2011 Code Red Technologies Ltd.
//
// timer_irq.c provides example interrupt handlers for each of the 4 timers to
// be found in the LPC1768 MCU fitted to the LPCXpresso176x development board.
// The interrupt handlers in this case simply increment a counter and toggle
// the state of LED2.
//
// Software License Agreement
//
// The software is owned by Code Red Technologies and/or its suppliers, and is
// protected under applicable copyright laws.  All rights are reserved.  Any
// use in violation of the foregoing restrictions may subject the user to criminal
// sanctions under applicable laws, as well as to civil liability for the breach
// of the terms and conditions of this license.
//
// THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
// OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
// USE OF THIS SOFTWARE FOR COMMERCIAL DEVELOPMENT AND/OR EDUCATION IS SUBJECT
// TO A CURRENT END USER LICENSE AGREEMENT (COMMERCIAL OR EDUCATIONAL) WITH
// CODE RED TECHNOLOGIES LTD.

#include "LPC17xx.h"
#include "leds.h"
#include "timer.h"

volatile uint32_t msTicks; // counter for 1ms SysTicks

extern uint8_t fl_start_T1;
extern uint8_t fl_start_T2;
extern uint32_t Time_ms;
static uint32_t timetick = 0;

void TIMER0_IRQHandler (void)
{
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  timer0_counter++;
  led2_invert();
  return;
}

void TIMER1_IRQHandler (void)
{
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  timer1_counter++;
  led2_invert();
  return;
}

void TIMER2_IRQHandler (void)
{
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  timer2_counter++;
  led2_invert();
  return;
}
void TIMER3_IRQHandler (void)
{
  LPC_TIM3->IR = 1;			/* clear interrupt flag */
  timer3_counter++;
  led2_invert();
  return;
}


// ****************
//  SysTick_Handler - just increment SysTick counter
void SysTick_Handler(void) {
  msTicks++;

  if(fl_start_T1||fl_start_T2){
	  led2_on();
	  solenoid_on();
	  if(timetick++ >= Time_ms){
		  fl_start_T1 = 0;
		  fl_start_T2 = 0;
		  timetick = 0;
		  led2_off();
		  solenoid_off();
	  }
  }
}

// ****************
// systick_delay - creates a delay of the appropriate number of Systicks (happens every 1 ms)
__INLINE static void systick_delay (uint32_t delayTicks) {
  uint32_t currentTicks;

  currentTicks = msTicks;	// read current tick counter
  // Now loop until required number of ticks passes.
  while ((msTicks - currentTicks) < delayTicks);
}

