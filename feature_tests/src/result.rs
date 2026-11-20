use super::*;

#[diplomat::bridge]
#[diplomat::include("src/attrs/cache_test.rs")]
pub mod ffi {
    super::cache_test_macro! {CachedIncludeZST}

    #[diplomat::opaque_mut]
    #[diplomat::attr(dotnet, manually_disposable)]
    #[diplomat::attr(auto, error)]
    pub struct ResultOpaque(i32);

    #[derive(PartialEq, Eq, Debug)]
    #[diplomat::attr(auto, error)]
    #[diplomat::attr(*, precondition_violation)]
    pub enum ErrorEnum {
        Foo,
        Bar,
    }

    #[derive(Debug)]
    #[diplomat::attr(auto, error)]
    pub struct ErrorStruct {
        i: i32,
        j: i32,
    }
    impl ErrorStruct {
        #[diplomat::attr(kotlin, disable)]
        #[diplomat::attr(dotnet, disable)]
        pub fn returns_result_option(is_some: bool) -> Result<DiplomatOption<ErrorStruct>, ()> {
            if is_some {
                Ok(Some(ErrorStruct { i: 0, j: 125 }).into())
            } else {
                Ok(None.into())
            }
        }
    }

    impl ResultOpaque {
        #[diplomat::attr(all(*, supports = fallible_constructors), constructor)]
        pub fn new(i: i32) -> Result<Box<ResultOpaque>, ErrorEnum> {
            Ok(Box::new(ResultOpaque(i)))
        }

        #[diplomat::attr(all(supports = named_constructors, supports = fallible_constructors), named_constructor = "failing_foo")]
        pub fn new_failing_foo() -> Result<Box<ResultOpaque>, ErrorEnum> {
            Err(ErrorEnum::Foo)
        }

        #[diplomat::attr(all(supports = named_constructors, supports = fallible_constructors), named_constructor = "failing_bar")]
        pub fn new_failing_bar() -> Result<Box<ResultOpaque>, ErrorEnum> {
            Err(ErrorEnum::Bar)
        }

        // TODO constructors: this should ideally be a constructor too
        #[diplomat::attr(dart, rename = "failing_unit")]
        pub fn new_failing_unit() -> Result<Box<ResultOpaque>, ()> {
            Err(())
        }

        #[diplomat::attr(all(supports = named_constructors, supports = fallible_constructors), named_constructor = "failing_struct")]
        pub fn new_failing_struct(i: i32) -> Result<Box<ResultOpaque>, ErrorStruct> {
            Err(ErrorStruct { i, j: 12 })
        }

        pub fn new_in_err(i: i32) -> Result<(), Box<ResultOpaque>> {
            Err(Box::new(ResultOpaque(i)))
        }

        pub fn new_int(i: i32) -> Result<i32, ()> {
            Ok(i)
        }

        #[diplomat::cfg(supports = custom_errors)]
        pub fn new_failing_int(i: i32) -> Result<(), i32> {
            Err(i)
        }

        pub fn new_in_enum_err(i: i32) -> Result<ErrorEnum, Box<ResultOpaque>> {
            Err(Box::new(ResultOpaque(i)))
        }

        #[diplomat::attr(dotnet, disable)]
        pub fn give_self<'a>(&'a self) -> Result<(), &'a Self> {
            Err(self)
        }

        /// When we take &str, the return type becomes a Result
        /// Test that this interacts gracefully with returning a reference type
        #[diplomat::attr(dotnet, disable)]
        pub fn takes_str<'a>(&'a mut self, _v: &str) -> &'a mut Self {
            self
        }

        #[diplomat::attr(auto, stringifier)]
        #[diplomat::attr(any(kotlin), disable)]
        #[diplomat::attr(dotnet, disable)]
        pub fn stringify_error<'a>(&'a self, _w: &mut DiplomatWrite) -> Result<(), &'a Self> {
            Err(self)
        }

        pub fn assert_integer(&self, i: i32) {
            assert_eq!(i, self.0);
        }
    }

    // FIXME: https://github.com/rust-diplomat/diplomat/issues/1123
    #[diplomat::cfg(supports=fallible_constructors)]
    pub struct FallibleOpaqueConstructor {
        x: i32,
    }

    impl FallibleOpaqueConstructor {
        #[diplomat::attr(auto, constructor)]
        pub fn ctor() -> Result<Self, Box<ResultOpaque>> {
            Err(Box::new(ResultOpaque(10)))
        }
    }

    /// An error raised as `LookupError` in languages that raise exceptions.
    #[diplomat::opaque]
    #[diplomat::cfg(supports = exceptions)]
    #[diplomat::attr(auto, exception = "LookupError")]
    pub struct MissingKey(String);

    impl MissingKey {
        #[diplomat::attr(auto, stringifier)]
        pub fn message(&self, w: &mut DiplomatWrite) {
            use std::fmt::Write;
            write!(w, "no key {:?}", self.0).unwrap();
        }
    }

    /// An error raised as `AttributeError`, so a dynamic attribute lookup failing with it works with
    /// Python's `hasattr` and `getattr(obj, name, default)`.
    #[diplomat::opaque]
    #[diplomat::cfg(supports = exceptions)]
    #[diplomat::attr(auto, exception = "AttributeError")]
    pub struct MissingAttribute(String);

    impl MissingAttribute {
        #[diplomat::attr(auto, stringifier)]
        pub fn message(&self, w: &mut DiplomatWrite) {
            use std::fmt::Write;
            write!(w, "no attribute {:?}", self.0).unwrap();
        }
    }

    /// An enum error raised as `ValueError`.
    #[derive(Debug)]
    #[diplomat::cfg(supports = exceptions)]
    #[diplomat::attr(auto, exception = "ValueError")]
    pub enum OutOfRange {
        TooSmall,
        TooLarge,
    }

    #[diplomat::opaque]
    #[diplomat::cfg(supports = exceptions)]
    pub struct ExceptionRaiser;

    impl ExceptionRaiser {
        pub fn lookup(key: &DiplomatStr) -> Result<i32, Box<MissingKey>> {
            match key {
                b"one" => Ok(1),
                _ => Err(Box::new(MissingKey(
                    String::from_utf8_lossy(key).into_owned(),
                ))),
            }
        }

        pub fn check_range(value: i32) -> Result<i32, OutOfRange> {
            match value {
                ..0 => Err(OutOfRange::TooSmall),
                101.. => Err(OutOfRange::TooLarge),
                _ => Ok(value),
            }
        }

        #[diplomat::attr(auto, constructor)]
        pub fn new() -> Box<Self> {
            Box::new(Self)
        }

        /// Resolves the attributes Python does not find on the object itself; only `answer` exists.
        #[diplomat::cfg(nanobind)]
        #[diplomat::attr(nanobind, rename = "__getattr__")]
        pub fn get_attribute(&self, name: &DiplomatStr) -> Result<i32, Box<MissingAttribute>> {
            match name {
                b"answer" => Ok(42),
                _ => Err(Box::new(MissingAttribute(
                    String::from_utf8_lossy(name).into_owned(),
                ))),
            }
        }
    }

    /// Yields `ResultOpaque(0)`, `ResultOpaque(1)`, ... up to `len` items, failing at `fail_at` if it is reached.
    #[diplomat::opaque_mut]
    #[diplomat::cfg(supports = fallible_iterators)]
    pub struct FallibleIterator {
        next: i32,
        len: i32,
        fail_at: i32,
    }

    impl FallibleIterator {
        #[diplomat::attr(auto, iterator)]
        pub fn next(&mut self) -> Result<Option<Box<ResultOpaque>>, ErrorEnum> {
            if self.next >= self.len {
                return Ok(None);
            }
            if self.next == self.fail_at {
                return Err(ErrorEnum::Bar);
            }
            self.next += 1;
            Ok(Some(Box::new(ResultOpaque(self.next - 1))))
        }
    }

    #[diplomat::opaque]
    #[diplomat::cfg(supports = fallible_iterators)]
    pub struct FallibleIterable {
        len: i32,
        fail_at: i32,
    }

    impl FallibleIterable {
        /// `fail_at` at or past `len` never fails.
        #[diplomat::attr(auto, constructor)]
        pub fn new(len: i32, fail_at: i32) -> Box<Self> {
            Box::new(Self { len, fail_at })
        }

        #[diplomat::attr(auto, iterable)]
        pub fn iter(&self) -> Box<FallibleIterator> {
            Box::new(FallibleIterator {
                next: 0,
                len: self.len,
                fail_at: self.fail_at,
            })
        }
    }
}
