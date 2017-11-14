//
// Created by Alice on 2017.03.10.
//
#pragma once
#ifndef DIFFUSION_WORKER_H
#define DIFFUSION_WORKER_H

#include "../core/DiffusionException.h"
#include "reusable.h"

namespace lc{
    template<class T>
    class Worker : public Reusable {
    public:
        //@formatter:off
        static const int ONERROR        = -1;
        static const int STANDARY       = 1 << 0;
        static const int RUNNING        = 1 << 1;
        static const int TERMINATED     = 1 << 2;
        static const int COMPLETED      = 1 << 4;
        //@formatter:off

        virtual int status() = 0;

        virtual bool interrupt()throw(DiffusionException) = 0;

        virtual uint64 run(T& job)throw(DiffusionException) = 0;

        virtual bool support(int options) = 0;

    };
}
#endif //DIFFUSION_WORKER_H
