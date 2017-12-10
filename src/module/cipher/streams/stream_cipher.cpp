//
// Created by Angel on 2017/12/6.
//
#include "stream_cipher.h"

namespace lc {
    uint64 StreamEncipher::run_non_fill(std::istream& in, std::ostream& out, uint64 length)  throw(DiffusionException) {
        if (length == -1) {
            length = get_length(in);
        }
        uint64 round = length / cache;
        uint64 remainder = length % cache;
        for (uint64 i = 0; i < round; i++) {
            in.read((char*) buf_in, cache);
            worker.run(buf_in, cache);
            out.write((char*) buf_in, cache);
            contact->addDone(cache);
        };
        if (remainder > 0) {
            in.read((char*) buf_in, remainder);
            uint64 count = worker.run(buf_in, remainder);
            padding->padding(buf_in + remainder - session->CI->diff, session->CI->diff);
            out.write((char*) buf_in, count);
            contact->addDone(remainder);
        }
        out.flush();
        return (uint64) ceil(1.0 * length / N) * N;
    }

    uint64 StreamEncipher::run_fill(std::istream& in, std::ostream& out, uint64 length)  throw(DiffusionException) {
        if (length == -1) {
            length = get_length(in);
        }
        uint64 sin = (cache / N) * (N - fill);
        uint64 round = length / sin;
        uint64 remainder = length % sin;
        for (uint64 i = 0; i < round; i++) {
            in.read((char*) buf_in, sin);
            worker.run(buf_in, buf_out, sin);
            out.write((char*) buf_out, cache);
            contact->addDone(sin);
        }
        if (remainder > 0) {
            in.read((char*) buf_in, remainder);
            uint64 count = worker.run(buf_in, buf_out, remainder);
            out.write((char*) buf_out, count);
            contact->addDone(remainder);
        }
        out.flush();
        return (uint64) ceil(1.0 * length / (N - fill)) * N;
    }

    ///
    //
    //
    uint64 StreamDecipher::run_non_fill(std::istream& in, std::ostream& out, uint64 length)  throw(DiffusionException) {
        if (length == -1) {
            length = get_length(in);
        }
        uint64 round = length / cache;
        uint64 remainder = length % cache;
        for (uint64 i = 0; i < round; i++) {
            in.read((char*) buf_in, cache);
            worker.run(buf_in, cache);
            out.write((char*) buf_in, cache);
            contact->addDone(cache);
        };
        uint64 count = 0;
        if (remainder > 0) {
            in.read((char*) buf_in, remainder);
            count = worker.run(buf_in, remainder);
            out.write((char*) buf_in, count - session->CI->diff);
            contact->addDone(remainder);
        }
        return length - session->CI->diff;
    }

    uint64 StreamDecipher::run_fill(std::istream& in, std::ostream& out, uint64 length)  throw(DiffusionException) {
        if (length == -1) {
            length = get_length(in);
        }
        int sin = (cache / N) * (N - fill);
        uint64 round = length / cache;
        uint64 remainder = length % cache;
        for (uint64 i = 0; i < round; i++) {
            in.read((char*) buf_in, cache);
            worker.run(buf_in, buf_out, cache);
            out.write((char*) buf_out, sin);
            contact->addDone(cache);
        }
        if (remainder > 0) {
            in.read((char*) buf_in, remainder);
            uint64 count = worker.run(buf_in, buf_out, remainder);
            out.write((char*) buf_out, count - session->CI->diff);
            contact->addDone(remainder);
        }
        out.flush();
        return length - session->CI->diff;
    }
}
