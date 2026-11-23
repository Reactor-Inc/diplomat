#ifndef SOMELIB_OutOfRange_D_HPP
#define SOMELIB_OutOfRange_D_HPP

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
    enum OutOfRange {
      OutOfRange_TooSmall = 0,
      OutOfRange_TooLarge = 1,
    };

    typedef struct OutOfRange_option {union { OutOfRange ok; }; bool is_ok; } OutOfRange_option;
} // namespace capi
} // namespace

namespace somelib {
/**
 * An enum error raised as `ValueError`.
 */
class OutOfRange {
public:
    enum Value {
        TooSmall = 0,
        TooLarge = 1,
    };

    OutOfRange(): value(Value::TooSmall) {}

    // Implicit conversions between enum and ::Value
    constexpr OutOfRange(Value v) : value(v) {}
    constexpr operator Value() const { return value; }
    // Prevent usage as boolean value
    explicit operator bool() const = delete;

    inline somelib::capi::OutOfRange AsFFI() const;
    inline static somelib::OutOfRange FromFFI(somelib::capi::OutOfRange c_enum);
private:
    Value value;
};

} // namespace
#endif // SOMELIB_OutOfRange_D_HPP
