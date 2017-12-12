//
// Created by Alice on 2017/12/10.
//
#include "SegmentFactory.h"
#include "../cmds/options.h"

using namespace lc;
std::vector<SegmentCipher*> vector;

static SegmentCipher* SegmentFactory::make(CipherInfo& info) {
    for (SegmentCipher* item:vector) {
        if (item->support(info.options) && item->lock()) {
            return item;
        }
    }
    SegmentCipher* instance;
    if (contains(info.options, Consts::ENCIPHER, Consts::MULTICORE)) {
        instance = new SerialSegmentEncipher();
        goto end;
    }
    if (contains(info.options, Consts::DECIPHER, Consts::MULTICORE)) {
        instance = new SerialSegmentDecipher();
        goto end;
    }
    if (contains(info.options, Consts::ENCIPHER | Consts::MULTICORE)) {
        instance = new ParallelSegmentEncipher();
        goto end;
    }
    if (contains(info.options, Consts::DECIPHER | Consts::MULTICORE)) {
        instance = new ParallelSegmentDecipher();
        goto end;
    }
    end:
    instance->lock();
    vector.push_back(instance);
    return instance;
}

void SegmentFactory::clear() {
    for (SegmentCipher* element:vector) {
        delete element;
    }
    vector.clear();
}

