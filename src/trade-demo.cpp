/*
 * trade-demo.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: luodichen
 */

#include <stdio.h>
#include <unistd.h>
#include "ThostFtdcMdApi.h"
#include "LMarketDataHandler.h"

int main()
{
    CThostFtdcMdApi *pApi = CThostFtdcMdApi::CreateFtdcMdApi();
    LMarketDataHandler handler(pApi);

    pApi->RegisterSpi(&handler);
    pApi->RegisterFront("tcp://ctp1-md1.citicsf.com:41213");
    pApi->Init();

    for (;;)
        usleep(1000000);

    return 0;
}
