//
// Created by Alice on 2017.03.01.
//
#ifndef DIFFUSION_STREAMCIPHER_H
#define DIFFUSION_STREAMCIPHER_H

#include <istream>
#include "Init.h"
#include "Info.h"
#include "../../core/DiffusionException.h"
#include "contacts/BufferContact.h"

namespace lc{

    class StreamCipher {
    public:
        virtual void init(SessionConfig* config, BufferContact* contact) = 0;

        virtual void deinit() = 0;

        virtual uint64 run(std::istream& in, std::ostream& out, uint64 length) throw(DiffusionException) = 0;
    };
}
#endif //DIFFUSION_STREAMCIPHER_H
