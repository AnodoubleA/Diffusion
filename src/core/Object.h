//
// Created by Alice on 2017.02.24.
//
#pragma once
#ifndef DIFFUSION_OBJECT_H
#define DIFFUSION_OBJECT_H

#include <stdexcept>
#include <cstdio>
#include <typeinfo>
#include "types.h"
#include "DiffusionException.h"

namespace lc{

    class Object {
        uint64 ID;
    public:
        Object() {
            this->ID = ((uint64) this);
        }

        virtual int hashCode() {
            return (int) identity();
        }

        inline virtual uint64 identity() final {
            return ID;
        }

        virtual const char* getClassName() final {
            return typeid(this).name();
        }

        virtual bool equals(Object& other) {

            return this->hashCode() == other.hashCode();
        }

        virtual const char* toString() {
            return typeid(this).name();
        }

        friend bool operator==(Object& _this, Object& that) {
            return _this.identity() == that.identity();
        }

    protected:
        virtual Object clone() throw(DiffusionException) {

        }
    };

}

#endif //DIFFUSION_OBJECT_H
