//
// Created by Angel on 2017/3/31.
//

#ifndef DIFFUSION_CMD_FACTORY_IMPL_H
#define DIFFUSION_CMD_FACTORY_IMPL_H

#include <vector>
#include "../../mvc/cmd/cmd_factory.h"
#include "cmds.h"
#include "text_cipher_command.h"

namespace lc{
    class CachedCommandFactory : public CommandFactory {
        std::vector<Command*> vector;
    public:
        Command* make(int code) override {
//            for (Command* item:vector) {
//                if (item->lock()) {
//                    return item;
//                }
//            }
            Command* command = nullptr;
            switch (code) {
                case cmd::FILE_CIPHER:
                    command = new FileCipherCommand();
                    break;
                case cmd::TEXT_ENCIPHER:
                    command = new TextEncipherCommand();
                    break;
                case cmd::TEXT_DECIPHER:
                    command = new TextDecipherCommand();
                    break;
            }
//            vector.push_back(command);
            return command;
        }
    };
}
#endif //DIFFUSION_CMD_FACTORY_IMPL_H
