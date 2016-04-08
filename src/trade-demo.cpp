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

// a dirty solution for the `double free or corruption` problem in libthostmduserapi.so
#define EXIT() kill(getpid(), 2)

static void usage(const char *szCommand)
{
    printf("Usage: %s [-c configure file path] [-i instrument id] [-o output file path] [-l log file path] [-a|-f]\n", szCommand);
}

int main(int argc, char **argv)
{
    LConfig config;
    CThostFtdcMdApi *pApi = CThostFtdcMdApi::CreateFtdcMdApi();

    LMarketDataHandler::FLAGS flags;
    std::string strConfigFile = "/etc/trade-demo.conf";
    flags.enMode = LMarketDataHandler::FLAGS::M_NORMAL;

    int opt = 0;
    while ((opt = getopt(argc, argv, "afc:i:o:l:")) != -1)
    {
        switch (opt)
        {
        case 'a':
            // flags.enMode = LMarketDataHandler::FLAGS::M_INTERACTIVE;
            fprintf(stderr, "interactive mode unimplemented temporarily\n");
            EXIT();
            break;

        case 'f':
            flags.enMode = LMarketDataHandler::FLAGS::M_FILE;
            break;

        case 'c':
            strConfigFile = optarg;
            break;

        case 'i':
            flags.strInstrument = optarg;
            break;

        case 'o':
            flags.strOutputFilePath = optarg;
            break;

        case 'l':
            flags.strLogFilePath = optarg;
            break;

        default:
            usage(argv[0]);
            EXIT();
        }
    }

    if (0 != config.Load(strConfigFile.c_str()))
    {
        printf("load configure file %s failed\n", strConfigFile.c_str());
        exit(-1);
    }

    LMarketDataHandler handler(pApi, config.m_szBrokerID, config.m_szUserID, config.m_szPassword, flags);
    pApi->RegisterSpi(&handler);
    pApi->RegisterFront(config.m_szServer);
    pApi->Init();

    handler.WaitForHandler();
    pApi->Release();

    EXIT();

    return 0;
}
