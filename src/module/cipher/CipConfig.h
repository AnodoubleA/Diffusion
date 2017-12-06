//
// Created by Alice on 2017.03.21.
//

#ifndef DIFFUSION_CIPCONFIG_H
#define DIFFUSION_CIPCONFIG_H


#include "../fs/FileSmash.h"
#include "AlgorithmFactory.h"
#include "../fs/file_smash_factory.h"
#include "key_handler_factory.h"

namespace lc{
    typedef class CipConfig {
    public:
        //@formatter:off
        constexpr static const char* HEADER = "DC3.14";
        constexpr static const char* REDAEH = "41.3CD";
        constexpr static const char HEADER_SIZE = 6;
        //@formatter:off
    } CCfg;

    extern AlgorithmFactory& getAlgorithmFactory();
    extern FileSmashFactory& getFileSmashFactory();
    extern KeyHandlerFactory& getKeyHandlerFactory();

    extern void freeInstance(Reusable* instance);
}
#endif //DIFFUSION_CIPCONFIG_H
