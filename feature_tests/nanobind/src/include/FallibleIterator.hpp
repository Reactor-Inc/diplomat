#ifndef SOMELIB_FallibleIterator_HPP
#define SOMELIB_FallibleIterator_HPP

#include "FallibleIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "ErrorEnum.hpp"
#include "ResultOpaque.hpp"
#include "diplomat_runtime.hpp"


namespace somelib {
namespace capi {
    extern "C" {

    typedef struct FallibleIterator_next_result {union {somelib::capi::ResultOpaque* ok; somelib::capi::ErrorEnum err;}; bool is_ok;} FallibleIterator_next_result;
    FallibleIterator_next_result FallibleIterator_next(somelib::capi::FallibleIterator* self);

    void FallibleIterator_destroy(FallibleIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline somelib::diplomat::result<somelib::diplomat::maybe_null<std::unique_ptr<somelib::ResultOpaque>>, somelib::ErrorEnum> somelib::FallibleIterator::next() {
    auto result = somelib::capi::FallibleIterator_next(this->AsFFI());
    return result.is_ok ? somelib::diplomat::result<somelib::diplomat::maybe_null<std::unique_ptr<somelib::ResultOpaque>>, somelib::ErrorEnum>(somelib::diplomat::Ok<somelib::diplomat::maybe_null<std::unique_ptr<somelib::ResultOpaque>>>(std::unique_ptr<somelib::ResultOpaque>(somelib::ResultOpaque::FromFFI(result.ok)))) : somelib::diplomat::result<somelib::diplomat::maybe_null<std::unique_ptr<somelib::ResultOpaque>>, somelib::ErrorEnum>(somelib::diplomat::Err<somelib::ErrorEnum>(somelib::ErrorEnum::FromFFI(result.err)));
}

inline const somelib::capi::FallibleIterator* somelib::FallibleIterator::AsFFI() const {
    return reinterpret_cast<const somelib::capi::FallibleIterator*>(this);
}

inline somelib::capi::FallibleIterator* somelib::FallibleIterator::AsFFI() {
    return reinterpret_cast<somelib::capi::FallibleIterator*>(this);
}

inline const somelib::FallibleIterator* somelib::FallibleIterator::FromFFI(const somelib::capi::FallibleIterator* ptr) {
    return reinterpret_cast<const somelib::FallibleIterator*>(ptr);
}

inline somelib::FallibleIterator* somelib::FallibleIterator::FromFFI(somelib::capi::FallibleIterator* ptr) {
    return reinterpret_cast<somelib::FallibleIterator*>(ptr);
}

inline void somelib::FallibleIterator::operator delete(void* ptr) {
    somelib::capi::FallibleIterator_destroy(reinterpret_cast<somelib::capi::FallibleIterator*>(ptr));
}


#endif // SOMELIB_FallibleIterator_HPP
