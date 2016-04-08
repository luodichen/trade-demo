/*
 * LFileScreen.h
 *
 *  Created on: Apr 8, 2016
 *      Author: luodichen
 */

#ifndef SRC_LFILESCREEN_H_
#define SRC_LFILESCREEN_H_

#include "IScreen.h"
#include <vector>
#include <string>
#include <utility>
#include <stdio.h>
#include <time.h>

class LFileScreen : public IScreen
{
public:
    LFileScreen(const char *szOutputFilePath, const char *szLogFilePath);
    virtual ~LFileScreen();

public:
    virtual void RefreshContent(std::vector<std::pair<std::string, std::string>> &vtPairs);
    virtual void Log(const char *szFormat, ...);
    virtual void RefreshInput(std::string strContent);

private:
    std::string m_strOutputFilePath;
    std::string m_strLogFilePath;
};

#endif /* SRC_LFILESCREEN_H_ */
