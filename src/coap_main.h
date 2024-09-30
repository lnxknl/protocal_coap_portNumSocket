/*******************************************************************************
 * Copyright (c)  2015  Dipl.-Ing. Tobias Rohde, http://www.lobaro.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *******************************************************************************/
#ifndef COAP_MAIN_H_
#define COAP_MAIN_H_

#include "liblobaro_coap.h"
#include "coap_interaction.h"

#define HOLDTIME_AFTER_NON_TRANSACTION_END (0)
#define POSTPONE_WAIT_TIME_SEK (3)
#define POSTPONE_MAX_WAIT_TIME (30)
#define CLIENT_MAX_RESP_WAIT_TIME (45)

#define USE_RFC7641_ADVANCED_TRANSMISSION (1) //Update representation of resource during retry of observe sendout

#ifdef COAP_ACK_TIMEOUT
#define ACK_TIMEOUT (COAP_ACK_TIMEOUT)
#else
#define ACK_TIMEOUT (8)
#endif
#define ACK_RANDOM_FACTOR (1.5)
#ifdef COAP_MAX_RETRANSMIT
#define MAX_RETRANSMIT (COAP_MAX_RETRANSMIT)
#else
#define MAX_RETRANSMIT (3)
#endif
#define NSTART (1) //todo implement
#define DEFAULT_LEISURE (5) //todo implement
#define PROBING_RATE (1)        //[client]


typedef struct {
	CoAP_Interaction_t *pInteractions;
	CoAP_API_t api;
} CoAP_t;

extern CoAP_t CoAP; //Stack global variables

#endif
