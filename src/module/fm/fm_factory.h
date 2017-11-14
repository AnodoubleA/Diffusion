//
// Created by Angel on 2017/3/30.
//

#ifndef DIFFUSION_FILEMAPPING_FACTORY_H
#define DIFFUSION_FILEMAPPING_FACTORY_H

#include "filemapping.h"
#include "winfm.h"

namespace lc{
    extern std::vector<FileMapping*> vector_fm;

    typedef class FileMappingFactory {
    public:
        static FileMapping* make() {
            for (FileMapping* item:vector_fm) {
                if (item->lock()) {
                    return item;
                }
            }
            FileMapping* instance = new WinFileMapping();
            vector_fm.push_back(instance);
            instance->lock();
            return instance;
        }
    } FMFactory;

}
#endif //DIFFUSION_FILEMAPPING_FACTORY_H
