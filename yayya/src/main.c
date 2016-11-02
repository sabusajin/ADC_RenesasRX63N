/*******************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only 
 * intended for use with Renesas products. No other uses are authorized. This 
 * software is owned by Renesas Electronics Corporation and is protected under
 * all applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
 * LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
 * AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
 * TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
 * ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
 * FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
 * ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
 * BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software
 * and to discontinue the availability of this software. By using this software,
 * you agree to the additional terms and conditions found by accessing the 
 * following link:
 * http://www.renesas.com/disclaimer *
 * Copyright (C) 2012 Renesas Electronics Corporation. All rights reserved.    
 *******************************************************************************/
/******************************************************************************
 * File Name     : main.c
 * Version       : 1.0
 * Device(s)     : RX63N
 * Tool-Chain    : Renesas RX Standard Toolchain 1.0.0
 * OS            : None
 * H/W Platform  : YRDKRX63N
 * Description   : Empty application project
 *                 This application provides a handy framework to serve as a
 *                 generic basis for any application. The MCU startup procedures
 *                 are provided, as well as some basic means for I/O. The LCD is 
 *                 initialized, board switches and their interrupt ISR stubs are
 *                 defined, and a simple loop blinks an LED to indicate that the
 *                 board is operating.
 *******************************************************************************/
/*******************************************************************************
 * History : DD.MM.YYYY     Version     Description
 *         : 22.09.2011     1.00        First release              
 *******************************************************************************/

/*******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include < stdint.h > 
#include < stdbool.h > 
#include < stdio.h > 
#include < float.h > 
#include < machine.h > 
#include "platform.h"
#include "r_switches.h"
#include < customADC.h > 
#define g_sw1_press PORT4.PIDR.BIT.B0
# define g_sw2_press PORT4.PIDR.BIT.B1
# define g_sw3_press PORT4.PIDR.BIT.B4
  /*******************************************************************************
   * Prototypes for local functions
   *******************************************************************************/

/******************************************************************************
 * Function name: main
 * Description  : Main program function
 * Arguments    : none
 * Return value : none
 ******************************************************************************/
void main(void) {
  /* Used to pace toggling of the LED */
  char ADC_OUT[10], VIN[10],ADC_OUT1[10],ADC_OUT2[10];
  float v_input, v_input1, v_input2;
  int adc_result1, adc_result2, sub_result;
  uint32_t led_counter;

  adcInit();

  /* Initialize LCD */
  lcd_initialize();

  /* Clear LCD */
  lcd_clear();

  /* Display message on LCD */
  lcd_display(LCD_LINE1, " Sajin Joel");
  lcd_display(LCD_LINE2, " ADC Test ");
  //lcd_display(LCD_LINE3, "channel 2:");
  /* 
      STDOUT is routed through the virtual console window tunneled through the JTAG debugger.
      Open the console window in HEW to see the output 
  */
  //printf("This is the debug console\r\n");

  /* The three pushbuttons on the YRDK board are tied to interrupt lines, set them up here */
  // R_SWITCHES_Init();

  /* This is the main loop.  It does nothing but toggle LED4 periodically */
  while (1) {

    if (S12AD.ADCSR.BIT.ADST == 0) {
      //adc_result1=adcRead(0x0004);
      //sprintf(ADC_OUT,"%d",adc_result1);
      if (g_sw1_press == 0) {
        while (1 && g_sw2_press == 1 && g_sw3_press == 1) {
          adc_result1 = adcRead(AN2);
          sprintf(ADC_OUT, "%d", adc_result1);
          lcd_display(LCD_LINE3, "Channel 2:");
          //lcd_display(LCD_LINE4, ADC_OUT);
          v_input = convertADC(3.3, adc_result1, 12);
          sprintf(VIN, "%f", v_input);
          lcd_display(LCD_LINE4, VIN);
        }

      }
      if (g_sw2_press == 0) {
        while (1 && g_sw1_press == 1 && g_sw3_press == 1) {
          adc_result1 = adcRead(AN8);
          sprintf(ADC_OUT, "%d", adc_result1);
          lcd_display(LCD_LINE3, "Channel 8:");
         // lcd_display(LCD_LINE4, ADC_OUT);
		  v_input = convertADC(3.3, adc_result1, 12);
          sprintf(VIN, "%f", v_input);
          lcd_display(LCD_LINE4, VIN);
        }
      }
    }
    if (g_sw3_press == 0) {
      while (1 && g_sw1_press == 1 && g_sw2_press == 1) {
		  
		  
        adc_result1 = adcRead(AN9);

        adc_result2 = adcRead(AN12);
		lcd_display(LCD_LINE3, "9 & 12");
		v_input1 = convertADC(3.3, adc_result1, 12);
		v_input2 = convertADC(3.3, adc_result2, 12);
		sprintf(ADC_OUT1, "%f", v_input1);
		sprintf(ADC_OUT2, "%f", v_input2);
		
		
		
		lcd_display(LCD_LINE4, ADC_OUT1);
		//lcd_display(LCD_LINE5, ADC_OUT2);
        //lcd_display(LCD_LINE3, "Channel 6:");
        sub_result = adc_result1 - adc_result2;
        if (sub_result > 0) {
          lcd_display(LCD_LINE7, "HIGH");
        } else if (sub_result < 0) {
          lcd_display(LCD_LINE7, "LOW");
        } else if (sub_result = 0) {
          lcd_display(LCD_LINE7, "EQUAL");
        }

      }
    }

  }
} /* End of function main() */

/******************************************************************************
 * Function name: sw1_callback
 * Description  : Callback function that is executed when SW1 is pressed.
 *                Called by sw1_isr in r_switches.c
 * Arguments    : none
 * Return value : none
 ******************************************************************************/
void sw1_callback(void) {
  nop(); /* Add your code here. Note: this is executing inside an ISR. */
} /* End of function sw1_callback() */

/******************************************************************************
 * Function name: sw2_callback
 * Description  : Callback function that is executed when SW2 is pressed.
 *                Called by sw2_isr in r_switches.c
 * Arguments    : none
 * Return value : none
 ******************************************************************************/
void sw2_callback(void) {
  nop(); /* Add your code here. Note: this is executing inside an ISR. */
} /* End of function sw2_callback() */

/******************************************************************************
 * Function name: sw3_callback
 * Description  : Callback function that is executed when SW3 is pressed.
 *                Called by sw3_isr in r_switches.c
 * Arguments    : none
 * Return value : none
 ******************************************************************************/
void sw3_callback(void) {
  nop(); /* Add your code here. Note: this is executing inside an ISR. */
} /* End of function sw3_callback() */