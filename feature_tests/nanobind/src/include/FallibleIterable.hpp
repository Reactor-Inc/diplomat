#ifndef SOMELIB_FallibleIterable_HPP
#define SOMELIB_FallibleIterable_HPP

#include "FallibleIterable.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "FallibleIterator.hpp"
#include "diplomat_runtime.hpp"


namespace somelib {
namespace capi {
    extern "C" {

    somelib::capi::FallibleIterable* FallibleIterable_new(int32_t len, int32_t fail_at);

    somelib::capi::FallibleIterator* FallibleIterable_iter(const somelib::capi::FallibleIterable* self);

    void FallibleIterable_destroy(FallibleIterable* self);

    } // extern "C"
} // namespace capi
} // namespace

inline std::unique_ptr<somelib::FallibleIterable> somelib::FallibleIterable::new_(int32_t len, int32_t fail_at) {
    auto result = somelib::capi::FallibleIterable_new(len,
        fail_at);
    return std::unique_ptr<somelib::FallibleIterable>(somelib::FallibleIterable::FromFFI(result));
}

inline std::unique_ptr<somelib::FallibleIterator> somelib::FallibleIterable::iter() const {
    auto result = somelib::capi::FallibleIterable_iter(this->AsFFI());
    return std::unique_ptr<somelib::FallibleIterator>(somelib::FallibleIterator::FromFFI(result));
}

inline const somelib::capi::FallibleIterable* somelib::FallibleIterable::AsFFI() const {
    return reinterpret_cast<const somelib::capi::FallibleIterable*>(this);
}

inline somelib::capi::FallibleIterable* somelib::FallibleIterable::AsFFI() {
    return reinterpret_cast<somelib::capi::FallibleIterable*>(this);
}

inline const somelib::FallibleIterable* somelib::FallibleIterable::FromFFI(const somelib::capi::FallibleIterable* ptr) {
    return reinterpret_cast<const somelib::FallibleIterable*>(ptr);
}

inline somelib::FallibleIterable* somelib::FallibleIterable::FromFFI(somelib::capi::FallibleIterable* ptr) {
    return reinterpret_cast<somelib::FallibleIterable*>(ptr);
}

inline void somelib::FallibleIterable::operator delete(void* ptr) {
    somelib::capi::FallibleIterable_destroy(reinterpret_cast<somelib::capi::FallibleIterable*>(ptr));
}


#endif // SOMELIB_FallibleIterable_HPP
