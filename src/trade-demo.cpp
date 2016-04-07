/*
 * trade-demo.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: luodichen
 */

#include <sys/types.h>
#include <signal.h>

#include <stdio.h>
#include <unistd.h>
#include "ThostFtdcMdApi.h"
#include "LMarketDataHandler.h"
#include "LConfig.h"

int main()
{
    LConfig config;
    CThostFtdcMdApi *pApi = CThostFtdcMdApi::CreateFtdcMdApi();

    LMarketDataHandler::FLAGS flags;
    flags.enMode = LMarketDataHandler::FLAGS::M_NORMAL;
    flags.strInstrument = "a1605";

    config.Load("/etc/trade-demo.conf");

    LMarketDataHandler handler(pApi, config.m_szBrokerID, config.m_szUserID, config.m_szPassword, flags);
    pApi->RegisterSpi(&handler);
    pApi->RegisterFront(config.m_szServer);
    pApi->Init();

    handler.WaitForHandler();
    pApi->Release();

    // a dirty solution for the `double free or corruption` problem in libthostmduserapi.so
    kill(getpid(), 2);

    return 0;
}
