//
// Created by Angel on 2017/3/29.
//

#ifndef DIFFUSION_INFO_HANDLER_H
#define DIFFUSION_INFO_HANDLER_H

#include "info.h"
#include "info_factory.h"

namespace lc{

    extern InfoFactory& getInfoFactory();

    class TextInfoHandler : public AbstractInfoHandler {
        InfoWriter* writer = getInfoFactory().getWriter(CO::TEXT, 0);
        InfoReader* reader;
    public:
        int length() override {
            return writer->length();
        }

        void read(byte buf[], Init& init, Info& info) throw(DiffusionException) {
            read(buf, info);
            T::computeInit(init, info.group, EXTEND_ROUND);
        }

        void read(byte buf[], Info& info) throw(DiffusionException) {
            int offset = CCfg::HEADER_SIZE;
            if (memcmp(CCfg::HEADER, buf, offset) != 0) {
                throw DiffusionException(I18N->get(ERROR_TEXT_FORMAT_INC));
            }
            int v = buf[offset] & 0xFF;
            if (reader == nullptr || reader->version() != v) {
                freeInstance(reader);
                reader = getInfoFactory().getReader(CO::TEXT, v);
            }
            if (reader == nullptr) {
                throw DiffusionException(I18N->gf(ERROR_TEXT_HVS_USP, v));
            }
            reader->read(buf + offset + 1, info);
        }

        void read(std::istream& in, Info& info) throw(DiffusionException) {

        }

        void write(byte buf[], Info& info) throw(DiffusionException) {
            writer->write(buf, info);
        }

        int version() override {
            return 0;
        }
    };

    class FileInfoHandler : public AbstractInfoHandler {
        InfoWriter* writer = getInfoFactory().getWriter(CO::FILE, 0);
        InfoReader* reader;
    public:
        int length() override {
            return writer->length();
        }

        void read(byte buf[], Info& info) throw(DiffusionException) {

        }

        void read(std::string& file, Init& init, Info& info) throw(DiffusionException) {
            std::ifstream in(file, std::ios::in | std::ios::binary);
            in.seekg(0, std::ios::end);
            int64 file_len = in.tellg();
            int headSize = CCfg::HEADER_SIZE + 1;
            int64 size = file_len - headSize;
            if (size <= 0) {
                throw DiffusionException(I18N->gf(ERROR_FILE_LEN_INC, file.c_str()));
            }
            byte buf[headSize];
            in.seekg(size);
            in.read((char*) buf, headSize);
            if (memcmp(buf + 1, CCfg::REDAEH, (size_t) (CCfg::HEADER_SIZE)) != 0) {
                throw DiffusionException(I18N->gf(ERROR_FILE_FORMAT_INC, file.c_str()));
            }
            int v = buf[0] & 0xFF;
            if (reader == nullptr || reader->version() != v) {
                freeInstance(reader);
                reader = getInfoFactory().getReader(CO::FILE, v);
            }
            if (reader == nullptr) {
                throw DiffusionException(I18N->gf(ERROR_FILE_HVS_USP, v, file.c_str()));
            }
            reader->read(in, info);
            T::computeInit(init, info.group, EXTEND_ROUND);
            in.close();
        }


        void read(std::istream& in, Info& info) throw(DiffusionException) {

        }

        void write(byte buf[], Info& info) throw(DiffusionException) {
            writer->write(buf, info);
        }

        int version() override {
            return 0;
        }
    };

    extern TextInfoHandler textInfoHandler;
    extern FileInfoHandler fileInfoHandler;
}
#endif //DIFFUSION_INFO_HANDLER_H
