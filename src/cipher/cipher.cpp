//
// Created by Alice on 2017.03.18.
//

#include "../module/random/SeedFactory.h"
#include "../module/random/Random.h"
#include "../module/fs/FileSmash.h"
#include "../module/fs/file_smash_factory.h"
#include "CipConfig.h"
#include "KeyHandler.h"
#include "info_factory.h"
#include "info_handler.h"
#include "../module/random/seed_factory_impl.h"
#include "../core/static_init.h"
#include "BufferCipher.h"

namespace lc{
    FileSmashFactory* fileSmash = nullptr;

    std::vector<BufferCipher*> buffer_map;

    FileSmashFactory& getFileSmashFactory() {
        if (fileSmash == nullptr) {
            fileSmash = new CachedFileSmashFactory();
        }
        return *fileSmash;
    }

    SeedFactory* seedFactory = nullptr;

    SeedFactory& getSeedFactory() {
        if (seedFactory == nullptr) {
            seedFactory = new SecureSeedFactory();
        }
        return *seedFactory;
    }

    void init_seedFactory() {
        getSeedFactory().init();
    }

    AlgorithmFactory* algorithmFactory = nullptr;

    AlgorithmFactory& getAlgorithmFactory() {
        if (algorithmFactory == nullptr) {
            algorithmFactory = new VersionedAlgorithmFactory();
        }
        return *algorithmFactory;
    }

    KeyHandlerFactory* keyHandlerFactory;

    KeyHandlerFactory& getKeyHandlerFactory() {
        if (keyHandlerFactory == nullptr) {
            keyHandlerFactory = new CachedKeyHandlerFactory();
        }
        return *keyHandlerFactory;
    }

    InfoFactory* infoFactory;

    InfoFactory& getInfoFactory() {
        if (infoFactory == nullptr) {
            infoFactory = new CachedInfoFactory();
        }
        return *infoFactory;
    }

    TextInfoHandler textInfoHandler;
    FileInfoHandler fileInfoHandler;

    void freeInstance(Reusable* instance) {
        if (instance != nullptr) {
            instance->unlock();
        }
    }
}
