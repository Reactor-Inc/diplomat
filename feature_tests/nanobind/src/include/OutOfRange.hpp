#ifndef SOMELIB_OutOfRange_HPP
#define SOMELIB_OutOfRange_HPP

#include "OutOfRange.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "diplomat_runtime.hpp"


namespace somelib {
namespace capi {

} // namespace capi
} // namespace

inline somelib::capi::OutOfRange somelib::OutOfRange::AsFFI() const {
    return static_cast<somelib::capi::OutOfRange>(value);
}

inline somelib::OutOfRange somelib::OutOfRange::FromFFI(somelib::capi::OutOfRange c_enum) {
    switch (c_enum) {
        case somelib::capi::OutOfRange_TooSmall:
        case somelib::capi::OutOfRange_TooLarge:
            return static_cast<somelib::OutOfRange::Value>(c_enum);
        default:
            std::abort();
    }
}
#endif // SOMELIB_OutOfRange_HPP
