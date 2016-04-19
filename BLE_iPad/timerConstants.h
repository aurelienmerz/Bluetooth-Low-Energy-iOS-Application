/**
 * Copyright (C) Hes-so VALAIS/WALLIS, HEI, Infotronics. 2014
 * Created by Aurélien Merz (merz.aurel@me.com)
 *
 * @file	timerConstants.h
 * @brief	nRF51822 Timer1 definitions of COMPARE VALUES for some sampling frequencies.
 *          TIMER MODE using prescalar of 7 making a tick every 8us.
 *			All values corresponds to the number of tick, you have to count to obtain the 
 *			desired sampling frequency.
 *
 *
 * @author	Aurélien MERZ
 * @version	1.0
 * @date	June 2014
 */

 #define SAMPLING_FREQ 4000

 #define COMPARE_VALUE_1kHz   0x7D
 #define COMPARE_VALUE_1k5Hz  0x53
 #define COMPARE_VALUE_2kHz   0x3E
 #define COMPARE_VALUE_2k5Hz  0x32
 #define COMPARE_VALUE_3kHz   0x29
 #define COMPARE_VALUE_3k5Hz  0x24
 #define COMPARE_VALUE_4kHz   0x1F
 #define COMPARE_VALUE_4k5Hz  0x1C
 #define COMPARE_VALUE_5kHz   0x29
 #define COMPARE_VALUE_5k5Hz  0x16
 #define COMPARE_VALUE_6kHz   0x15
 #define COMPARE_VALUE_6k5Hz  0x13 
 #define COMPARE_VALUE_7kHz   0x11
 #define COMPARE_VALUE_8kHz   0xD
 #define COMPARE_VALUE_9kHz   0xC
 #define COMPARE_VALUE_10kHz  0xD
 #define COMPARE_VALUE_11kHz  0xB
 #define COMPARE_VALUE_12kHz  0xA
