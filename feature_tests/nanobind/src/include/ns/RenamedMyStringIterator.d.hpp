#ifndef SOMELIB_ns_RenamedMyStringIterator_D_HPP
#define SOMELIB_ns_RenamedMyStringIterator_D_HPP

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"


namespace somelib::ns {
namespace capi {
    struct RenamedMyStringIterator;
} // namespace capi
} // namespace

namespace somelib::ns {
/**
 * Yields strings borrowed from a `MyIndexer`.
 */
class RenamedMyStringIterator {
public:

  inline std::optional<std::string_view> next() DIPLOMAT_LIFETIME_BOUND;

    inline const somelib::ns::capi::RenamedMyStringIterator* AsFFI() const;
    inline somelib::ns::capi::RenamedMyStringIterator* AsFFI();
    inline static const somelib::ns::RenamedMyStringIterator* FromFFI(const somelib::ns::capi::RenamedMyStringIterator* ptr);
    inline static somelib::ns::RenamedMyStringIterator* FromFFI(somelib::ns::capi::RenamedMyStringIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    RenamedMyStringIterator() = delete;
    RenamedMyStringIterator(const somelib::ns::RenamedMyStringIterator&) = delete;
    RenamedMyStringIterator(somelib::ns::RenamedMyStringIterator&&) noexcept = delete;
    RenamedMyStringIterator operator=(const somelib::ns::RenamedMyStringIterator&) = delete;
    RenamedMyStringIterator operator=(somelib::ns::RenamedMyStringIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // SOMELIB_ns_RenamedMyStringIterator_D_HPP
