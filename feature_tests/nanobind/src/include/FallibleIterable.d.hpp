#ifndef SOMELIB_FallibleIterable_D_HPP
#define SOMELIB_FallibleIterable_D_HPP

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
namespace capi { struct FallibleIterable; }
class FallibleIterable;
namespace capi { struct FallibleIterator; }
class FallibleIterator;
} // namespace somelib



namespace somelib {
namespace capi {
    struct FallibleIterable;
} // namespace capi
} // namespace

namespace somelib {
class FallibleIterable {
public:

  /**
   * `fail_at` at or past `len` never fails.
   */
  inline static std::unique_ptr<somelib::FallibleIterable> new_(int32_t len, int32_t fail_at);

  inline std::unique_ptr<somelib::FallibleIterator> iter() const;

    inline const somelib::capi::FallibleIterable* AsFFI() const;
    inline somelib::capi::FallibleIterable* AsFFI();
    inline static const somelib::FallibleIterable* FromFFI(const somelib::capi::FallibleIterable* ptr);
    inline static somelib::FallibleIterable* FromFFI(somelib::capi::FallibleIterable* ptr);
    inline static void operator delete(void* ptr);
private:
    FallibleIterable() = delete;
    FallibleIterable(const somelib::FallibleIterable&) = delete;
    FallibleIterable(somelib::FallibleIterable&&) noexcept = delete;
    FallibleIterable operator=(const somelib::FallibleIterable&) = delete;
    FallibleIterable operator=(somelib::FallibleIterable&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // SOMELIB_FallibleIterable_D_HPP
