//
// Created by Alice on 2017.03.21.
//

#ifndef DIFFUSION_FILE_SMASH_FACTORY_H
#define DIFFUSION_FILE_SMASH_FACTORY_H

#include "FileSmash.h"
#include "secure_file_smash.h"

namespace lc{
    class FileSmashFactory {
    public:
        virtual FileSmash* make() = 0;
    };

    class CachedFileSmashFactory : public FileSmashFactory {
        std::vector<FileSmash*> vector;
    public:
        FileSmash* make() override {
            for (FileSmash* item:vector) {
                if (item->lock()) {
                    return item;
                }
            }
            FileSmash* instance = new SecureFileSmash();
            instance->lock();
            vector.push_back(instance);
            return instance;
        }
    };
}
#endif //DIFFUSION_FILE_SMASH_FACTORY_H
