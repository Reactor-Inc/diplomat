#include "diplomat_nanobind_common.hpp"


#include "Opaque.hpp"
#include "OptionalOpaqueField.hpp"

namespace somelib {
void add_OptionalOpaqueField_binding(nb::module_ mod) {
    nb::class_<somelib::OptionalOpaqueField> st(mod, "OptionalOpaqueField", "A struct whose opaque field may be unset.");
    st
        .def(nb::init<>())
        .def(nb::init<somelib::Opaque*, int32_t>(), "op"_a.none(),  "count"_a.none())
        .def_prop_rw("op",
            [](const somelib::OptionalOpaqueField& self) { return nullable<decltype(self.op)>{self.op}; },
            [](somelib::OptionalOpaqueField& self, somelib::Opaque* v) { self.op = v; },
            nb::for_setter(nb::arg("value").none())
        )
        .def_rw("count", &somelib::OptionalOpaqueField::count)
        .def("has_op", &somelib::OptionalOpaqueField::has_op);
}

} 