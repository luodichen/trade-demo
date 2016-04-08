/*
 * LInterActiveScreen.h
 *
 *  Created on: Apr 8, 2016
 *      Author: luodichen
 */

#ifndef SRC_LINTERACTIVESCREEN_H_
#define SRC_LINTERACTIVESCREEN_H_

#include "IScreen.h"

class LInterActiveScreen : public IScreen
{
public:
    LInterActiveScreen();
    virtual ~LInterActiveScreen();

public:
    virtual void RefreshContent(std::vector<std::pair<std::string, std::string>> &vtPairs);
    virtual void Log(const char *szFormat, ...);
    virtual void RefreshInput(std::string strContent);
};

#endif /* SRC_LINTERACTIVESCREEN_H_ */
