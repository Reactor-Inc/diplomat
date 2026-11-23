#include "diplomat_nanobind_common.hpp"


#include "FallibleIterable.hpp"

namespace somelib {
void add_FallibleIterable_binding(nb::module_ mod) {
    PyType_Slot somelib_FallibleIterable_slots[] = {
        {Py_tp_free, (void *)somelib::FallibleIterable::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<somelib::FallibleIterable> opaque(mod, "FallibleIterable", nb::type_slots(somelib_FallibleIterable_slots));
    opaque
        .def(nb::new_(std::move(maybe_op_unwrap(&somelib::FallibleIterable::new_))), "len"_a, "fail_at"_a, "`fail_at` at or past `len` never fails.")
        .def("__iter__", std::move(maybe_op_unwrap(&somelib::FallibleIterable::iter)));
}

} 