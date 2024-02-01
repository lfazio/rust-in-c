// SPDX Licence-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#include <al/print.h>

#include <rs/Rust.h>

Option(Box(usize)) sum(usize n)
{
	Option(Box(usize)) o;

	if (n == 0)
		return None(Option_new());

	o = sum(n - 1);
	OPTION_MATCH(o)	{
	OPTION_NONE:
		return Some(o, Box_create(&n, sizeof(n), true));

	OPTION_SOME: {
		Box(usize) b = Option_unwrap(o);
		usize *v = Cast(usize *, Box_ref(b));

		*v = *v + n;
		return Some(o, b);
	}

	OPTION_UNREACHABLE:
		unreachable();
	}
}

int main(void) {
	Option(Box(usize)) o;

	info("Rust-like Box in Option example");
	info("===============================");
	info("");

	o = sum(100);
	OPTION_MATCH(o) {
	OPTION_NONE:
		info("sum(0)=0");
		break;

	OPTION_SOME: {
		Box(usize) b = Option_unwrap(o);
		usize *v = Cast(usize *, Box_ref(b));

		print("<I> b=");
		Box_display(b);
		println("");
		info("sum(100)=%lu", *v);
		Box_drop(b);
		break;
	}

	OPTION_UNREACHABLE:
		unreachable();
	}

	Option_drop(o);

	return 0;
}