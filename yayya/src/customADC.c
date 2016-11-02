
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <float.h>
#include "platform.h"
#include "customADC.h"



void adcInit(){
MSTP(S12AD) = 0;
 PORT4.PODR.BIT.B2 = 0;    
    PORT4.PDR.BIT.B2  = 0;    
    PORT4.PMR.BIT.B2  = 0;    /* First set I/O pin mode register to GPIO mode. */    
	PORT4.PODR.BIT.B6 = 0;    /* Clear I/O pin data register to low output. */
    PORT4.PDR.BIT.B6  = 0;    /* Set I/O pin direction to input. */
    PORT4.PMR.BIT.B6  = 0;
	PORTD.PODR.BIT.B3 = 0;    /* Clear I/O pin data register to low output. */
    PORTD.PDR.BIT.B3  = 0;    /* Set I/O pin direction to input. */
	PORTD.PMR.BIT.B3  = 0;
	
	PORTD.PODR.BIT.B0=0;
	PORTD.PDR.BIT.B0 =0;
    PORTD.PMR.BIT.B0  = 0;
	
	PORTD.PODR.BIT.B1=0;
	PORTD.PDR.BIT.B1 =0;
    PORTD.PMR.BIT.B1  = 0;
	
	PORTD.PODR.BIT.B4=0;
	PORTD.PDR.BIT.B4 =0;
    PORTD.PMR.BIT.B4  = 0;
	
    MPC.P42PFS.BYTE = 0x80;   /* Set port function register to analog input, no interrupt. */  
	
SYSTEM.MSTPCRA.BIT.MSTPA17=0; 
 S12AD.ADCSR.BYTE=0x0C; 
  
   S12AD.ADCER.BIT.ACE=1; 
   
    S12AD.ADCER.BIT.ADRFMT=0;
}
	
	
	
int adcRead(int channel){
	int adc_result;
	S12AD.ADANS0.WORD= channel;
S12AD.ADCSR.BIT.ADST = 1;
char ADC_OUT[20];
 
 while(S12AD.ADCSR.BIT.ADST ==1 );
 
    if(channel == AN2){
    adc_result = (S12AD.ADDR2 & 0X0FFF);  
	}      
 if(channel == AN8){
    adc_result = (S12AD.ADDR8 & 0X0FFF);
	sprintf(ADC_OUT, "%d", adc_result);
          //lcd_display(LCD_LINE6, ADC_OUT);  
		  
	}         
 if(channel == AN9){
    adc_result = (S12AD.ADDR9 & 0X0FFF);  
	} 
	if (channel== AN12)
	{
		adc_result = (S12AD.ADDR12 & 0X0FFF);  
	} 
	
	
   return adc_result;
 
}
    
float convertADC(float v_ref, int adc_result1, int n_bits ){
	
	float v_in;
	int a = 1 << n_bits;
	int b= a-1;
	v_in = (adc_result1 * v_ref) / b;
	return v_in;
	} 