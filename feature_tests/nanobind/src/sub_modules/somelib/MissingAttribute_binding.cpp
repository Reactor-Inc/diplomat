#include "diplomat_nanobind_common.hpp"


#include "MissingAttribute.hpp"

namespace somelib {
void add_MissingAttribute_binding(nb::module_ mod) {
    PyType_Slot somelib_MissingAttribute_slots[] = {
        {Py_tp_free, (void *)somelib::MissingAttribute::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<somelib::MissingAttribute> opaque(mod, "MissingAttribute", nb::type_slots(somelib_MissingAttribute_slots), "An error raised as `AttributeError`, so a dynamic attribute lookup failing with it works with\nPython's `hasattr` and `getattr(obj, name, default)`.");
    opaque
        .def("__str__", &somelib::MissingAttribute::message);
}

} 