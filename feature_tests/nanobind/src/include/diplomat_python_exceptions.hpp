#pragma once

#include <memory>
#include <nanobind/nanobind.h>

#include "MissingAttribute.d.hpp"
#include "MissingKey.d.hpp"
#include "OutOfRange.d.hpp"

namespace somelib {

// The Python exception class an error is raised as: `Exception`, unless the error type names
// another with `#[diplomat::attr(nanobind, exception = "...")]`.
template<typename E>
struct python_exception {
    static PyObject* type() { return PyExc_Exception; }
};

// Opaque errors are returned boxed.
template<typename E>
struct python_exception<std::unique_ptr<E>> : python_exception<E> {};

template<>
struct python_exception<::somelib::MissingAttribute> {
    static PyObject* type() { return PyExc_AttributeError; }
};

template<>
struct python_exception<::somelib::MissingKey> {
    static PyObject* type() { return PyExc_LookupError; }
};

template<>
struct python_exception<::somelib::OutOfRange> {
    static PyObject* type() { return PyExc_ValueError; }
};

}