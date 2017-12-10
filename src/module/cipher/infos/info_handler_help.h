//
// Created by Angel on 2017/3/29.
//

#ifndef DIFFUSION_INFO_HANDLER_HELP_H
#define DIFFUSION_INFO_HANDLER_HELP_H

#include "../info_handler.h"
#include "../InfoHandlerFactory.h"

namespace lc{

    class TextInfoHandler : public AbstractInfoHandler {
        InfoWriter* writer = InfoHandlerFactory::getWriter(0, CO::TEXT);
        InfoReader* reader;
    public:
        int length() override {
            return writer->length();
        }

        void read(byte buf[], AlgorithmInfo& init, Info& info) throw(DiffusionException) {
            read(buf, info);
            T::computeInit(init, info.group, EXTEND_ROUND);
        }

        void read(byte buf[], Info& info) throw(DiffusionException) {
            int offset = IH::HEADER_SIZE;
            if (memcmp(IH::HEADER, buf, offset) != 0) {
                throw DiffusionException(I18N->get(ERROR_TEXT_FORMAT_INC));
            }
            int v = buf[offset] & 0xFF;
            if (reader == nullptr || reader->version() != v) {
                freeInstance(reader);
                reader = InfoHandlerFactory::getReader(0, CO::TEXT);
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
        InfoWriter* writer = InfoHandlerFactory::getWriter(0, CO::FILE);
        InfoReader* reader;
    public:
        int length() override {
            return writer->length();
        }

        void read(byte buf[], Info& info) throw(DiffusionException) {

        }

        void read(std::string& file, AlgorithmInfo& init, Info& info) throw(DiffusionException) {
            std::ifstream in(file, std::ios::in | std::ios::binary);
            in.seekg(0, std::ios::end);
            int64 file_len = in.tellg();
            int headSize = IH::HEADER_SIZE + 1;
            int64 size = file_len - headSize;
            if (size <= 0) {
                throw DiffusionException(I18N->gf(ERROR_FILE_LEN_INC, file.c_str()));
            }
            byte buf[headSize];
            in.seekg(size);
            in.read((char*) buf, headSize);
            if (memcmp(buf + 1, IH::REDAEH, (size_t) (IH::HEADER_SIZE)) != 0) {
                throw DiffusionException(I18N->gf(ERROR_FILE_FORMAT_INC, file.c_str()));
            }
            int v = buf[0] & 0xFF;
            if (reader == nullptr || reader->version() != v) {
                freeInstance(reader);
                reader = InfoHandlerFactory::getReader(0, CO::FILE);
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
}
#endif //DIFFUSION_INFO_HANDLER_HELP_H
