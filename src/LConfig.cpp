/*
 * LConfig.cpp
 *
 *  Created on: Apr 6, 2016
 *      Author: luodichen
 */

#include "LConfig.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <string>

LConfig::LConfig()
    : m_szServer({ 0 })
    , m_szBrokerID({ 0 })
    , m_szUserID({ 0 })
    , m_szPassword({ 0 })
{

}

LConfig::~LConfig()
{

}

int LConfig::Load(const char *szPath)
{
    FILE *fp = fopen(szPath, "r");
    if (nullptr == fp)
        return -1;

    char buffer[1024] = { 0 };

    std::map<std::string, char *> mapKeyMapper = {
            { "server", m_szServer },
            { "broker", m_szBrokerID },
            { "user", m_szUserID },
            { "password", m_szPassword }
    };
    while (nullptr != fgets(buffer, sizeof(buffer), fp))
    {
        char key[1024] = { 0 }, value[1024] = { 0 };
        sscanf(buffer, "%s %s", key, value);

        if (mapKeyMapper.find(key) != mapKeyMapper.end())
        {
            strcpy(mapKeyMapper[key], value);
        }
    }

    fclose(fp);
    return 0;
}
