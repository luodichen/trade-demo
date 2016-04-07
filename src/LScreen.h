/*
 * LScreen.h
 *
 *  Created on: Apr 6, 2016
 *      Author: luodichen
 */

#ifndef SRC_LSCREEN_H_
#define SRC_LSCREEN_H_

#include "IScreen.h"
#include <vector>
#include <string>
#include <utility>
#include <stdio.h>
#include <time.h>

class LScreen : public IScreen
{
public:
    LScreen();
    virtual ~LScreen();

    virtual void RefreshContent(std::vector<std::pair<std::string, std::string>> &vtPairs);

    /*
    template <typename ... ARGS>
    virtual void Log(const char *szFormat, ARGS ...args)
    {
        time_t tTime = time(nullptr);
        struct tm tmTime = { 0 };
        char szTime[128] = { 0 };
        strftime(szTime, sizeof(szTime), "%Y-%m-%d %H:%M:%S", localtime_r(&tTime, &tmTime));

        fprintf(stderr, "[%s] ", szTime);
        fprintf(stderr, szFormat, args...);
        fprintf(stderr, "\n");
    }
    */
    virtual void Log(const char *szFormat, ...);
    virtual void RefreshInput(std::string strContent);
};

#endif /* SRC_LSCREEN_H_ */
