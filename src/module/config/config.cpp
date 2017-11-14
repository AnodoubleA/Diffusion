//
// Created by Alice on 2017.03.18.
//

#include "../../mvc/notify/HashClassifyNotification.h"
#include "../i18n/i18N.h"
#include "ini_config.h"
#include "../fm/filemapping.h"
#include "../cmds/cmd_factory_impl.h"

namespace lc{
    //@formatter:off
    const int EXTEND_ROUND      = 1;
    const int MIN_SIZE          = 32 << 3;
    const int MAX_SIZE          = 65536 << 3;
    const int MIN_KEY_LENGTH    = 30;
    const int MIN_SMASH_TIMES   = 10;
    const int MAX_SMASH_TIMES   = 100;
    const int MIN_KEY_LEVEL     = 1;
    const int MAX_KEY_LEVEL     = 2;
    const int MIN_BUFMLT        = 1;
    const int MAX_BUFMLT        = UINT16_MAX;

    const int DEFAULT_SMASH_TIMES = 49;
    int BUFFER_MULTIPLE         = 1024;
    int CORE_COUNT_LOG          = 0;
    int CORE_BUFFER_LOG         = 20;
    std::string apppath;


    const char* EXTEND_FILE_NAME = ".dc";
    bool USE_FILE_EXNAME = true;

    HashClassifyNotification* notification = new HashClassifyNotification();

    ClassifyNotification& getNotification(){
        return *notification;
    }
    CommandFactory* commandFactory;
    const int allocationGranularity = FileMapping::allocationGranularity();
    CommandFactory& getCommandFactory(){
        if(commandFactory == nullptr){
            commandFactory = new CachedCommandFactory();
        }
        return *commandFactory;
    };
    //Configuration syscfg;
}
