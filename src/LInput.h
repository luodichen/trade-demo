/*
 * LInput.h
 *
 *  Created on: Apr 7, 2016
 *      Author: luodichen
 */

#ifndef SRC_LINPUT_H_
#define SRC_LINPUT_H_

#include <pthread.h>
#include <string>

class LInput
{
public:
    LInput();
    virtual ~LInput();

    int Init();

protected:
    virtual void BufferChanged(std::string strBuffer) = 0;
    virtual void CommandConfirm(std::string strCommand) = 0;

private:
    static void *WorkThread(void *pSelf);

private:
    pthread_t m_tWorkThread;
    std::string m_strBuffer;
};

#endif /* SRC_LINPUT_H_ */
