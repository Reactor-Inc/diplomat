#include "diplomat_nanobind_common.hpp"


#include "ExceptionRaiser.hpp"

namespace somelib {
void add_ExceptionRaiser_binding(nb::module_ mod) {
    PyType_Slot somelib_ExceptionRaiser_slots[] = {
        {Py_tp_free, (void *)somelib::ExceptionRaiser::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<somelib::ExceptionRaiser> opaque(mod, "ExceptionRaiser", nb::type_slots(somelib_ExceptionRaiser_slots));
    opaque
        .def("__getattr__", std::move(maybe_op_unwrap(&somelib::ExceptionRaiser::__getattr__)), "name"_a, "Resolves the attributes Python does not find on the object itself; only `answer` exists.")
        .def(nb::new_(std::move(maybe_op_unwrap(&somelib::ExceptionRaiser::new_))))
        .def_static("check_range", &somelib::ExceptionRaiser::check_range, "value"_a)
        .def_static("lookup", std::move(maybe_op_unwrap(&somelib::ExceptionRaiser::lookup)), "key"_a);
}

} 