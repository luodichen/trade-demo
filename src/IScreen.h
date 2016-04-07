/*
 * IScreen.h
 *
 *  Created on: Apr 7, 2016
 *      Author: luodichen
 */

#ifndef SRC_ISCREEN_H_
#define SRC_ISCREEN_H_

#include <vector>
#include <string>
#include <utility>

class IScreen
{
public:
    IScreen() { };
    virtual ~IScreen() { };

    virtual void RefreshContent(std::vector<std::pair<std::string, std::string>> &vtPairs) = 0;

    //template <typename ... ARGS>
    virtual void Log(const char *szFormat, ...) = 0;

    virtual void RefreshInput(std::string strContent) = 0;
};

#endif /* SRC_ISCREEN_H_ */
