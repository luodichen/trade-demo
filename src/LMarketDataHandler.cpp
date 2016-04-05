/*
 * LMarketDataHandler.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: luodichen
 */

#include <stdio.h>
#include <string.h>
#include "ThostFtdcTraderApi.h"
#include "ThostFtdcMdApi.h"
#include "ThostFtdcUserApiDataType.h"
#include "ThostFtdcUserApiStruct.h"
#include "LMarketDataHandler.h"

#define STRCPY_S(d, s) strncpy((d), (s), sizeof(d))

LMarketDataHandler::LMarketDataHandler(CThostFtdcMdApi *pApi)
    : m_pApi(pApi)
{

}

LMarketDataHandler::~LMarketDataHandler()
{

}

void LMarketDataHandler::OnFrontConnected()
{
    CThostFtdcReqUserLoginField objLoginReq;
    STRCPY_S(objLoginReq.BrokerID, "");
    STRCPY_S(objLoginReq.UserID, "");
    STRCPY_S(objLoginReq.Password, "");

    m_pApi->ReqUserLogin(&objLoginReq, 0);
}

void LMarketDataHandler::OnFrontDisconnected(int nReason)
{
    printf("disconnected\n");
}

void LMarketDataHandler::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
                                        CThostFtdcRspInfoField *pRspInfo,
                                        int nRequestID, bool bIsLast)
{
    printf("user logged in, err=%d, msg=%s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);

    char *szInstrument[] = {"a1605", "a1607"};
    int nRet = m_pApi->SubscribeMarketData(szInstrument, 2);
    printf("subscribe: %d\n", nRet);
}

void LMarketDataHandler::OnRspError(CThostFtdcRspInfoField *pRspInfo,
                                    int nRequestID, bool bIsLast)
{
    printf("error: %d, %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
}

void LMarketDataHandler::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
    printf("market data received\n");
}

void LMarketDataHandler::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument,
                                            CThostFtdcRspInfoField *pRspInfo,
                                            int nRequestID, bool bIsLast)
{
    printf("market subscribe response: %d, %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
}
