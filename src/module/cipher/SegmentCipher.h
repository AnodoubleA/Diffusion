//
// Created by Alice on 2017.03.01.
//
#pragma once
#ifndef DIFFUSION_SEGMENTCIPHER_H
#define DIFFUSION_SEGMENTCIPHER_H

#include "../../core/types.h"

#include "Segment.h"
#include "SessionInfo.h"

namespace lc {
    class SegmentCipher : public Segment, public Reusable {

    public:

        virtual void init(SessionInfo* config) = 0;

        virtual void deinit() = 0;

        virtual bool support(uint64 options) = 0;
    };
}
#endif //DIFFUSION_SEGMENTCIPHER_H
