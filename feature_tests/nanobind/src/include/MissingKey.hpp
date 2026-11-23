#ifndef SOMELIB_MissingKey_HPP
#define SOMELIB_MissingKey_HPP

#include "MissingKey.d.hpp"

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
    extern "C" {

    void MissingKey_message(const somelib::capi::MissingKey* self, somelib::diplomat::capi::DiplomatWrite* write);

    void MissingKey_destroy(MissingKey* self);

    } // extern "C"
} // namespace capi
} // namespace

inline std::string somelib::MissingKey::message() const {
    std::string output;
    somelib::diplomat::capi::DiplomatWrite write = somelib::diplomat::WriteFromString(output);
    somelib::capi::MissingKey_message(this->AsFFI(),
        &write);
    return output;
}
template<typename W>
inline void somelib::MissingKey::message_write(W& writeable) const {
    somelib::diplomat::capi::DiplomatWrite write = somelib::diplomat::WriteTrait<W>::Construct(writeable);
    somelib::capi::MissingKey_message(this->AsFFI(),
        &write);
}

inline const somelib::capi::MissingKey* somelib::MissingKey::AsFFI() const {
    return reinterpret_cast<const somelib::capi::MissingKey*>(this);
}

inline somelib::capi::MissingKey* somelib::MissingKey::AsFFI() {
    return reinterpret_cast<somelib::capi::MissingKey*>(this);
}

inline const somelib::MissingKey* somelib::MissingKey::FromFFI(const somelib::capi::MissingKey* ptr) {
    return reinterpret_cast<const somelib::MissingKey*>(ptr);
}

inline somelib::MissingKey* somelib::MissingKey::FromFFI(somelib::capi::MissingKey* ptr) {
    return reinterpret_cast<somelib::MissingKey*>(ptr);
}

inline void somelib::MissingKey::operator delete(void* ptr) {
    somelib::capi::MissingKey_destroy(reinterpret_cast<somelib::capi::MissingKey*>(ptr));
}


#endif // SOMELIB_MissingKey_HPP
