//
// Created by Alice on 2017.03.12.
//

#ifndef DIFFUSION_TEXTENCIPHER_H
#define DIFFUSION_TEXTENCIPHER_H

#include "../../cipher/structs.h"
#include "SegmentCipher.h"
#include "segments/serial_segment_cipher.h"
#include "../../tool/converter.h"
#include "info_factory.h"
#include "info_handler.h"

namespace lc{

    class TextCipher {
    public:

        virtual void init(Init& init, Info& info) = 0;

        virtual byte* run(byte* buf, int in_len, int& out_len) throw(DiffusionException) = 0;
    };

    class AbstractTextCipher : public TextCipher {
    protected:
        ~AbstractTextCipher() {
            delete (padding);
            delete (handler);
            delete (algorithm);
        }

        int level = 0, options = 0;
        Padding* padding = nullptr;
        KeyHandler* handler = nullptr;
        Algorithm* algorithm = nullptr;
        Init it;
        Info io;
    public:
        virtual void init(Init& init, Info& info) override {
            options = info.options;
            level = info.level;
        }
    };

    class TextEncipher : public AbstractTextCipher {
        Algorithm* algorithm = nullptr;
        EncipherBuffer worker;
        int N = 0;
    public:
        TextEncipher() {
            padding = new RandomBlockPadding();
        }

        void init(Init& init, Info& info) override {
            if (algorithm == nullptr) {
                algorithm = getAlgorithmFactory().make(CO::ENCIPHER, info.algorithm);
            }
            if (handler == nullptr || level != info.level) {
                freeInstance(handler);
                handler = getKeyHandlerFactory().make(info.level);
            }
            AbstractTextCipher::init(init, info);
            handler->init(init, info);
            worker.setHandler(*handler);
            worker.setPadding(padding);
            worker.setAlgorithm(*algorithm);
            worker.init(init, info);
            it = init;
            io = info;
            N = init.N;
        }

        byte* run(byte* in, int in_len, int& out_len) throw(DiffusionException) {
            if (!contains(options, CipherOption::ENCIPHER)) {
                throw DiffusionException("Invalid options: 0x" + Cvt::toString(options, 16));
            }
            int info_len = textInfoHandler.length();
            int real = N - padding->compute(N);
            int remainder = in_len % real;
            io.diff = remainder == 0 ? 0 : (real - remainder);
            out_len = std::ceil(1.0 * in_len / real) * N + info_len;
            byte* out = new byte[out_len];
            textInfoHandler.write(out, io);
            worker.run(in, out + info_len, in_len);
            return out;
        }

    };

    class TextDecipher : public AbstractTextCipher {
        DecipherBuffer worker;
        Algorithm* algorithm = nullptr;
        int A_VSR = 0;
    public:
        TextDecipher() {
            padding = new RandomBlockPadding();
        }

        virtual void init(Init& init, Info& info) override {
            if (algorithm == nullptr || A_VSR != info.algorithm) {
                freeInstance(algorithm);
                algorithm = getAlgorithmFactory().make(CO::DECIPHER, info.algorithm);
            }
            if (handler == nullptr || level != info.level) {
                freeInstance(handler);
                handler = getKeyHandlerFactory().make(info.level);
            }
            AbstractTextCipher::init(init, info);
            handler->init(init, info);
            worker.setPadding(padding);
            worker.setHandler(*handler);
            worker.setAlgorithm(*algorithm);
            worker.init(init, info);
            A_VSR = info.algorithm;
        }


        byte* run(byte* in, int in_len, int& out_len) throw(DiffusionException) {
            byte* out = new byte[out_len];
            int len = textInfoHandler.length();
            worker.run(in + len, out, in_len - len);
            out_len -= io.diff;
            return out;
        }
    };

    class TextDecipherWrapper : public TextDecipher {
    public:
        void init(Init& init, Info& info) override {
            it = init;
            io = info;
        }

        byte* run(byte* in, int in_len, int& out_len) throw(DiffusionException) {
            int info_len = textInfoHandler.length();
            if (in_len < info_len) {
                throw DiffusionException(I18N->gf(ERROR_TEXT_LEN_INC, in_len));
            }
            textInfoHandler.read(in, it, io);
            int N = it.N;
            int count = N - padding->compute(N);
            out_len = ceil(1.0 * (in_len - info_len) / N) * count;
            TextDecipher::init(it, io);
            return TextDecipher::run(in, in_len, out_len);
        }
    };
}
#endif //DIFFUSION_TEXTENCIPHER_H
