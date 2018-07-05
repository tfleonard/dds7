/*
 * listbox.cpp
 *
 *  Created on: May 2, 2018
 *      Author: tleonard
 */

 #include <ctype.h>
 #include <stdint.h>
 #include <stdio.h>

 #include <avr/io.h>
 #include <avr/interrupt.h>

 #include "clock.h"
 #include "uart.h"
 #include "led.h"
 #include "lcd.h"
 #include "graphics.h"
 #include "dds.h"
 #include "sw.h"
 #include "ElapsedTime.h"
 #include "Encoder.h"
 #include "vfo.h"
 #include "params.h"


#include "listbox.h"


template <class T> listbox<T>::listbox(Lcd *l, list_info_t li, T &listEntries) {
	lcd = l;
	listInfo = li;
	list = listEntries;
	numMembers = li.numListEntries;
	this->numMembers = numMembers;
	curIndx = 0;
	pixColor  fg_color = {0xfc,0xfc,0xfc};
}


template <class T> T listbox<T>::operator++ (void) {
	curIndx++;
	if (curIndx == numMembers) {
		curIndx = 0;
	}
	updateDisplay();
}


template <class T> T listbox<T>::operator-- (void) {
	if (curIndx == 0) {
		curIndx = numMembers-1;
	} else {
		curIndx--;
	}
	updateDisplay();
}



template <class T>	T listbox<T>::getSelected() {
	return list[curIndx];
}



template <class T> void listbox<T>::setSelected(T entry) {
	for (uint8_t i=0; i < numMembers; i++) {
		if (list[i] == entry) {
			curIndx = i;
		}
	}
	updateDisplay();
}



template  <class T> void listbox<T>::updateDisplay(void) {
uint16_t line;
uint16_t col;
	line = listInfo.val_psn.line;
	col =  listInfo.val_psn.col;
	lcd->gotoxy(line,col);
	lcd->puts(listInfo.listStrings[curIndx], fg_color);
}




