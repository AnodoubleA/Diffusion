//
// Created by Alice on 2017.03.14.
//

#ifndef DIFFUSION_ABSTRACTFILECIPHER_H
#define DIFFUSION_ABSTRACTFILECIPHER_H

#include "FileCipher.h"
#include "Padding.h"
#include "KeyHandler.h"
#include "../config/Config.h"
#include "InfoHeader.h"

namespace lc{
    class AbstractFileCipher : public FileCipher {
    protected:
        Padding* padding = getPadding();
        KeyHandler* handler = nullptr;
        Algorithm* algorithm = nullptr;
        BufferMessenger* contact;
        Info io;
        AlgorithmInfo it;

    public:

        ~AbstractFileCipher() {
            delete (padding);
        }

        int version() override {
            return 1;
        }

        void init(AlgorithmInfo& init, Info& info, BufferMessenger* contact) override {
            this->contact = contact;
            io = info;
            it = init;
        }

        void deinit() override {

        }

    protected:
        virtual Padding* getPadding() {
            return new RandomBlockPadding();
        }
    };

}
#endif //DIFFUSION_ABSTRACTFILECIPHER_H
