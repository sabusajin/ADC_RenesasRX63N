#include "platform.h"
#include <stdio.h>
#include <float.h>
#define MAX_COUNTS 4095.0
#define VREFH 3.3
#define VREFL 0.0
#define AN0 0x0001
#define AN1 0x0002
#define AN2 0x0004
#define AN3 0x0008
#define AN4 0x0010
#define AN5 0x0020
#define AN6 0x0040
#define AN7 0x0080
#define AN8 0x0100
#define AN9 0x0200
#define AN10 0x0400
#define AN11 0x0800
#define AN12 0x1000
#define AN13 0x2000
#define AN14 0x4000
#define AN15 0x8000

void adcInit(void); // This function initializes the ADC for us
int adcRead(int channel); // This function will read an analog value from the specified channel
float convertADC(float v_ref, int adc_result, int n_bits );
