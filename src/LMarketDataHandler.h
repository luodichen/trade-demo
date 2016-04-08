/*
 * LMarketDataHandler.h
 *
 *  Created on: Apr 5, 2016
 *      Author: luodichen
 */

#ifndef LMARKETDATAHANDLER_H_
#define LMARKETDATAHANDLER_H_

#include "ThostFtdcMdApi.h"
#include "LInput.h"
#include "IScreen.h"
#include <vector>
#include <string>
#include <limits>
#include <cfloat>
#include <utility>
#include <semaphore.h>

template <typename Tx>
bool IsMaxDouble(Tx d)
{
    return false;
}

template <>
bool IsMaxDouble<>(double d);

class LMarketDataHandler : public CThostFtdcMdSpi
{
public:
    typedef struct tagFLAGS
    {
        enum MODE {
            M_NORMAL        = 0,
            M_FILE          = 1,
            M_INTERACTIVE   = 2
        } enMode;

        std::string strInstrument;
        std::string strOutputFilePath;
        std::string strLogFilePath;

        tagFLAGS()
            : enMode(M_NORMAL)
            , strInstrument("")
            , strOutputFilePath("")
            , strLogFilePath("")
        {

        }
    } FLAGS;

public:
    LMarketDataHandler(CThostFtdcMdApi *pApi, const char *szBroker,
            const char *szUser, const char *szPassword, FLAGS flags);
    virtual ~LMarketDataHandler();

public:
    void WaitForHandler();

private:
    class LInputHandler : public LInput
    {
    public:
        LInputHandler(LMarketDataHandler *pMarketDataHandler);

    protected:
        virtual void BufferChanged(std::string strBuffer);
        virtual void CommandConfirm(std::string strCommand);

    private:
        LMarketDataHandler *m_pMarketDataHandler;
    };

private:
    virtual void OnFrontConnected();
    virtual void OnFrontDisconnected(int nReason);
    virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
                                CThostFtdcRspInfoField *pRspInfo,
                                int nRequestID, bool bIsLast);
    virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo,
                            int nRequestID, bool bIsLast);
    virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);
    virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument,
                                    CThostFtdcRspInfoField *pRspInfo,
                                    int nRequestID, bool bIsLast);

private:
    static std::vector<std::pair<std::string, std::string>> DepthMarketDataParser(
            const CThostFtdcDepthMarketDataField *pMarketData);

    template <typename T>
    static std::pair<std::string, std::string> KVPair(const T &field,
            const char *szKey, const char *szFormat)
    {
        char szValue[1024] = { 0 };

        if (IsMaxDouble(field))
        {
            return { szKey, "-" };
        }

        snprintf(szValue, sizeof(szValue), szFormat, field);
        return { szKey, szValue };
    }

private:
    CThostFtdcMdApi *m_pApi;
    std::string m_strBroker;
    std::string m_strUser;
    std::string m_strPassword;

    //LScreen m_objScreen;
    IScreen *m_pScreen;
    LInputHandler m_objInputHandler;
    FLAGS m_objFlags;
    sem_t m_semHandlerCompleted;
};

#endif /* LMARKETDATAHANDLER_H_ */
