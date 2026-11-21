#ifndef SOMELIB_FallibleIterator_D_HPP
#define SOMELIB_FallibleIterator_D_HPP

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
namespace capi { struct ResultOpaque; }
class ResultOpaque;
class ErrorEnum;
} // namespace somelib



namespace somelib {
namespace capi {
    struct FallibleIterator;
} // namespace capi
} // namespace

namespace somelib {
/**
 * Yields `ResultOpaque(0)`, `ResultOpaque(1)`, ... up to `len` items, failing at `fail_at` if it is reached.
 */
class FallibleIterator {
public:

  inline somelib::diplomat::result<somelib::diplomat::maybe_null<std::unique_ptr<somelib::ResultOpaque>>, somelib::ErrorEnum> next();

    inline const somelib::capi::FallibleIterator* AsFFI() const;
    inline somelib::capi::FallibleIterator* AsFFI();
    inline static const somelib::FallibleIterator* FromFFI(const somelib::capi::FallibleIterator* ptr);
    inline static somelib::FallibleIterator* FromFFI(somelib::capi::FallibleIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    FallibleIterator() = delete;
    FallibleIterator(const somelib::FallibleIterator&) = delete;
    FallibleIterator(somelib::FallibleIterator&&) noexcept = delete;
    FallibleIterator operator=(const somelib::FallibleIterator&) = delete;
    FallibleIterator operator=(somelib::FallibleIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // SOMELIB_FallibleIterator_D_HPP
