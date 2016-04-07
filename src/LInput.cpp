/*
 * LInput.cpp
 *
 *  Created on: Apr 7, 2016
 *      Author: luodichen
 */

#include "LInput.h"

LInput::LInput()
    : m_tWorkThread((pthread_t)(-1))
    , m_strBuffer("")
{

}

LInput::~LInput()
{
    if ((pthread_t)(-1) != m_tWorkThread)
    {
        pthread_cancel(m_tWorkThread);
        pthread_join(m_tWorkThread, nullptr);
    }
}

int LInput::Init()
{
    int nRet = pthread_create(&m_tWorkThread, nullptr, WorkThread, this);
    if (0 != nRet)
        return nRet;

    return nRet;
}

void *LInput::WorkThread(void *pSelf)
{
    LInput *pThis = (LInput *)pSelf;

    for (;;)
    {
        int nChar = getchar();
        if ((nChar >= 'a' && nChar <= 'z')
                || (nChar >= 'A' && nChar <= 'Z')
                || (nChar >= '0' && nChar <= '9'))
        {
            pThis->m_strBuffer += (char)nChar;
            pThis->BufferChanged(pThis->m_strBuffer);
        }
        else if (nChar == '\b' && pThis->m_strBuffer.length() > 0)
        {
            pThis->m_strBuffer.erase(pThis->m_strBuffer.end() - 1);
            pThis->BufferChanged(pThis->m_strBuffer);
        }
        else if (nChar == '\n' || nChar == '\r')
        {
            pThis->CommandConfirm(pThis->m_strBuffer);
            pThis->m_strBuffer = "";
        }
    }
    return nullptr;
}
