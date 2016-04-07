/*
 * LConfig.h
 *
 *  Created on: Apr 6, 2016
 *      Author: luodichen
 */

#ifndef SRC_LCONFIG_H_
#define SRC_LCONFIG_H_

#include <stdlib.h>

class LConfig
{
public:
    LConfig();
    virtual ~LConfig();

    int Load(const char *szPath);

public:
    char m_szServer[1024];
    char m_szBrokerID[1024];
    char m_szUserID[1024];
    char m_szPassword[1024];
};

#endif /* SRC_LCONFIG_H_ */
