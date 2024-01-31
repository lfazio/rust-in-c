#include <al/print.h>

#include <rs/Rust.h>

Option(usize) sum(usize n)
{
	Option(usize) o;

	if (n == 0)
		return None(Option_new());

	o = sum(n - 1);
	OPTION_MATCH(o)	{
	OPTION_NONE:
		return Some(o, n);

	OPTION_SOME:
		return Some(o, Cast(void *, Option_unwrap(o) + n));

	OPTION_UNREACHABLE:
		unreachable();
	}
}

int main(void) {
	Option(usize) o;

	info("Rust-like Option example");
	info("========================");
	info("");

	o = sum(100);
	OPTION_MATCH(o) {
	OPTION_NONE:
		print("<I> o=");
		Option_display(o);
		println("");
		info("sum(0)=0");
		break;

	OPTION_SOME:
		print("<I> o=");
		Option_display(o);
		println("");
		info("sum(100)=%lu", Cast(usize, Option_unwrap(o)));
		break;

	OPTION_UNREACHABLE:
		unreachable();
	}

	Option_drop(o);

	return 0;
}