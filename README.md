Rust-like Struct for C development
==================================

This is just a project for fun.

# Rust-like structures

It is a mimic of structures used in the [Rust language](https://www.rust-lang.org).
I've found them useful and practical for C development. This can be improved with 
other structures used in `rust`.

It is plain `c11`.

## Option

This structure is used in the [Rust language](https://www.rust-lang.org) and allows to return Some or None values.

```c
#include <rs/Rust.h>

// Use an Option to hold an errno value
Option(int) myfunc(void) {
	Option(int) x = Some(Option_new(), Deref(-EINVAL));
	return x;
}

int main(void) {
	Option(int) x = myfunc();

	OPTION_MATCH(x) {
	OPTION_NONE:
		printf("No error...\n");
		break;

	OPTION_SOME:
		printf("Some error: %d...\n", Cast(int, Option_unwrap(x)));
		break;

	OPTION_UNREACHABLE:
		printf("Unreachable...\n");
		break;
	}

	Option_drop(x);

	return 0;
}
```

The type in the `Option(type)` option type construct is used to recall the user the type stored inside. This is not used by the Option(type) macro.

The interface is defined in [`Option.h`](include/rs/Option.h) and an example can be found in [`tests/test-option.c`](tests/test-option.c).

## Result

This structure is used in the [Rust language](https://www.rust-lang.org) and allows to return good values `Ok()` or erroneous values `Err()`.

```c
#include <rs/Rust.h>

// Use a Result to hold either a valid value or an errno value
Result(usize, int) myfunc(void) {
	Result(usize, int) x = Err(Result_new(), Deref(-EINVAL));
	return x;
}

int main(void) {
	Result(int) x = myfunc();

	RESULT_MATCH(x) {
	RESULT_OK:
		printf("Ok: %u...\n", Cast(usize, Result_unwrap(x)));
		break;

	RESULT_ERR:
		printf("Err: %d...\n", Cast(int, Result_err(x)));
		break;

	RESULT_UNREACHABLE:
		printf("Unreachable...\n");
		break;
	}

	Result_drop(x);

	return 0;
}
```

The types in the `Result(type_ok, type_err)` Result type construct are used to recall the user the types stored inside. They are not used by the Result(type_ok, type_err) macro.

The interface is defined in [`Result.h`](include/rs/Result.h) and an example can be found in [`tests/test-result.c`](tests/test-result.c).


## Box

Box is used in the [Rust language](https://www.rust-lang.org) and allows to allocate memory on the heap.

The interface is defined in [`Box.h`](include/rs/Box.h) and an example can be found in [`tests/test-box.c`](tests/test-box.c).

## Rc

Rc is used in the [Rust language](https://www.rust-lang.org) and allows to reference counted objects.

The interface is defined in [`Rc.h`](include/rs/Rc.h) and an example can be found in [`tests/test-rc.c`](tests/test-rc.c).

## Trait

Traits are similar to interfaces in other languages.

The interface is defined in [`Trait.h`](include/rs/Trait.h) and an example can be found in [`tests/test-trait.c`](tests/test-trait.c).


## Build

Just run the following command to build librs.a and also the examples.

```sh
make
```

In order to clean intermediate files:

```sh
make clean
```

And in order to clean all generated files:

```sh
make distclean
```

The makefile is easily twekable so you can use it to build your own projects or just
to prototype with it in your own example.

# LICENCE

The licence of this project is Apache 2.0. See the [LICENCE file](LICENCE) for more details.