#ifndef SOMELIB_OptionalOpaqueField_D_HPP
#define SOMELIB_OptionalOpaqueField_D_HPP

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
namespace capi { struct Opaque; }
class Opaque;
} // namespace somelib



namespace somelib {
namespace capi {
    struct OptionalOpaqueField {
      const somelib::capi::Opaque* op;
      int32_t count;
    };

    typedef struct OptionalOpaqueField_option {union { OptionalOpaqueField ok; }; bool is_ok; } OptionalOpaqueField_option;
} // namespace capi
} // namespace


namespace somelib {
/**
 * A struct whose opaque field may be unset.
 */
struct OptionalOpaqueField {
    somelib::Opaque* op;
    int32_t count;

  inline bool has_op() const;

    inline somelib::capi::OptionalOpaqueField AsFFI() const;
    inline static somelib::OptionalOpaqueField FromFFI(somelib::capi::OptionalOpaqueField c_struct);
};

} // namespace
#endif // SOMELIB_OptionalOpaqueField_D_HPP
