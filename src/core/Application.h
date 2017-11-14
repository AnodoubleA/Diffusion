//
// Created by Alice on 2017.03.07.
//
#pragma once
#ifndef DIFFUSION_APPLICATION_H
#define DIFFUSION_APPLICATION_H

#include "../module/config/type_config.h"
#include "../module/i18n/i18N.h"

namespace lc{
    extern TypeConfig* config;

    class Application {
    public:
        static void initialize();

        static void startup();
    };
}
#endif //DIFFUSION_APPLICATION_H
