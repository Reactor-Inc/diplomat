#ifndef SOMELIB_ExceptionRaiser_HPP
#define SOMELIB_ExceptionRaiser_HPP

#include "ExceptionRaiser.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "MissingAttribute.hpp"
#include "MissingKey.hpp"
#include "OutOfRange.hpp"
#include "diplomat_runtime.hpp"


namespace somelib {
namespace capi {
    extern "C" {

    typedef struct ExceptionRaiser_lookup_result {union {int32_t ok; somelib::capi::MissingKey* err;}; bool is_ok;} ExceptionRaiser_lookup_result;
    ExceptionRaiser_lookup_result ExceptionRaiser_lookup(somelib::diplomat::capi::DiplomatStringView key);

    typedef struct ExceptionRaiser_check_range_result {union {int32_t ok; somelib::capi::OutOfRange err;}; bool is_ok;} ExceptionRaiser_check_range_result;
    ExceptionRaiser_check_range_result ExceptionRaiser_check_range(int32_t value);

    somelib::capi::ExceptionRaiser* ExceptionRaiser_new(void);

    typedef struct ExceptionRaiser_get_attribute_result {union {int32_t ok; somelib::capi::MissingAttribute* err;}; bool is_ok;} ExceptionRaiser_get_attribute_result;
    ExceptionRaiser_get_attribute_result ExceptionRaiser_get_attribute(const somelib::capi::ExceptionRaiser* self, somelib::diplomat::capi::DiplomatStringView name);

    void ExceptionRaiser_destroy(ExceptionRaiser* self);

    } // extern "C"
} // namespace capi
} // namespace

inline somelib::diplomat::result<int32_t, std::unique_ptr<somelib::MissingKey>> somelib::ExceptionRaiser::lookup(std::string_view key) {
    auto result = somelib::capi::ExceptionRaiser_lookup({key.data(), key.size()});
    return result.is_ok ? somelib::diplomat::result<int32_t, std::unique_ptr<somelib::MissingKey>>(somelib::diplomat::Ok<int32_t>(result.ok)) : somelib::diplomat::result<int32_t, std::unique_ptr<somelib::MissingKey>>(somelib::diplomat::Err<std::unique_ptr<somelib::MissingKey>>(std::unique_ptr<somelib::MissingKey>(somelib::MissingKey::FromFFI(result.err))));
}

inline somelib::diplomat::result<int32_t, somelib::OutOfRange> somelib::ExceptionRaiser::check_range(int32_t value) {
    auto result = somelib::capi::ExceptionRaiser_check_range(value);
    return result.is_ok ? somelib::diplomat::result<int32_t, somelib::OutOfRange>(somelib::diplomat::Ok<int32_t>(result.ok)) : somelib::diplomat::result<int32_t, somelib::OutOfRange>(somelib::diplomat::Err<somelib::OutOfRange>(somelib::OutOfRange::FromFFI(result.err)));
}

inline std::unique_ptr<somelib::ExceptionRaiser> somelib::ExceptionRaiser::new_() {
    auto result = somelib::capi::ExceptionRaiser_new();
    return std::unique_ptr<somelib::ExceptionRaiser>(somelib::ExceptionRaiser::FromFFI(result));
}

inline somelib::diplomat::result<int32_t, std::unique_ptr<somelib::MissingAttribute>> somelib::ExceptionRaiser::__getattr__(std::string_view name) const {
    auto result = somelib::capi::ExceptionRaiser_get_attribute(this->AsFFI(),
        {name.data(), name.size()});
    return result.is_ok ? somelib::diplomat::result<int32_t, std::unique_ptr<somelib::MissingAttribute>>(somelib::diplomat::Ok<int32_t>(result.ok)) : somelib::diplomat::result<int32_t, std::unique_ptr<somelib::MissingAttribute>>(somelib::diplomat::Err<std::unique_ptr<somelib::MissingAttribute>>(std::unique_ptr<somelib::MissingAttribute>(somelib::MissingAttribute::FromFFI(result.err))));
}

inline const somelib::capi::ExceptionRaiser* somelib::ExceptionRaiser::AsFFI() const {
    return reinterpret_cast<const somelib::capi::ExceptionRaiser*>(this);
}

inline somelib::capi::ExceptionRaiser* somelib::ExceptionRaiser::AsFFI() {
    return reinterpret_cast<somelib::capi::ExceptionRaiser*>(this);
}

inline const somelib::ExceptionRaiser* somelib::ExceptionRaiser::FromFFI(const somelib::capi::ExceptionRaiser* ptr) {
    return reinterpret_cast<const somelib::ExceptionRaiser*>(ptr);
}

inline somelib::ExceptionRaiser* somelib::ExceptionRaiser::FromFFI(somelib::capi::ExceptionRaiser* ptr) {
    return reinterpret_cast<somelib::ExceptionRaiser*>(ptr);
}

inline void somelib::ExceptionRaiser::operator delete(void* ptr) {
    somelib::capi::ExceptionRaiser_destroy(reinterpret_cast<somelib::capi::ExceptionRaiser*>(ptr));
}


#endif // SOMELIB_ExceptionRaiser_HPP
