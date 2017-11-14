//
// Created by Alice on 2017.03.18.
//
#include "../../cipher/schedulers.h"
#include "text_cipher_command.h"

namespace lc{
    namespace npcmd{
        int batch = 1;
        Scheduler<Item*>* scheduler = nullptr;

        FileFilter filter;
        TextEncipher* textEncipher = nullptr;
        TextDecipher* textDecipher = nullptr;

        Scheduler<Item*>& getScheduler() {
            if (scheduler == nullptr) {
                scheduler = new SyncCipherScheduler();
            }
            return *scheduler;
        }

        TextEncipher& getTextEncipher() {
            if (textEncipher == nullptr) {
                textEncipher = new TextEncipher();
            }
            return *textEncipher;
        }

        TextDecipher& getTextDecipher() {
            if (textDecipher == nullptr) {
                textDecipher = new TextDecipherWrapper();
            }
            return *textDecipher;
        }
    }
}
