#include "diplomat_nanobind_common.hpp"


#include "OutOfRange.hpp"

namespace somelib {
void add_OutOfRange_binding(nb::module_ mod) {
    nb::class_<somelib::OutOfRange> e_class(mod, "OutOfRange", "An enum error raised as `ValueError`.");
    
        nb::enum_<somelib::OutOfRange::Value> enumerator(e_class, "OutOfRange");
        enumerator
            .value("TooSmall", somelib::OutOfRange::TooSmall)
            .value("TooLarge", somelib::OutOfRange::TooLarge)
            .export_values();
    
        e_class
            .def(nb::init_implicit<somelib::OutOfRange::Value>())
            .def(nb::self == somelib::OutOfRange::Value())
            .def("__repr__", [](const somelib::OutOfRange& self){
                return nb::str(nb::cast(somelib::OutOfRange::Value(self)));
            });
}

} 