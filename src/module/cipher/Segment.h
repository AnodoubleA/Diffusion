//
// Created by Angel on 2017/12/7.
//

#ifndef DIFFUSION_SEGMENT_H
#define DIFFUSION_SEGMENT_H

#include "../../core/types.h"

namespace lc{

    class Segment {

    public:

        /**
         * Process a buffer of in and output in buffer of out.
         * @param in
         * @param out
         * @param length input length
         * @return output length
         */
        virtual uint64 run(byte* in, byte* out, uint64 length) = 0;

        /**
         * Process a buffer.
         * @param in
         * @param length input length
         * @return output length
         */
        virtual uint64 run(byte* in, uint64 length) = 0;
    };
}
#endif //DIFFUSION_SEGMENT_H
