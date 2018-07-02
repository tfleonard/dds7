/*
 * relay.h
 *
 * Created: 6/17/2018 11:19:26 AM
 *  Author: tleonard
 */ 


#ifndef RELAY_H_
#define RELAY_H_

#include <stdlib.h>


class relay {
	
private:
	params *param;
	vfo *curVfo;
	band_t band;

public:
	relay(params *prm);	
	void setVfo(vfo *v);
	void selectTx(bool upd);
	void selectRx(bool upd);
	void setBand(band_t b);
	void *operator new(size_t size) { return malloc(size);}
	void operator delete(void *ptr) { if (ptr) free(ptr); }

};



#endif /* RELAY_H_ */