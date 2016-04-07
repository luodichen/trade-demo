/*
 * LScreen.cpp
 *
 *  Created on: Apr 6, 2016
 *      Author: luodichen
 */


#include "LScreen.h"
#include <stdarg.h>

LScreen::LScreen()
    : IScreen()
{

}

LScreen::~LScreen()
{

}

void LScreen::RefreshContent(std::vector<std::pair<std::string, std::string>> &vtPairs)
{
    for (auto &item : vtPairs)
    {
        printf("%s:\t\t%s\n", item.first.c_str(), item.second.c_str());
    }
}

void LScreen::RefreshInput(std::string strContent)
{
    printf("%s\n", strContent.c_str());
}

void LScreen::Log(const char *szFormat, ...)
{
    time_t tTime = time(nullptr);
    struct tm tmTime = { 0 };
    char szTime[128] = { 0 };
    strftime(szTime, sizeof(szTime), "%Y-%m-%d %H:%M:%S", localtime_r(&tTime, &tmTime));

    fprintf(stderr, "[%s] ", szTime);

    va_list args;
    va_start(args, szFormat);
    vfprintf(stderr, szFormat, args);
    va_end(args);
    fprintf(stderr, "\n");
}
