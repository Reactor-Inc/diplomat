#include "diplomat_nanobind_common.hpp"


#include "FallibleIterator.hpp"

namespace somelib {
void add_FallibleIterator_binding(nb::module_ mod) {
    PyType_Slot somelib_FallibleIterator_slots[] = {
        {Py_tp_free, (void *)somelib::FallibleIterator::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<somelib::FallibleIterator> opaque(mod, "FallibleIterator", nb::type_slots(somelib_FallibleIterator_slots), "Yields `ResultOpaque(0)`, `ResultOpaque(1)`, ... up to `len` items, failing at `fail_at` if it is reached.");
    opaque
        .def("__next__", [](somelib::FallibleIterator& self){
                auto next = map_inner(self.next());
                return iterator_next<decltype(next)>::get(std::move(next));
            })
            .def("__iter__", [](nb::handle self) { return self; });
}

} 