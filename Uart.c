// Uart.c
// Runs on LM4F120/TM4C123
// Use UART1 to implement bidirectional data transfer to and from 
// another microcontroller in Lab 9.  This time, interrupts and FIFOs
// are used.
// Daniel Valvano
// November 14, 2018
// Modified by EE345L students Charlie Gough && Matt Hawk
// Modified by EE345M students Agustinus Darmawan && Mingjie Qiu

/* Lab solution, Do not post
 http://users.ece.utexas.edu/~valvano/
*/

// This U0Rx PC4 (in) is connected to other LaunchPad PC5 (out)
// This U0Tx PC5 (out) is connected to other LaunchPad PC4 (in)
// This ground is connected to other LaunchPad ground

#include <stdint.h>
#include "Fifo.h"
#include "Uart.h"
#include "../inc/tm4c123gh6pm.h"

uint32_t DataLost; 
// Initialize UART1
// Baud rate is 115200 bits/sec
// Make sure to turn ON UART1 Receiver Interrupt (Interrupt 6 in NVIC)
// Write UART1_Handler

void Uart_Init(void){
   // --UUU-- complete with your code
	SYSCTL_RCGCUART_R |= 0x002;			//activate UART1
	SYSCTL_RCGCGPIO_R |= 0x004;			//activate port C
	//RxFifo_Init?
	UART1_CTL_R &= ~UART_CTL_UARTEN;	//disable UART
	UART1_IBRD_R = 27;
	UART1_FBRD_R = 8;
	UART1_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);
	UART1_IFLS_R &= ~0x3F;
	UART1_IFLS_R += (UART_IFLS_TX1_8 | UART_IFLS_RX1_8);
	UART1_IM_R |= (UART_IM_RXIM | UART_IM_TXIM | UART_IM_RTIM);
	UART1_CTL_R |= 0x0301;
	GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R & 0xFFFFFF00) + 0x00000011;
	GPIO_PORTC_AMSEL_R &= ~0x0030;		//disable analog function on PC4-5
	GPIO_PORTC_AFSEL_R |= 0x0030;
	GPIO_PORTA_DEN_R |= 0x0030;
	NVIC_PRI1_R = (NVIC_PRI1_R & 0xFFFF00FF) | 0x00004000;
	//NVIC_EN0_R = NVIC_EN0_INT5;			//WHY DOES THIS HAVE AN ERROR? WHERE IS NVIC_EN0_INT5?
	EnableInterrupts();

	
}

// input ASCII character from UART
// spin if RxFifo is empty
// Receiver is interrupt driven
char Uart_InChar(void){
	
	
  return 0; // --UUU-- remove this, replace with real code
}

//------------UART1_InMessage------------
// Accepts ASCII characters from the serial port
//    and adds them to a string until ETX is typed
//    or until max length of the string is reached.
// Input: pointer to empty buffer of 8 characters
// Output: Null terminated string
// THIS FUNCTION IS OPTIONAL
void UART1_InMessage(char *bufPt){
}

//------------UART1_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
// Transmitter is busywait
void Uart_OutChar(char data){
  // --UUU-- complete with your code
	//TXFF is UART1_FR_R bit 5
	uint32_t TXFF;
	TXFF = UART1_FR_R & 0x0020;
	while (TXFF != 0) {};							//wait for TXFF to be 0
	UART1_DR_R = data;
	
}

// hardware RX FIFO goes from 7 to 8 or more items
// UART receiver Interrupt is triggered; This is the ISR
void UART1_Handler(void){
  // --UUU-- complete with your code
}
