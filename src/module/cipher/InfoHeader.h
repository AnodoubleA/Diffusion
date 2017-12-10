//
// Created by Alice on 2017.03.21.
//

#ifndef DIFFUSION_INFOHEADER_H
#define DIFFUSION_INFOHEADER_H


#include "../fs/FileSmash.h"
#include "AlgorithmFactory.h"
#include "../fs/file_smash_factory.h"
#include "KeyHandlerFactory.h"

namespace lc {
    class DC3_14InfoHeader;

    typedef class InfoHeader {
    public:
        virtual const char* header() = 0;

        virtual const char* inHeader() = 0;

        virtual const int size() = 0;

        virtual const int identity() = 0;

        static InfoHeader& DC3_14();
    } IH;

    class DC3_14InfoHeader : public InfoHeader {
    private:
        constexpr static const char* HEADER = "DC3.14";
        constexpr static const int SIZE = 6;

    public:
        const char* header() override {
            return HEADER;
        }

        const int size() override {
            return 6;
        }

        const int identity() override {
            return 1;
        }
    };
}
#endif //DIFFUSION_INFOHEADER_H
