// SPDX Licence-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#include <errno.h>

#include <al/print.h>

#include <rs/Rust.h>

Result(usize, int) sum(usize n)
{
	Result(usize, int) r;

	if (n == 0)
		return Err(Result_new(), Deref(-ERANGE));

	r = sum(n - 1);
	RESULT_MATCH(r)	{
	RESULT_ERR:
		return Ok(r, Deref(n));

	RESULT_OK:
		return Ok(r, Cast(void *, Deref(Result_unwrap(r) + n)));

	RESULT_UNREACHABLE:
		unreachable();
	}
}

int main(void) {
	Result(usize, int) r;

	info("Rust-like Result example");
	info("========================");
	info("");

	r = sum(100);
	RESULT_MATCH(r) {
	RESULT_ERR:
		print("<I> r=");
		Result_display(r);
		println("");
		info("sum(0)=0");
		break;

	RESULT_OK:
		print("<I> r=");
		Result_display(r);
		println("");
		info("sum(100)=%lu", Cast(usize, Result_unwrap(r)));
		break;

	RESULT_UNREACHABLE:
		unreachable();
	}

	Result_drop(r);

	return 0;
}