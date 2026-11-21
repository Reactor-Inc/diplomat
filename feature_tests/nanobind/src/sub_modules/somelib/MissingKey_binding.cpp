#include "diplomat_nanobind_common.hpp"


#include "MissingKey.hpp"

namespace somelib {
void add_MissingKey_binding(nb::module_ mod) {
    PyType_Slot somelib_MissingKey_slots[] = {
        {Py_tp_free, (void *)somelib::MissingKey::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<somelib::MissingKey> opaque(mod, "MissingKey", nb::type_slots(somelib_MissingKey_slots), "An error raised as `LookupError` in languages that raise exceptions.");
    opaque
        .def("__str__", &somelib::MissingKey::message);
}

} 