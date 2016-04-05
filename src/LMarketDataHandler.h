/*
 * LMarketDataHandler.h
 *
 *  Created on: Apr 5, 2016
 *      Author: luodichen
 */

#ifndef LMARKETDATAHANDLER_H_
#define LMARKETDATAHANDLER_H_

#include "ThostFtdcMdApi.h"

class LMarketDataHandler : public CThostFtdcMdSpi
{
public:
    LMarketDataHandler(CThostFtdcMdApi *pApi);
    virtual ~LMarketDataHandler();

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
    CThostFtdcMdApi *m_pApi;
};

#endif /* LMARKETDATAHANDLER_H_ */
