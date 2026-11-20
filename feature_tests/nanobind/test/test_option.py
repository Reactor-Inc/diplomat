import somelib
import pytest

def test_option():

    o = somelib.OptionOpaque.new(1415)
    o.assert_integer(1415)

    o = somelib.OptionOpaque.new_none()
    assert not o, "new_none() returns None"

    s = somelib.OptionOpaque.new_struct()
    s.a.assert_integer(101)
    s.b.assert_char(U'餐')
    assert s.c == 904, "correct struct returned"
    s.d.assert_integer(926535)

    s = somelib.OptionOpaque.new_struct_nones()

    assert not s.a, "new_struct_nones() returns None"
    assert not s.b, "new_struct_nones() returns None"
    assert s.c == 908, "correct struct returned"

    opt_u8 = somelib.OptionOpaque.accepts_option_u8(None, sentinel=123)
    assert not opt_u8, "accepts_option_u8 is idempotent"
    opt_u8 = somelib.OptionOpaque.accepts_option_u8(5, sentinel=123)
    assert opt_u8 == 5, "accepts_option_u8 is idempotent"
    opt_enum = somelib.OptionOpaque.accepts_option_enum(None, sentinel=123)
    assert not opt_enum, "accepts_option_enum is idempotent"
    opt_enum = somelib.OptionOpaque.accepts_option_enum(somelib.OptionEnum.Foo, sentinel=123)
    assert opt_enum == somelib.OptionEnum.Foo, "accepts_option_enum is idempotent"
    opt_struct = somelib.OptionOpaque.accepts_option_input_struct(None, sentinel=123)
    assert not opt_struct, "accepts_option_input_struct is idempotent"
    opt_struct = somelib.OptionOpaque.accepts_option_input_struct(somelib.OptionInputStruct(1, None, somelib.OptionEnum.Foo), sentinel=123)
    assert opt_struct.a == 1, "accepts_option_input_struct is idempotent"
    assert not opt_struct.b, "accepts_option_input_struct is idempotent"
    assert opt_struct.c == somelib.OptionEnum.Foo, "accepts_option_input_struct is idempotent"

    opt_struct = somelib.OptionOpaque.returns_option_input_struct()
    assert opt_struct.a == 6, "returns_option_input_struct returns the right values"
    assert not opt_struct.b, "returns_option_input_struct returns the right values"
    assert opt_struct.c == somelib.OptionEnum.Bar, "returns_option_input_struct returns the right values"
    
    exists = somelib.OptionOpaque.option_opaque_argument(somelib.OptionOpaque.new(1415))
    assert exists, "option_opaque_argument did not return expected result"
    exists = somelib.OptionOpaque.option_opaque_argument()
    assert not exists, "option_opaque_argument did not return expected result with default argument"

    string_array = ["string1", "string2"]
    str_slice_result = somelib.OptionOpaque.accepts_option_str_slice(string_array, sentinel=123)
    assert str_slice_result, "option_str_slice functions"

    assert somelib.OptionOpaque.accepts_option_str("accepts optional string!", sentinel=123) == 24, "Optional string param (Some)"
    assert somelib.OptionOpaque.accepts_option_str(None, sentinel=123) == 0, "Optional string param (None)"

    int_array = [1, 2, 3, 4]
    assert somelib.OptionOpaque.accepts_option_primitive(int_array, sentinel=123) == 10, "Optional primitive param (Some)"
    assert somelib.OptionOpaque.accepts_option_primitive(None, sentinel=123) == -1, "Optional primitive param (None)"

def test_out_struct():
    with pytest.raises(TypeError):
        out = somelib.OptionStruct()
    # Check that our constructors and setters fail
    out = somelib.OptionOpaque.new_struct()
    with pytest.raises(AttributeError):
        out.c = 10
    assert out.c == 904
    with pytest.raises(AttributeError):
        out.d = somelib.OptionOpaque.new(14)

def _return_type(function):
    """The return annotation of a nanobind function's signature, as its stubs show it."""
    return function.__nb_signature__[0][0].split("->")[-1].strip()


def test_optional_opaque_returns_are_typed_optional():
    assert _return_type(somelib.OptionOpaque.new_none).endswith(".OptionOpaque | None")
    assert _return_type(somelib.OptionOpaque.returns_none_self).endswith(".OptionOpaque | None")
    # Inside a Result, only the success is optional; the error raises.
    assert _return_type(somelib.OptionOpaque.new_fallible).endswith(".OptionOpaque | None")
    # A non-optional opaque stays as is.
    assert _return_type(somelib.ResultOpaque.new_failing_foo).endswith("ResultOpaque")
    assert not _return_type(somelib.ResultOpaque.new_failing_foo).endswith("| None")


def test_optional_opaque_returns():
    assert somelib.OptionOpaque.new_fallible(0) is None
    somelib.OptionOpaque.new_fallible(7).assert_integer(7)
    with pytest.raises(Exception):
        somelib.OptionOpaque.new_fallible(-1)
    assert somelib.OptionOpaque.none_static is None
    o = somelib.OptionOpaque.new(3)
    assert o.returns_none_self() is None
    assert o.returns_some_self() is o
