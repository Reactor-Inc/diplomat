#ifndef SOMELIB_MissingKey_D_HPP
#define SOMELIB_MissingKey_D_HPP

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
    struct MissingKey;
} // namespace capi
} // namespace

namespace somelib {
/**
 * An error raised as `LookupError` in languages that raise exceptions.
 */
class MissingKey {
public:

  inline std::string message() const;
  template<typename W>
  inline void message_write(W& writeable_output) const;

    inline const somelib::capi::MissingKey* AsFFI() const;
    inline somelib::capi::MissingKey* AsFFI();
    inline static const somelib::MissingKey* FromFFI(const somelib::capi::MissingKey* ptr);
    inline static somelib::MissingKey* FromFFI(somelib::capi::MissingKey* ptr);
    inline static void operator delete(void* ptr);
private:
    MissingKey() = delete;
    MissingKey(const somelib::MissingKey&) = delete;
    MissingKey(somelib::MissingKey&&) noexcept = delete;
    MissingKey operator=(const somelib::MissingKey&) = delete;
    MissingKey operator=(somelib::MissingKey&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // SOMELIB_MissingKey_D_HPP
