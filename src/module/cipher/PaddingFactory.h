//
// Created by Angel on 2017/12/7.
//

#ifndef DIFFUSION_PADDINGFACTORY_H
#define DIFFUSION_PADDINGFACTORY_H

#include "Padding.h"
#include "../cmds/options.h"
#include "paddings/RandomBlockPadding.h"

namespace lc{
    class PaddingFactory {
    public:
        static Padding* make(uint64 options) {
            if (options & CipherOption::PADDING) {
                return new RandomBlockPadding();
            }
            return nullptr;
        }
    };
}
#endif //DIFFUSION_PADDINGFACTORY_H
