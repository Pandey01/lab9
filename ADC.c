// ADC.c
// Runs on LM4F120/TM4C123
// Provide functions that initialize ADC0
// Last Modified: 11/14/2018
// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

// ADC initialization function 
// Input: none
// Output: none
void ADC_Init(void){
 // --UUU-- Complete this(copy from Lab8)
	uint32_t delay;
		SYSCTL_RCGCGPIO_R |= 0x08;			//turn on clock for port D
		while ( (SYSCTL_RCGCGPIO_R & 0x08) == 0) {};				//wait for clock to stabilize
		GPIO_PORTD_DIR_R &= ~0x04;			//set PD2 as an input
		GPIO_PORTD_AFSEL_R |= 0x04;			//enable alternate function w/ AFSEL register
		GPIO_PORTD_DEN_R &= ~0x04;			//disable digital function
	  GPIO_PORTD_AMSEL_R |= 0x04;			//enable analog function
		SYSCTL_RCGCADC_R |= 0x01;				//turn on ADC clock
		delay = SYSCTL_RCGCADC_R;				//extra time to stabilize
		delay = SYSCTL_RCGCADC_R;
		delay = SYSCTL_RCGCADC_R;
		delay = SYSCTL_RCGCADC_R;
		ADC0_PC_R = 0x01;								//THIS IS FOR MAX SAMPLING RATE OF 125Khz, how do we make it 60hz??
		ADC0_SSPRI_R = 0x0123;
		ADC0_ACTSS_R &= ~0x0008;
		ADC0_SSMUX3_R = (ADC0_SSMUX3_R & 0xFFFFFFF0) + 5;				//set channel Ain5
		ADC0_SSCTL3_R = 0x0006;
		ADC0_IM_R &= ~0x0008;
		ADC0_ACTSS_R |= 0x0008;
		
		

}

//------------ADC_In------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
uint32_t ADC_In(void){  
	uint32_t result;
	ADC0_PSSI_R = 0x0008;				//initiate SS3 (software trigger)
	while ( (ADC0_RIS_R & 0x08) == 0) {};				//wait for conversion to be done
	result = ADC0_SSFIFO3_R & 0x0FFF;						//read 12 bit result
	ADC0_ISC_R = 0x008;									//completion of ADC conversion & getting the result
  return result; // remove this, replace with real code
   // --UUU-- Complete this(copy from Lab8)
	
}


