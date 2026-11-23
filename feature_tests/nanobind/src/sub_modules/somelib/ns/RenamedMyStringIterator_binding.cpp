#include "diplomat_nanobind_common.hpp"


#include "ns/RenamedMyStringIterator.hpp"

namespace somelib::ns {
void add_RenamedMyStringIterator_binding(nb::module_ mod) {
    PyType_Slot somelib_ns_RenamedMyStringIterator_slots[] = {
        {Py_tp_free, (void *)somelib::ns::RenamedMyStringIterator::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<somelib::ns::RenamedMyStringIterator> opaque(mod, "RenamedMyStringIterator", nb::type_slots(somelib_ns_RenamedMyStringIterator_slots), "Yields strings borrowed from a `MyIndexer`.");
    opaque
        .def("__next__", [](somelib::ns::RenamedMyStringIterator& self){
                auto next = self.next();
                return iterator_next<decltype(next)>::get(std::move(next));
            })
            .def("__iter__", [](nb::handle self) { return self; });
}

} 