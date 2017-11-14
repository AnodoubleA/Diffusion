//
// Created by Alice on 2017.03.17.
//

#ifndef C_TEST_LEVEL_H
#define C_TEST_LEVEL_H

#include <string>
#include "../../core/types.h"

namespace lc{
    struct LevelContext {
        uint64& number;
        std::string& options;
        void* target = nullptr;
    };

    class Level {
    public:
        virtual Level* next() = 0;

        virtual Level* init(LevelContext& context) {
            return this;
        }

        virtual Level* link(uint64 value, const std::string& flag) = 0;

        virtual bool format(LevelContext& context) = 0;
    };
}
#endif //C_TEST_LEVEL_H
