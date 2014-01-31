/**
 * zling:
 *  light-weight lossless data compression utility.
 *
 * Copyright (C) 2012-2013 by Zhang Li <zhangli10 at baidu.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * @author zhangli10<zhangli10@baidu.com>
 * @brief  libzling.
 */
#ifndef SRC_LIBZLING_H
#define SRC_LIBZLING_H

#include "inc.h"

namespace baidu {
namespace zling {

struct IInputer {
    virtual size_t GetData(unsigned char* buf, size_t len) = 0;
    virtual bool IsEnd() = 0;
    virtual bool IsErr() = 0;
};
struct IOutputer {
    virtual size_t PutData(unsigned char* buf, size_t len) = 0;
    virtual bool IsErr() = 0;
};
struct IActionHandler {
    virtual void OnInit() {}
    virtual void OnDone() {}
    virtual void OnProcess() {}

    inline void SetInputerOutputer(IInputer* inputer, IOutputer* outputer, bool is_encode) {
        m_is_encode = is_encode;
        m_inputer = inputer;
        m_outputer = outputer;
    }
    inline bool IsEncode() {
        return m_is_encode;
    }
    inline IInputer* GetInputer() {
        return m_inputer;
    }
    inline IOutputer* GetOutputer() {
        return m_outputer;
    }

private:
    bool       m_is_encode;
    IInputer*  m_inputer;
    IOutputer* m_outputer;
};

int Encode(IInputer* inputer, IOutputer* outputer, IActionHandler* action_handler = NULL);
int Decode(IInputer* inputer, IOutputer* outputer, IActionHandler* action_handler = NULL);

}  // namespace zling
}  // namespace baidu
#endif  // SRC_LIBZLING_H