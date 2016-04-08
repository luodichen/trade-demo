/*
 * LMarketDataHandler.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: luodichen
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "ThostFtdcMdApi.h"
#include "LMarketDataHandler.h"
#include "LScreen.h"
#include "LFileScreen.h"

#define STRCPY_S(d, s) strncpy((d), (s), sizeof(d))

LMarketDataHandler::LMarketDataHandler(CThostFtdcMdApi *pApi, const char *szBroker,
        const char *szUser, const char *szPassword, FLAGS flags)
    : m_pApi(pApi), m_strBroker(szBroker), m_strUser(szUser), m_strPassword(szPassword)
    , m_pScreen(nullptr), m_objInputHandler(this), m_objFlags(flags)
{
    sem_init(&m_semHandlerCompleted, 0, 0);
    // m_objInputHandler.Init();
    if (flags.enMode == LMarketDataHandler::FLAGS::M_NORMAL)
    {
        m_pScreen = new LScreen();
    }
    else if (flags.enMode == LMarketDataHandler::FLAGS::M_FILE)
    {
        m_pScreen = new LFileScreen(flags.strOutputFilePath.c_str(),
                flags.strLogFilePath.c_str());
    }

    m_pScreen->Log("connecting to server...");
}

LMarketDataHandler::~LMarketDataHandler()
{
    if (nullptr != m_pScreen)
    {
        delete m_pScreen;
        m_pScreen = nullptr;
    }
}

void LMarketDataHandler::OnFrontConnected()
{
    CThostFtdcReqUserLoginField objLoginReq;
    STRCPY_S(objLoginReq.BrokerID, m_strBroker.c_str());
    STRCPY_S(objLoginReq.UserID, m_strUser.c_str());
    STRCPY_S(objLoginReq.Password, m_strPassword.c_str());

    m_pScreen->Log("connected.");
    m_pScreen->Log("login - BrokerID: %s, UserID: %s",
            m_strBroker.c_str(), m_strUser.c_str());
    m_pApi->ReqUserLogin(&objLoginReq, 0);
}

void LMarketDataHandler::OnFrontDisconnected(int nReason)
{
    m_pScreen->Log("disconnected");
}

void LMarketDataHandler::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
                                        CThostFtdcRspInfoField *pRspInfo,
                                        int nRequestID, bool bIsLast)
{
    m_pScreen->Log("user logged in, err=%d, msg=%s", pRspInfo->ErrorID,
            pRspInfo->ErrorMsg);

    if (m_objFlags.strInstrument != "")
    {
        char szInstrument[32] = { 0 };
        char *szInstrumentPackage[] = { szInstrument };
        STRCPY_S(szInstrument, m_objFlags.strInstrument.c_str());

        int nRet = m_pApi->SubscribeMarketData(szInstrumentPackage, 1);
        m_pScreen->Log("subscribe %s, returns %d", szInstrument, nRet);
    }
}

void LMarketDataHandler::OnRspError(CThostFtdcRspInfoField *pRspInfo,
                                    int nRequestID, bool bIsLast)
{
    m_pScreen->Log("error: %d, %s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
}

void LMarketDataHandler::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
    m_pScreen->Log("market data received");
    m_pScreen->Log("%s: %.2f", pDepthMarketData->InstrumentID,
            pDepthMarketData->LastPrice);

    auto md = DepthMarketDataParser(pDepthMarketData);
    m_pScreen->RefreshContent(md);

    if (m_objFlags.enMode == LMarketDataHandler::FLAGS::M_NORMAL
            || m_objFlags.enMode == LMarketDataHandler::FLAGS::M_FILE)
    {
        char szInstrument[32] = { 0 };
        char *szInstrumentPackage[] = { szInstrument };
        STRCPY_S(szInstrument, m_objFlags.strInstrument.c_str());
        m_pApi->UnSubscribeMarketData(szInstrumentPackage, 1);

        sem_post(&m_semHandlerCompleted);
    }
}

void LMarketDataHandler::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument,
                                            CThostFtdcRspInfoField *pRspInfo,
                                            int nRequestID, bool bIsLast)
{
    m_pScreen->Log("market subscribe response: %d, %s",
            pRspInfo->ErrorID, pRspInfo->ErrorMsg);
}

std::vector<std::pair<std::string, std::string>> LMarketDataHandler::DepthMarketDataParser(
        const CThostFtdcDepthMarketDataField *pMarketData)
{
    return {
        KVPair(pMarketData->InstrumentID, "InstrumentID", "%s"),
        KVPair(pMarketData->TradingDay, "TradingDay", "%s"),
        KVPair(pMarketData->UpdateTime, "UpdateTime", "%s"),
        KVPair(pMarketData->LastPrice, "LastPrice", "%.2f"),
        KVPair(pMarketData->OpenPrice, "OpenPrice", "%.2f"),
        KVPair(pMarketData->ClosePrice, "ClosePrice", "%.2f"),
        KVPair(pMarketData->HighestPrice, "HighestPrice", "%.2f"),
        KVPair(pMarketData->LowestPrice, "LowestPrice", "%.2f"),
        KVPair(pMarketData->AveragePrice, "AveragePrice", "%.2f"),
    };
}

LMarketDataHandler::LInputHandler::LInputHandler(LMarketDataHandler *pMarketDataHandler)
    : m_pMarketDataHandler(pMarketDataHandler)
{

}

void LMarketDataHandler::LInputHandler::BufferChanged(std::string strBuffer)
{

}

void LMarketDataHandler::LInputHandler::CommandConfirm(std::string strCommand)
{
    m_pMarketDataHandler->m_pScreen->RefreshInput(strCommand);
}

void LMarketDataHandler::WaitForHandler()
{
    if (m_objFlags.enMode == FLAGS::MODE::M_NORMAL
            || m_objFlags.enMode == FLAGS::MODE::M_FILE)
    {
        struct timespec timeout = { 0, 0 };
        timeout.tv_sec = time(nullptr) + 5;
        if (-1 == sem_timedwait(&m_semHandlerCompleted, &timeout))
        {
            m_pScreen->Log("timed out");
        }
    }
    else
    {
        sem_wait(&m_semHandlerCompleted);
    }
}

template <>
bool IsMaxDouble<>(double d)
{
    return d == DBL_MAX;
}
