/*
 * listbox.h
 *
 *  Created on: May 2, 2018
 *      Author: tleonard
 */

#ifndef LISTBOX_H_
#define LISTBOX_H_


typedef struct _list_info_t {
	pixpsn_t label_psn;
	const char *label;
	pixpsn_t val_psn;
	const char **listStrings;
	uint8_t numListEntries;
} list_info_t;



template <class T> class listbox {

private:
	T &list;
	uint8_t	numMembers;
	list_info_t listInfo;
	uint8_t curIndx;
	void updateDisplay(void);
	Lcd *lcd;
	pixColor fg_color;

public:
	listbox(Lcd *l, list_info_t li, T &listEntries);
	T getSelected();
	void setSelected(T entry);
	T operator++ (void);
	T operator--(void);

	void *operator new(size_t size) { return malloc(size);}
	void operator delete(void *ptr) { if (ptr) free(ptr); }

};


#endif /* LISTBOX_H_ */
