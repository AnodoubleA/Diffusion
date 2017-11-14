//
// Created by Angel on 2017/3/30.
//

#ifndef DIFFUSION_VALUES_H
#define DIFFUSION_VALUES_H

#define VALUE_NFD "Value not found for key: "

#include "../../mvc/notify/HashClassifyNotification.h"
#include "../../mvc/cmd/cmd_factory.h"


namespace lc{
    //@formatter:off
    extern std::string apppath;
    extern const int EXTEND_ROUND;
    extern const int MIN_SIZE;
    extern const int MAX_SIZE;
    extern const int MIN_KEY_LENGTH;
    extern const int DEFAULT_SMASH_TIMES;
    extern const int MIN_SMASH_TIMES;
    extern const int MAX_SMASH_TIMES;
    extern const int MIN_KEY_LEVEL;
    extern const int MAX_KEY_LEVEL;
    extern const int MIN_BUFMLT;
    extern const int MAX_BUFMLT;
    extern const int allocationGranularity;

    extern const char* EXTEND_FILE_NAME;

    extern int BUFFER_MULTIPLE;
    extern int CORE_COUNT_LOG;
    extern int CORE_BUFFER_LOG;
    extern bool USE_FILE_EXNAME;
}
#endif //DIFFUSION_VALUES_H
