/*
 * CANHardwareClockSettings.h
 *
 *  Created on: Oct 16, 2016
 *      Author: Jimmy
 */

#if (F_CPU==8000000ULL)	//speed-specific baud rate schedule
	switch (baud)
	{
		case 100:
			CANBT1 = 0x12;              // Timing - Baud Rate Prescaler. See the data sheet errata if CANBT1=0.
			CANBT2 = 0x04;              // Timing - Re-Synchronization Jump Width and Propagation.
			CANBT3 = 0x13;              // Timing - Phase Segment 2, Phase Segment 1 and Sample Point.
			baudRate_ = baud;
			break;

		case 125:
			CANBT1 = 0x0E;              // Timing - Baud Rate Prescaler. See the data sheet errata if CANBT1=0.
			CANBT2 = 0x04;              // Timing - Re-Synchronization Jump Width and Propagation.
			CANBT3 = 0x13;              // Timing - Phase Segment 2, Phase Segment 1 and Sample Point.
			baudRate_ = baud;
			break;

		case 200:
			CANBT1 = 0x08;              // Timing - Baud Rate Prescaler. See the data sheet errata if CANBT1=0.
			CANBT2 = 0x04;              // Timing - Re-Synchronization Jump Width and Propagation.
			CANBT3 = 0x13;              // Timing - Phase Segment 2, Phase Segment 1 and Sample Point.
			baudRate_ = baud;
			break;

		case 250:
			CANBT1 = 0x06;              // Timing - Baud Rate Prescaler. See the data sheet errata if CANBT1=0.
			CANBT2 = 0x04;              // Timing - Re-Synchronization Jump Width and Propagation.
			CANBT3 = 0x13;              // Timing - Phase Segment 2, Phase Segment 1 and Sample Point.
			baudRate_ = baud;
			break;

		case 500:
			CANBT1 = 0x02;              // Timing - Baud Rate Prescaler. See the data sheet errata if CANBT1=0.
			CANBT2 = 0x04;              // Timing - Re-Synchronization Jump Width and Propagation.
			CANBT3 = 0x13;              // Timing - Phase Segment 2, Phase Segment 1 and Sample Point.
			baudRate_ = baud;
			break;

		case 1000:
			CANBT1 = 0x00;              // Timing - Baud Rate Prescaler. See the data sheet errata if CANBT1=0.
			CANBT2 = 0x04;              // Timing - Re-Synchronization Jump Width and Propagation.
			CANBT3 = 0x12;              // Timing - Phase Segment 2, Phase Segment 1 and Sample Point.
			baudRate_ = baud;
			break;

		default: //default case is to assume the last case was working or the minimum speed (if no already initialized)
			if (!initialized_)
			{
				CANBT1 = 0x12;              // Timing - Baud Rate Prescaler. See the data sheet errata if CANBT1=0.
				CANBT2 = 0x04;              // Timing - Re-Synchronization Jump Width and Propagation.
				CANBT3 = 0x13;              // Timing - Phase Segment 2, Phase Segment 1 and Sample Point.
				baudRate_ = DEFAULT_CAN_BAUD;
			}
			break;
	}
#endif


	#if (F_CPU==4000000ULL)	//speed-specific baud rate schedule
	switch (baud)
	{
		case 100:
			CANBT1 = 0x08;              // Timing - Baud Rate Prescaler. See the data sheet errata if CANBT1=0.
			CANBT2 = 0x04;              // Timing - Re-Synchronization Jump Width and Propagation.
			CANBT3 = 0x13;              // Timing - Phase Segment 2, Phase Segment 1 and Sample Point.
			baudRate_ = baud;
			break;

		case 125:
			CANBT1 = 0x06;              // Timing - Baud Rate Prescaler. See the data sheet errata if CANBT1=0.
			CANBT2 = 0x04;              // Timing - Re-Synchronization Jump Width and Propagation.
			CANBT3 = 0x13;              // Timing - Phase Segment 2, Phase Segment 1 and Sample Point.
			baudRate_ = baud;
			break;

		case 200:
			CANBT1 = 0x00;              // Timing - Baud Rate Prescaler. See the data sheet errata if CANBT1=0.
			CANBT2 = 0x0E;              // Timing - Re-Synchronization Jump Width and Propagation.
			CANBT3 = 0x4A;              // Timing - Phase Segment 2, Phase Segment 1 and Sample Point.
			baudRate_ = baud;
			break;

		case 250:
			CANBT1 = 0x02;              // Timing - Baud Rate Prescaler. See the data sheet errata if CANBT1=0.
			CANBT2 = 0x04;              // Timing - Re-Synchronization Jump Width and Propagation.
			CANBT3 = 0x13;              // Timing - Phase Segment 2, Phase Segment 1 and Sample Point.
			baudRate_ = baud;
			break;

		case 500:
			CANBT1 = 0x00;              // Timing - Baud Rate Prescaler. See the data sheet errata if CANBT1=0.
			CANBT2 = 0x04;              // Timing - Re-Synchronization Jump Width and Propagation.
			CANBT3 = 0x12;              // Timing - Phase Segment 2, Phase Segment 1 and Sample Point.
			baudRate_ = baud;
			break;

		default: //default case is to assume the last case was working or the minimum speed (if no already initialized)
			if (!initialized_)
			{
				CANBT1 = 0x08;              // Timing - Baud Rate Prescaler. See the data sheet errata if CANBT1=0.
				CANBT2 = 0x04;              // Timing - Re-Synchronization Jump Width and Propagation.
				CANBT3 = 0x13;              // Timing - Phase Segment 2, Phase Segment 1 and Sample Point.
				baudRate_ = DEFAULT_CAN_BAUD;
			}
			break;
	}
	#endif

