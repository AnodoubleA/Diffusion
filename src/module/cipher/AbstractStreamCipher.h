//
// Created by Angel on 2017/12/6.
//

#ifndef DIFFUSION_ABSTRACTSTREAMCIPHER_H
#define DIFFUSION_ABSTRACTSTREAMCIPHER_H

#include "StreamCipher.h"
#include "Algorithm.h"
#include "Padding.h"
#include "KeyHandler.h"

extern int allocationGranularity;
extern int BUFFER_MULTIPLE;

namespace lc {
    class AbstractStreamCipher : public StreamCipher {
    protected:
        byte* buf_in = nullptr;
        byte* buf_out = nullptr;
        Padding* padding = nullptr;
        KeyHandler* handler = nullptr;
        Algorithm* algorithm = nullptr;
        BufferContact* contact = nullptr;
        SessionConfig* config = nullptr;
        int N = 0, fill = 0, cache;
        bool pad = false;
    public:
        virtual ~AbstractStreamCipher() {
            delete[](buf_in);
            delete[](buf_out);
        }

        AbstractStreamCipher() {
            cache = allocationGranularity * BUFFER_MULTIPLE;
            buf_in = new byte[cache];
            buf_out = new byte[cache];
        }

        void setPadding(Padding* padding) {
            this->padding = padding;
        }

        void setHandler(KeyHandler& handler) {
            this->handler = &handler;
        }

        void setAlgorithm(Algorithm& algorithm) {
            this->algorithm = &algorithm;
        }

        virtual void init(SessionConfig* config, BufferContact* contact) {
            this->N = config->init->N;
            this->config = config;
            this->contact = contact;
            fill = padding == nullptr ? 0 : padding->compute(N);
            pad = (config->options & CO::PADDING) != 0;
        }
    };
}
#endif //DIFFUSION_ABSTRACTSTREAMCIPHER_H
