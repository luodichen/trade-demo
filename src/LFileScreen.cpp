/*
 * LFileScreen.cpp
 *
 *  Created on: Apr 8, 2016
 *      Author: luodichen
 */

#include "LFileScreen.h"
#include <stdarg.h>

LFileScreen::LFileScreen(const char *szOutputFilePath, const char *szLogFilePath)
    : IScreen()
    , m_strOutputFilePath(szOutputFilePath)
    , m_strLogFilePath(szLogFilePath)
{

}

LFileScreen::~LFileScreen()
{

}


void LFileScreen::RefreshContent(std::vector<std::pair<std::string, std::string>> &vtPairs)
{
    if ("" == m_strOutputFilePath)
        return;

    FILE *fp = fopen(m_strOutputFilePath.c_str(), "w");
    if (nullptr == fp)
    {
        Log("error: open file `%s` failed", m_strOutputFilePath.c_str());
        return;
    }

    for (auto &item : vtPairs)
    {
        fprintf(fp, "%s:\t\t%s\n", item.first.c_str(), item.second.c_str());
    }
    fclose(fp);
}

void LFileScreen::RefreshInput(std::string strContent)
{

}

void LFileScreen::Log(const char *szFormat, ...)
{
    FILE *fp = nullptr;

    if ("" == m_strLogFilePath)
    {
        fp = stderr;
    }
    else
    {
        fp = fopen(m_strLogFilePath.c_str(), "a");
        if (nullptr == fp)
            return;
    }

    time_t tTime = time(nullptr);
    struct tm tmTime = { 0 };
    char szTime[128] = { 0 };
    strftime(szTime, sizeof(szTime), "%Y-%m-%d %H:%M:%S", localtime_r(&tTime, &tmTime));

    fprintf(fp, "[%s] ", szTime);

    va_list args;
    va_start(args, szFormat);
    vfprintf(fp, szFormat, args);
    va_end(args);
    fprintf(fp, "\n");

    if (fp != stderr)
        fclose(fp);
}
