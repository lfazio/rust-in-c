// SPDX Licence-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#include <al/print.h>

#include <rs/Rust.h>

Option(Box(usize)) sum(usize n)
{
	Option(Arc(Box(usize))) o;

	if (n == 0)
		return None(Option_new());

	o = sum(n - 1);
	OPTION_MATCH(o)	{
	OPTION_NONE:
		return Some(o, Arc_create(Box_create(&n, sizeof(n), true), Box_free));

	OPTION_SOME: {
		Arc(Box(usize)) rc = Option_unwrap(o);
		usize *v;

		Arc_lock(rc);
		v = Cast(usize *, Box_ref(Arc_ref(rc)));
		*v = *v + n;
		Arc_unlock(rc);

		return Some(o, rc);
	}

	OPTION_UNREACHABLE:
		unreachable();
	}
}

int main(void) {
	Option(Arc(Box(usize))) o;

	info("Rust-like Arc of Box in Option example");
	info("======================================");
	info("");

	o = sum(100);
	OPTION_MATCH(o) {
	OPTION_NONE:
		info("sum(0)=0");
		break;

	OPTION_SOME: {
		Arc(Box(usize)) arc = Option_unwrap(o);
		usize *v;

		Arc_lock(arc);
		v = Cast(usize *, Box_ref(Arc_ref(arc)));

		print("<I> arc=");
		Result_drop(fmt_display(Arc, arc));
		println("");
		info("sum(100)=%lu", *v);
		Arc_unlock(arc);

		Arc_drop(arc);
		break;
	}

	OPTION_UNREACHABLE:
		unreachable();
	}

	Option_drop(o);

	return 0;
}