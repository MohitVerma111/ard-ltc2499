/*************************************************************************
Title:    MRBus Arduino Library Header
Authors:  Nathan Holmes <maverick@drgw.net>, Colorado, USA
          Michael Petersen <railfan@drgw.net>, Colorado, USA
          Michael Prader, South Tyrol, Italy
File:     mrbus-avr.h
License:  GNU General Public License v3

LICENSE:
    Copyright (C) 2012 Nathan Holmes, Michael Petersen, and Michael Prader

    Original MRBus code developed by Nathan Holmes for PIC architecture.
    This file is based on AVR port by Michael Prader.  Updates and
    compatibility fixes by Michael Petersen.
    
    UART code derived from AVR UART library by Peter Fleury, and as
    modified by Tim Sharpe.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License along
    with this program. If not, see http://www.gnu.org/licenses/
    
*************************************************************************/
#ifndef ARD2499_H
#define ARD2499_H

#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include "Arduino.h"
#include "Wire.h"


#define FAKE_CONFIG1_TEMPERATURE   6
#define LTC2499_CONFIG1_ENABLE     5
#define LTC2499_CONFIG1_SINGLE_END 4
#define LTC2499_CONFIG1_ODD        3
#define LTC2499_CONFIG1_A2         2
#define LTC2499_CONFIG1_A1         1
#define LTC2499_CONFIG1_A0         0

#define LTC2499_CHAN_DIFF_0P_1N    (0)
#define LTC2499_CHAN_DIFF_2P_3N    (_BV(LTC2499_CONFIG1_A0))
#define LTC2499_CHAN_DIFF_4P_5N    (_BV(LTC2499_CONFIG1_A1))
#define LTC2499_CHAN_DIFF_6P_7N    (_BV(LTC2499_CONFIG1_A1) | _BV(LTC2499_CONFIG1_A0))
#define LTC2499_CHAN_DIFF_8P_9N    (_BV(LTC2499_CONFIG1_A2))
#define LTC2499_CHAN_DIFF_10P_11N  (_BV(LTC2499_CONFIG1_A2) | _BV(LTC2499_CONFIG1_A0))
#define LTC2499_CHAN_DIFF_12P_13N  (_BV(LTC2499_CONFIG1_A2) | _BV(LTC2499_CONFIG1_A1))
#define LTC2499_CHAN_DIFF_14P_15N  (_BV(LTC2499_CONFIG1_A2) | _BV(LTC2499_CONFIG1_A1) | _BV(LTC2499_CONFIG1_A0))

#define LTC2499_CHAN_DIFF_1P_0N    (_BV(LTC2499_CONFIG1_ODD))
#define LTC2499_CHAN_DIFF_3P_2N    (_BV(LTC2499_CONFIG1_ODD) | _BV(LTC2499_CONFIG1_A0))
#define LTC2499_CHAN_DIFF_5P_4N    (_BV(LTC2499_CONFIG1_ODD) | _BV(LTC2499_CONFIG1_A1))
#define LTC2499_CHAN_DIFF_7P_6N    (_BV(LTC2499_CONFIG1_ODD) | _BV(LTC2499_CONFIG1_A1) | _BV(LTC2499_CONFIG1_A0))
#define LTC2499_CHAN_DIFF_9P_8N    (_BV(LTC2499_CONFIG1_ODD) | _BV(LTC2499_CONFIG1_A2))
#define LTC2499_CHAN_DIFF_11P_10N  (_BV(LTC2499_CONFIG1_ODD) | _BV(LTC2499_CONFIG1_A2) | _BV(LTC2499_CONFIG1_A0))
#define LTC2499_CHAN_DIFF_13P_12N  (_BV(LTC2499_CONFIG1_ODD) | _BV(LTC2499_CONFIG1_A2) | _BV(LTC2499_CONFIG1_A1))
#define LTC2499_CHAN_DIFF_15P_14N  (_BV(LTC2499_CONFIG1_ODD) | _BV(LTC2499_CONFIG1_A2) | _BV(LTC2499_CONFIG1_A1) | _BV(LTC2499_CONFIG1_A0))

#define LTC2499_CHAN_SINGLE_0P     (_BV(LTC2499_CONFIG1_SINGLE_END))
#define LTC2499_CHAN_SINGLE_1P     (_BV(LTC2499_CONFIG1_SINGLE_END) | _BV(LTC2499_CONFIG1_ODD))
#define LTC2499_CHAN_SINGLE_2P     (_BV(LTC2499_CONFIG1_SINGLE_END) | _BV(LTC2499_CONFIG1_A0))
#define LTC2499_CHAN_SINGLE_3P     (_BV(LTC2499_CONFIG1_SINGLE_END) | _BV(LTC2499_CONFIG1_ODD) | _BV(LTC2499_CONFIG1_A0))
#define LTC2499_CHAN_SINGLE_4P     (_BV(LTC2499_CONFIG1_SINGLE_END) | _BV(LTC2499_CONFIG1_A1))
#define LTC2499_CHAN_SINGLE_5P     (_BV(LTC2499_CONFIG1_SINGLE_END) | _BV(LTC2499_CONFIG1_ODD) | _BV(LTC2499_CONFIG1_A1))
#define LTC2499_CHAN_SINGLE_6P     (_BV(LTC2499_CONFIG1_SINGLE_END) | _BV(LTC2499_CONFIG1_A1) | _BV(LTC2499_CONFIG1_A0))
#define LTC2499_CHAN_SINGLE_7P     (_BV(LTC2499_CONFIG1_SINGLE_END) | _BV(LTC2499_CONFIG1_ODD) | _BV(LTC2499_CONFIG1_A1) | _BV(LTC2499_CONFIG1_A0))
#define LTC2499_CHAN_SINGLE_8P     (_BV(LTC2499_CONFIG1_SINGLE_END) | _BV(LTC2499_CONFIG1_A2))
#define LTC2499_CHAN_SINGLE_9P     (_BV(LTC2499_CONFIG1_SINGLE_END) | _BV(LTC2499_CONFIG1_ODD) | _BV(LTC2499_CONFIG1_A2))
#define LTC2499_CHAN_SINGLE_10P    (_BV(LTC2499_CONFIG1_SINGLE_END) | _BV(LTC2499_CONFIG1_A2) | _BV(LTC2499_CONFIG1_A0))
#define LTC2499_CHAN_SINGLE_11P    (_BV(LTC2499_CONFIG1_SINGLE_END) | _BV(LTC2499_CONFIG1_ODD) | _BV(LTC2499_CONFIG1_A2) | _BV(LTC2499_CONFIG1_A0))
#define LTC2499_CHAN_SINGLE_12P    (_BV(LTC2499_CONFIG1_SINGLE_END) | _BV(LTC2499_CONFIG1_A2) | _BV(LTC2499_CONFIG1_A1))
#define LTC2499_CHAN_SINGLE_13P    (_BV(LTC2499_CONFIG1_SINGLE_END) | _BV(LTC2499_CONFIG1_ODD) | _BV(LTC2499_CONFIG1_A2) | _BV(LTC2499_CONFIG1_A1))
#define LTC2499_CHAN_SINGLE_14P    (_BV(LTC2499_CONFIG1_SINGLE_END) | _BV(LTC2499_CONFIG1_A2) | _BV(LTC2499_CONFIG1_A1) | _BV(LTC2499_CONFIG1_A0))
#define LTC2499_CHAN_SINGLE_15P    (_BV(LTC2499_CONFIG1_SINGLE_END) | _BV(LTC2499_CONFIG1_ODD) | _BV(LTC2499_CONFIG1_A2) | _BV(LTC2499_CONFIG1_A1) | _BV(LTC2499_CONFIG1_A0))

// The temperature channel is actually fake - we manipulate things internally
#define LTC2499_CHAN_TEMPERATURE   (_BV(FAKE_CONFIG1_TEMPERATURE))

#define LTC2499_CONFIG2_ENABLE2     7
#define LTC2499_CONFIG2_IM          6
#define LTC2499_CONFIG2_FA          5
#define LTC2499_CONFIG2_FB          4
#define LTC2499_CONFIG2_SPD         3

#define LTC2499_CONFIG2_50HZ_REJ    (_BV(LTC2499_CONFIG2_FB))
#define LTC2499_CONFIG2_60HZ_REJ    (_BV(LTC2499_CONFIG2_FA))
#define LTC2499_CONFIG2_60_50HZ_REJ (0)  
#define LTC2499_CONFIG2_SPEED_2X    (_BV(LTC2499_CONFIG2_SPD))

#define ARD2499_INIT_SUCCESS      0
#define ARD2499_INIT_LTC2499_ERR  1
#define ARD2499_INIT_EEPROM_ERR   2

#define ARD2499_EEPROM_ADDR_EUI48  0xFA

#define ARD2499_EEP_ADDR_ZZ 0x53
#define ARD2499_EEP_ADDR_0Z 0x54
#define ARD2499_EEP_ADDR_Z0 0x55
#define ARD2499_EEP_ADDR_00 0x56

#define ARD2499_ADC_ADDR_000   0x14
#define ARD2499_ADC_ADDR_00Z   0x15
#define ARD2499_ADC_ADDR_001   0x16
#define ARD2499_ADC_ADDR_0Z0   0x17
#define ARD2499_ADC_ADDR_0ZZ   0x24
#define ARD2499_ADC_ADDR_0Z1   0x25
#define ARD2499_ADC_ADDR_010   0x26
#define ARD2499_ADC_ADDR_01Z   0x27
#define ARD2499_ADC_ADDR_011   0x28
#define ARD2499_ADC_ADDR_Z00   0x35
#define ARD2499_ADC_ADDR_Z01   0x37
#define ARD2499_ADC_ADDR_Z0Z   0x36
#define ARD2499_ADC_ADDR_ZZ0   0x44
#define ARD2499_ADC_ADDR_ZZZ   0x45
#define ARD2499_ADC_ADDR_ZZ1   0x46
#define ARD2499_ADC_ADDR_Z10   0x47
#define ARD2499_ADC_ADDR_Z1Z   0x54
#define ARD2499_ADC_ADDR_Z11   0x55
#define ARD2499_ADC_ADDR_100   0x56
#define ARD2499_ADC_ADDR_10Z   0x57
#define ARD2499_ADC_ADDR_101   0x64
#define ARD2499_ADC_ADDR_1Z0   0x65
#define ARD2499_ADC_ADDR_1ZZ   0x66
#define ARD2499_ADC_ADDR_1Z1   0x67
#define ARD2499_ADC_ADDR_110   0x74
#define ARD2499_ADC_ADDR_111   0x76
#define ARD2499_ADC_ADDR_11Z   0x75

class Ard2499
{
	public:
		Ard2499();
		byte begin(byte ltc2499Address, byte eepromAddress);
		const char* eui48Get();
		byte eepromRead(byte address);
		byte eepromWrite(byte address, byte value, byte blocking);
		unsigned long ltc2499Read();
		byte ltc2499ChangeChannel(byte channel);
		byte ltc2499ChangeConfiguration(byte config);
		unsigned int ltc2499ReadTemperatureK();
	private:
		uint8_t init_status;
		uint8_t i2cAddr_ltc2499;
		uint8_t i2cAddr_eeprom;
		uint8_t current2499Config;
		uint8_t current2499Channel;
		char eui48[6*2+1];

};

#define LTC2499_READERROR 0xFFFFFFFF

#endif // ARD2499_H

