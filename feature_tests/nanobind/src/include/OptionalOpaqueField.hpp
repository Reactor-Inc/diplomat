#ifndef SOMELIB_OptionalOpaqueField_HPP
#define SOMELIB_OptionalOpaqueField_HPP

#include "OptionalOpaqueField.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "Opaque.hpp"
#include "diplomat_runtime.hpp"


namespace somelib {
namespace capi {
    extern "C" {

    bool OptionalOpaqueField_has_op(somelib::capi::OptionalOpaqueField self);

    } // extern "C"
} // namespace capi
} // namespace

inline bool somelib::OptionalOpaqueField::has_op() const {
    auto result = somelib::capi::OptionalOpaqueField_has_op(this->AsFFI());
    return result;
}


inline somelib::capi::OptionalOpaqueField somelib::OptionalOpaqueField::AsFFI() const {
    return somelib::capi::OptionalOpaqueField {
        /* .op = */ op ? op->AsFFI() : nullptr,
        /* .count = */ count,
    };
}

inline somelib::OptionalOpaqueField somelib::OptionalOpaqueField::FromFFI(somelib::capi::OptionalOpaqueField c_struct) {
    return somelib::OptionalOpaqueField {
        /* .op = */ (somelib::Opaque*)somelib::Opaque::FromFFI(c_struct.op),
        /* .count = */ c_struct.count,
    };
}


#endif // SOMELIB_OptionalOpaqueField_HPP
