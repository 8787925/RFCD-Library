/*
 * CANnetwork.h
 *
 *  Created on: Oct 12, 2016
 *      Author: Jimmy
 */

#ifndef CANNETWORK_H_
#define CANNETWORK_H_

#include "config.h"

#ifndef NUMBER_OF_CAN_NETWORKS
#define NUMBER_OF_CAN_NETWORKS 1
#endif

enum networkID
{
	NETWORK1,
	NETWORK2
};


class CANnetwork
{
	public:
	//
	//addDevice(CANhardware*)
	//

	void addDevice(CANhardware* networkHardware, networkID networkNumber);


	//
	//joinNetwork(networkID)
	//

	void joinNetwork(networkID networkNumber);


	//
	//listenOnly(networkID)
	//

	void listenOnly(networkID networkNumber);


	//
	//retrieveNetworkHardware(networkID)
	//

	CANhardware* retrieveNetwork(networkID networkNumber);

private:
	//
	//variables
	//

	CANhardware*  networks_[NUMBER_OF_CAN_NETWORKS];
};



#endif /* CANNETWORK_H_ */
