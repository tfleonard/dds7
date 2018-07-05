/* 
 * File:   dds.c
 * Author: root
 *
 * Created on April 9, 2009, 7:09 PM
 */
 
 #include <ctype.h>
 #include <stdint.h>
 #include <stdio.h>

 #include <avr/io.h>
 #include <avr/interrupt.h>

#include <math.h>
#include "clock.h"
#include "dds.h"

void ddsSend(uint16_t *buf, uint8_t cnt);

//
// DDS uses bits PB0 - PB2, PB5
//

void DdsInit(void) {

volatile uint8_t reg;
	uint16_t buf[5];
	uint32_t freq = (uint32_t)((float)CNTS_PER_HZ * 1000000.0);

	reg = DDRB;
	reg |= (DDS_OUT_BITS | PGA_OUT_BITS);		// set Led pin to output
	DDRB = reg;

	reg = PORTB;
	reg &= ~(DDS_OUT_BITS | PGA_OUT_BITS);	
	reg |= (DDS_DEFAULT | PGA_DEFAULT);	
	PORTB = reg;

	buf[0] = (DDS_CMD_B28 | DDS_CMD_RST);
	buf[1] = DDS_REG_VFOA | (freq & DDS_FREQ_MSK);
	buf[2] = DDS_REG_VFOA | ( (freq >> DDS_FREQ_MSB_SHFT) & DDS_FREQ_MSK);
	buf[3] = DDS_REG_PHA;
	buf[4] = DDS_CMD_B28;
	ddsSend(buf, 5);
	
}

//
// phase change per dds clock is {dds resolution) / (dds clock).
// the phase increment is then the freq in hz * the phase change per clock 
//
// with a 40 mhz clock and 32 bits of resolution the phase change 
// per dds clock is 107.3741824 clocks per hz
// 
// for a dds output frequency of 7.000000 mhz, this is a phase
// increment of 0x2ccccccc.  For 7.000001 mhz this is a phase
// increment of 0x2ccccd38.
// 
//
// with a 125 mhz clock and 32 bits of resolution the phase change 
// per dds clock is 34.359738368 clocks per hz
// 
// with a 25 mhz clock and 28 bits of resolution the phase change
// per dds clock is 10.73741824 clock per hz
//
// for a dds output frequency of 7.000000 mhz, this is a phase
// increment of 0x0E560418.  For 7.000001 mhz this is a phase
// increment of 0x0E56043B.
// 



void dds(float fout) {

float n;
uint32_t phaseInc;
uint16_t buf[2];

	n = fout * (float)CNTS_PER_HZ;		// phase change per clock
	phaseInc = (uint32_t)n;
	buf[0] = DDS_REG_VFOA | (phaseInc & DDS_FREQ_MSK);
	buf[1] = DDS_REG_VFOA | ( (phaseInc >> DDS_FREQ_MSB_SHFT) & DDS_FREQ_MSK);
	ddsSend(buf, 2);
printf("fout: %7.5f, LSB: 0x%x, MSB: 0x%x\n", fout, buf[0], buf[1]);	
}



void ddsSend(uint16_t *buf, uint8_t cnt) {

	cli();
	PORTB &= 	~FQUD_CLK;

	while (cnt--) {
		uint16_t val = *buf++;
		for (int i=0; i< 16; i++) {
			if (val & 0x8000) {
				PORTB |= SD;
			} else {
				PORTB &= ~SD;
			}
			PORTB |= W_CLK;
			PORTB &= ~W_CLK;
			val <<= 1;
		}
	}
	
	PORTB |= FQUD_CLK;
	sei();
}
		
		
				
	
	
	
	
	
	

void setGain(uint16_t gain) {






}






