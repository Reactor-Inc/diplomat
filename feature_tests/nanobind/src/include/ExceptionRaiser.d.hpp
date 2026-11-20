#ifndef SOMELIB_ExceptionRaiser_D_HPP
#define SOMELIB_ExceptionRaiser_D_HPP

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
namespace capi { struct ExceptionRaiser; }
class ExceptionRaiser;
namespace capi { struct MissingAttribute; }
class MissingAttribute;
namespace capi { struct MissingKey; }
class MissingKey;
class OutOfRange;
} // namespace somelib



namespace somelib {
namespace capi {
    struct ExceptionRaiser;
} // namespace capi
} // namespace

namespace somelib {
class ExceptionRaiser {
public:

  inline static somelib::diplomat::result<int32_t, std::unique_ptr<somelib::MissingKey>> lookup(std::string_view key);

  inline static somelib::diplomat::result<int32_t, somelib::OutOfRange> check_range(int32_t value);

  inline static std::unique_ptr<somelib::ExceptionRaiser> new_();

  /**
   * Resolves the attributes Python does not find on the object itself; only `answer` exists.
   */
  inline somelib::diplomat::result<int32_t, std::unique_ptr<somelib::MissingAttribute>> __getattr__(std::string_view name) const;

    inline const somelib::capi::ExceptionRaiser* AsFFI() const;
    inline somelib::capi::ExceptionRaiser* AsFFI();
    inline static const somelib::ExceptionRaiser* FromFFI(const somelib::capi::ExceptionRaiser* ptr);
    inline static somelib::ExceptionRaiser* FromFFI(somelib::capi::ExceptionRaiser* ptr);
    inline static void operator delete(void* ptr);
private:
    ExceptionRaiser() = delete;
    ExceptionRaiser(const somelib::ExceptionRaiser&) = delete;
    ExceptionRaiser(somelib::ExceptionRaiser&&) noexcept = delete;
    ExceptionRaiser operator=(const somelib::ExceptionRaiser&) = delete;
    ExceptionRaiser operator=(somelib::ExceptionRaiser&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // SOMELIB_ExceptionRaiser_D_HPP
