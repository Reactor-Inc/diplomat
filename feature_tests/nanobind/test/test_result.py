import somelib
import unittest

class TestResult(unittest.TestCase):
    
    def test_result(self):
        r2 = somelib.ResultOpaque(5)
        r2.assert_integer(5)

        with self.assertRaises(Exception) as cm:
            somelib.ResultOpaque.new_failing_foo()

        assert cm.exception.args[0] == somelib.ErrorEnum.Foo, "foo error"

        with self.assertRaises(Exception) as cm:
            somelib.ResultOpaque.new_failing_bar()
        assert cm.exception.args[0] == somelib.ErrorEnum.Bar, "bar error"

        with self.assertRaises(Exception) as cm:
            somelib.ResultOpaque.new_failing_unit()
        assert cm.exception, "unit error"

        with self.assertRaises(Exception) as cm:
            somelib.ResultOpaque.new_failing_struct(109)
        # Exceptions are universally converted to strings, so we cannot access fields.
        # If present, stringifiers are used
        assert cm.exception.args[0].j == 12, "struct error"
        assert cm.exception.args[0].i == 109, "struct error"

        integer = somelib.ResultOpaque.new_int(109)
        assert integer == 109, "int ok"

        with self.assertRaises(Exception) as cm:
            somelib.ResultOpaque.new_in_err(198)
        # No methods allowed, exceptions are only strings
        #cm.exception.assert_integer(198)
        cm.exception.args[0].assert_integer(198)

        a = somelib.ResultOpaque(102)
        b = a.takes_str("Hello there")
        a.assert_integer(102)
        b.assert_integer(102)

        with self.assertRaises(Exception) as cm:
            a = somelib.ResultOpaque(0)
            a.give_self()
        a.assert_integer(0)

    def test_stringifier_loop(self):
        a = somelib.ResultOpaque(0)
        with self.assertRaises(Exception) as cm:
            str(a)
        
        cm.exception.args[0].assert_integer(0)
        
        with self.assertRaises(Exception) as cm2:
            str(cm.exception)
        cm2.exception.args[0].assert_integer(0)
    
    def test_result_op_ctor(self):
        with self.assertRaises(Exception) as cm:
            somelib.FallibleOpaqueConstructor()
        cm.exception.args[0].assert_integer(10)

    def test_result_type_signatures(self):
        """The diplomat::result<T, E> type_caster unwraps to T on success and raises on error,
        so the Python-visible return type should be T, not the bare word 'result'.

        nanobind's __doc__ contains the signature (e.g. "new_int(i: int) -> int").
        The .pyi stub should show:
            def new_int(i: int) -> int: ...
            def new_failing_foo() -> ResultOpaque: ...
        NOT:
            def new_int(i: int) -> result: ...
        """
        def get_return_type(method):
            """Extract the return type string from a nanobind method's __doc__ signature."""
            for line in method.__doc__.splitlines():
                if "->" in line:
                    return line.split("->")[-1].strip()
            return None

        assert get_return_type(somelib.ResultOpaque.new_int) == "int"
        assert get_return_type(somelib.ResultOpaque.new_failing_foo).endswith("ResultOpaque")


class TestExceptions(unittest.TestCase):
    """Error types naming an `exception` are raised as that Python class, with the error as its argument."""

    def test_opaque_error_raises_named_class(self):
        assert somelib.ExceptionRaiser.lookup("one") == 1
        with self.assertRaises(LookupError) as cm:
            somelib.ExceptionRaiser.lookup("two")
        assert str(cm.exception) == 'no key "two"'

    def test_enum_error_raises_named_class(self):
        assert somelib.ExceptionRaiser.check_range(50) == 50
        with self.assertRaises(ValueError) as cm:
            somelib.ExceptionRaiser.check_range(101)
        assert cm.exception.args[0] == somelib.OutOfRange.TooLarge

    def test_unnamed_error_raises_exception(self):
        with self.assertRaises(Exception) as cm:
            somelib.ResultOpaque.new_failing_foo()
        assert type(cm.exception) is Exception

    def test_attribute_error_from_getattr(self):
        raiser = somelib.ExceptionRaiser()
        assert raiser.answer == 42
        assert hasattr(raiser, "answer")
        assert not hasattr(raiser, "question")
        assert getattr(raiser, "question", None) is None
        with self.assertRaises(AttributeError) as cm:
            raiser.question
        assert str(cm.exception) == 'no attribute "question"'


class TestFallibleIterator(unittest.TestCase):
    def test_iterates_until_exhausted(self):
        items = list(somelib.FallibleIterable(3, 3))
        assert len(items) == 3
        for i, item in enumerate(items):
            item.assert_integer(i)

    def test_error_raises_instead_of_ending(self):
        iterator = iter(somelib.FallibleIterable(5, 2))
        next(iterator).assert_integer(0)
        next(iterator).assert_integer(1)
        with self.assertRaises(Exception) as cm:
            next(iterator)
        assert cm.exception.args[0] == somelib.ErrorEnum.Bar

    def test_error_propagates_out_of_for_loop(self):
        seen = []
        with self.assertRaises(Exception):
            for item in somelib.FallibleIterable(5, 2):
                seen.append(item)
        assert len(seen) == 2

    def test_next_signature_is_the_item(self):
        assert somelib.FallibleIterator.__next__.__doc__.splitlines()[0].endswith(".ResultOpaque")
