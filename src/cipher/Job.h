//
// Created by Alice on 2017.03.10.
//
#pragma once
#ifndef DIFFUSION_JOB_H
#define DIFFUSION_JOB_H
namespace lc{
    class Job {
    public:
        //@formatter:off
        static const int STANDBY          = 1 << 0;
        static const int PAUSED           = 1 << 1;
        static const int CIPHER_BEGIN     = 1 << 2;
        static const int CIPHER_END       = 1 << 3;
        static const int INTERRUPTED      = 1 << 4;
        static const int DEL_BEGIN        = 1 << 5;
        static const int DEL_END          = 1 << 6;
        static const int COMPLETED        = 1 << 7;

        static const int ONERROR          = 1 << 1;
        //@formatter:on

        int ID = 0;

        virtual int status() = 0;

        virtual int flags() = 0;
    };
}
#endif //DIFFUSION_JOB_H
