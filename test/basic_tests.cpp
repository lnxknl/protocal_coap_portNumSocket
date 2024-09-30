/*******************************************************************************
 * Copyright (c) 2016  MSc. David Graeff <david.graeff@web.de>
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
 */

#include <gtest/gtest.h>
#include <coap.h>
#include <stdint.h>

typedef int16_t bufsize;
extern "C" void	bstats(bufsize *curalloc, bufsize *totfree, bufsize *maxfree, long *nget, long *nrel);

// Test fixture class. For these very basic tests, we only allocate some memory in the fixture.
class BasicTest : public testing::Test {
 protected:
  virtual void SetUp() {
	  // CoAP_Init can only be called once with the same memory address,
	  // because internally bpool is called, which does not check if the same
	  // address range is already in the managed memory pool.
	  // Leads to an endless loop otherwise.
	  static bool initialized = false;
	  if (!initialized) {

		  CoAP_API_t coapApi;
		  coapApi.debugPuts = NULL;
		  coapApi.rtc1HzCnt = NULL;

		  CoAP_Config_t coapCfg;
		  coapCfg.Memory = CoAP_WorkMemory;
		  coapCfg.MemorySize = sizeof(CoAP_WorkMemory);

		  CoAP_Init(coapApi, coapCfg);
		  initialized = true;
	  }
  }

  uint8_t CoAP_WorkMemory[4096] = { 0 };
};

TEST_F(BasicTest, MemoryTest) {
	bufsize curalloc, curalloc2, totfree, maxfree;
	long nget,nrel;

	bstats(&curalloc, &totfree, &maxfree, &nget, &nrel);
	
	void* buf = coap_mem_get(16);
	ASSERT_NE(buf, nullptr) << "Failed to allocate memory";
	
	int i = coap_mem_size((uint8_t*)buf);
	ASSERT_EQ(i, 16) << "Buffer should be 16 bytes";
	
	coap_mem_release(buf);
	bstats(&curalloc2, &totfree, &maxfree, &nget, &nrel);
	ASSERT_EQ(curalloc, curalloc2) << "Available memory should be the same after get/release";
}

TEST_F(BasicTest, AllocSocketTest) {
	SocketHandle_t socketHandle = (SocketHandle_t) 0;
	uint16_t LocalPort = 1234;

	CoAP_Socket_t* pSocket;
	pSocket=RetrieveSocket(socketHandle);
	ASSERT_EQ(pSocket, nullptr) << "Interface id should not be in use";
	
	pSocket = AllocSocket();
	ASSERT_NE(pSocket, nullptr) << "Failed to allocate a socket";
	

	// No real implementation, just for type check during test yet
	pSocket->Handle = nullptr;
	pSocket->Tx  = nullptr;
	pSocket->Alive = true;
}