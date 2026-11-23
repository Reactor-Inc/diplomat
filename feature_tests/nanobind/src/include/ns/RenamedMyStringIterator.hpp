#ifndef SOMELIB_ns_RenamedMyStringIterator_HPP
#define SOMELIB_ns_RenamedMyStringIterator_HPP

#include "RenamedMyStringIterator.d.hpp"

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
    extern "C" {

    typedef struct namespace_MyStringIterator_next_result {union {somelib::diplomat::capi::DiplomatStringView ok; }; bool is_ok;} namespace_MyStringIterator_next_result;
    namespace_MyStringIterator_next_result namespace_MyStringIterator_next(somelib::ns::capi::RenamedMyStringIterator* self);

    void namespace_MyStringIterator_destroy(RenamedMyStringIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline std::optional<std::string_view> somelib::ns::RenamedMyStringIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = somelib::ns::capi::namespace_MyStringIterator_next(this->AsFFI());
    return result.is_ok ? std::optional<std::string_view>(std::string_view(result.ok.data, result.ok.len)) : std::nullopt;
}

inline const somelib::ns::capi::RenamedMyStringIterator* somelib::ns::RenamedMyStringIterator::AsFFI() const {
    return reinterpret_cast<const somelib::ns::capi::RenamedMyStringIterator*>(this);
}

inline somelib::ns::capi::RenamedMyStringIterator* somelib::ns::RenamedMyStringIterator::AsFFI() {
    return reinterpret_cast<somelib::ns::capi::RenamedMyStringIterator*>(this);
}

inline const somelib::ns::RenamedMyStringIterator* somelib::ns::RenamedMyStringIterator::FromFFI(const somelib::ns::capi::RenamedMyStringIterator* ptr) {
    return reinterpret_cast<const somelib::ns::RenamedMyStringIterator*>(ptr);
}

inline somelib::ns::RenamedMyStringIterator* somelib::ns::RenamedMyStringIterator::FromFFI(somelib::ns::capi::RenamedMyStringIterator* ptr) {
    return reinterpret_cast<somelib::ns::RenamedMyStringIterator*>(ptr);
}

inline void somelib::ns::RenamedMyStringIterator::operator delete(void* ptr) {
    somelib::ns::capi::namespace_MyStringIterator_destroy(reinterpret_cast<somelib::ns::capi::RenamedMyStringIterator*>(ptr));
}


#endif // SOMELIB_ns_RenamedMyStringIterator_HPP
