//
// Created by Alice on 2017.03.18.
//

#include "../module/random/SeedFactory.h"
#include "../module/random/Random.h"
#include "../module/fs/FileSmash.h"
#include "../module/fs/file_smash_factory.h"
#include "../module/cipher/InfoHeader.h"
#include "../module/cipher/KeyHandler.h"
#include "../module/cipher/InfoHandlerFactory.h"
#include "../module/cipher/infos/info_handler_help.h"
#include "../module/random/seed_factory_impl.h"
#include "../core/static_init.h"
#include "../module/cipher/SegmentCipher.h"

namespace lc{
    FileSmashFactory* fileSmash = nullptr;

    std::vector<SegmentCipher*> buffer_map;

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

    InfoHandlerFactory* infoFactory;

    InfoHandlerFactory& getInfoFactory() {
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
