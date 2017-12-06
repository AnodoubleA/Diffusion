//
// Created by Angel on 2017/12/6.
//
#include "serial_segment_cipher.h"

namespace lc {
    uint64 SerialSegmentEncipher::run(byte* in, byte* out, uint64 length) {
        int H = N - fill, F = N;
        uint64 round = (length / H) >> 2;
        uint64 remainder = (length / H) & 3;
        for (uint64 i = 0; i < round; i++) {
            memcpy(out, in, H);
            padding->padding(out + H, fill);
            algorithm->run(out, handler->update());
            in += H;
            out += F;
            memcpy(out, in, H);
            padding->padding(out + H, fill);
            algorithm->run(out, handler->update());
            in += H;
            out += F;
            memcpy(out, in, H);
            padding->padding(out + H, fill);
            algorithm->run(out, handler->update());
            in += H;
            out += F;
            memcpy(out, in, H);
            padding->padding(out + H, fill);
            algorithm->run(out, handler->update());
            in += H;
            out += F;
        }
        for (uint64 i = 0; i < remainder; i++) {
            memcpy(out, in, H);
            padding->padding(out + H, fill);
            algorithm->run(out, handler->update());
            in += H;
            out += F;
        }
        uint64 lost = length % H;
        if (lost > 0) {
            memcpy(out, in, lost);
            padding->padding(out + lost, F - lost);
            algorithm->run(out, handler->update());
        }
        return (uint64) std::ceil(1.0 * length / H) * F;
    }

    uint64 SerialSegmentEncipher::run(byte* in, uint64 length) {
        uint64 round = (length >> L) >> 3;
        uint64 remainder = (length >> L) & 7;
        for (uint64 i = 0; i < round; i++) {
            algorithm->run(in, handler->update());
            in += N;
            algorithm->run(in, handler->update());
            in += N;
            algorithm->run(in, handler->update());
            in += N;
            algorithm->run(in, handler->update());
            in += N;
            algorithm->run(in, handler->update());
            in += N;
            algorithm->run(in, handler->update());
            in += N;
            algorithm->run(in, handler->update());
            in += N;
            algorithm->run(in, handler->update());
            in += N;
        }
        for (uint64 i = 0; i < remainder; i++) {
            algorithm->run(in, handler->update());
            in += N;
        }
        return length;
    }

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SerialSegmentDecipher code
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    uint64 SerialSegmentDecipher::run(byte* in, byte* out, uint64 length) {
        int H = N - fill, F = N;
        uint64 round = (length / F) >> 2;
        uint64 remainder = (length / F) & 3;
        for (uint64 i = 0; i < round; i++) {
            algorithm->run(in, handler->update());
            memcpy(out, in, H);
            in += F;
            out += H;
            algorithm->run(in, handler->update());
            memcpy(out, in, H);
            in += F;
            out += H;
            algorithm->run(in, handler->update());
            memcpy(out, in, H);
            in += F;
            out += H;
            algorithm->run(in, handler->update());
            memcpy(out, in, H);
            in += F;
            out += H;
        }
        for (uint64 i = 0; i < remainder; i++) {
            algorithm->run(in, handler->update());
            memcpy(out, in, H);
            in += F;
            out += H;
        }
        return (uint64) std::ceil(1.0 * length / F) * H;
    }

    uint64 SerialSegmentDecipher::run(byte* in, uint64 length) {
        uint64 round = (length >> L) >> 3;
        uint64 remainder = (length >> L) & 7;
        for (uint64 i = 0; i < round; i++) {
            algorithm->run(in, handler->update());
            in += N;
            algorithm->run(in, handler->update());
            in += N;
            algorithm->run(in, handler->update());
            in += N;
            algorithm->run(in, handler->update());
            in += N;
            algorithm->run(in, handler->update());
            in += N;
            algorithm->run(in, handler->update());
            in += N;
            algorithm->run(in, handler->update());
            in += N;
            algorithm->run(in, handler->update());
            in += N;
        }
        for (uint64 i = 0; i < remainder; i++) {
            algorithm->run(in, handler->update());
            in += N;
        }
        return length;
    }
}

