#ifndef SOMELIB_MissingAttribute_D_HPP
#define SOMELIB_MissingAttribute_D_HPP

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
    struct MissingAttribute;
} // namespace capi
} // namespace

namespace somelib {
/**
 * An error raised as `AttributeError`, so a dynamic attribute lookup failing with it works with
 * Python's `hasattr` and `getattr(obj, name, default)`.
 */
class MissingAttribute {
public:

  inline std::string message() const;
  template<typename W>
  inline void message_write(W& writeable_output) const;

    inline const somelib::capi::MissingAttribute* AsFFI() const;
    inline somelib::capi::MissingAttribute* AsFFI();
    inline static const somelib::MissingAttribute* FromFFI(const somelib::capi::MissingAttribute* ptr);
    inline static somelib::MissingAttribute* FromFFI(somelib::capi::MissingAttribute* ptr);
    inline static void operator delete(void* ptr);
private:
    MissingAttribute() = delete;
    MissingAttribute(const somelib::MissingAttribute&) = delete;
    MissingAttribute(somelib::MissingAttribute&&) noexcept = delete;
    MissingAttribute operator=(const somelib::MissingAttribute&) = delete;
    MissingAttribute operator=(somelib::MissingAttribute&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // SOMELIB_MissingAttribute_D_HPP
