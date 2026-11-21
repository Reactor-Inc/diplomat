#ifndef SOMELIB_MissingAttribute_HPP
#define SOMELIB_MissingAttribute_HPP

#include "MissingAttribute.d.hpp"

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

    void MissingAttribute_message(const somelib::capi::MissingAttribute* self, somelib::diplomat::capi::DiplomatWrite* write);

    void MissingAttribute_destroy(MissingAttribute* self);

    } // extern "C"
} // namespace capi
} // namespace

inline std::string somelib::MissingAttribute::message() const {
    std::string output;
    somelib::diplomat::capi::DiplomatWrite write = somelib::diplomat::WriteFromString(output);
    somelib::capi::MissingAttribute_message(this->AsFFI(),
        &write);
    return output;
}
template<typename W>
inline void somelib::MissingAttribute::message_write(W& writeable) const {
    somelib::diplomat::capi::DiplomatWrite write = somelib::diplomat::WriteTrait<W>::Construct(writeable);
    somelib::capi::MissingAttribute_message(this->AsFFI(),
        &write);
}

inline const somelib::capi::MissingAttribute* somelib::MissingAttribute::AsFFI() const {
    return reinterpret_cast<const somelib::capi::MissingAttribute*>(this);
}

inline somelib::capi::MissingAttribute* somelib::MissingAttribute::AsFFI() {
    return reinterpret_cast<somelib::capi::MissingAttribute*>(this);
}

inline const somelib::MissingAttribute* somelib::MissingAttribute::FromFFI(const somelib::capi::MissingAttribute* ptr) {
    return reinterpret_cast<const somelib::MissingAttribute*>(ptr);
}

inline somelib::MissingAttribute* somelib::MissingAttribute::FromFFI(somelib::capi::MissingAttribute* ptr) {
    return reinterpret_cast<somelib::MissingAttribute*>(ptr);
}

inline void somelib::MissingAttribute::operator delete(void* ptr) {
    somelib::capi::MissingAttribute_destroy(reinterpret_cast<somelib::capi::MissingAttribute*>(ptr));
}


#endif // SOMELIB_MissingAttribute_HPP
