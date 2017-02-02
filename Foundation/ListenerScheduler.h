/*
 * ListenerScheduler.h
 *
 *  Created on: Jan 22, 2017
 *      Author: Jimmy
 */

#ifndef FOUNDATION_LISTENERSCHEDULER_H_
#define FOUNDATION_LISTENERSCHEDULER_H_

#include "C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Foundation\Listener.h"
#include "C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Foundation\PointerListKit.h"

template <const uint8_t  SIZE>

class ListenerScheduler: public PointerList<Listener, SIZE>
{

	//
	//constructor
	//

	ListenerScheduler()
	{

	}


	//
	//executeList()
	//

	bool executeList()
	{
		Listener* listener;
		itterator_ = 0;
		for (int i=0; i<SIZE; i++)
		{
			listener = this->itterate();
			if (listener != 0)
			{
				listener->listenerEvent();
			}
		}

	}


	//
	//variables
	//


};


#endif /* FOUNDATION_LISTENERSCHEDULER_H_ */
