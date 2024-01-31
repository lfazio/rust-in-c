#include <al/print.h>

#include <rs/Rust.h>

Option(Box(usize)) sum(usize n)
{
	Option(Rc(Box(usize))) o;

	if (n == 0)
		return None(Option_new());

	o = sum(n - 1);
	OPTION_MATCH(o)	{
	OPTION_NONE:
		return Some(o, Rc_create(Box_create(&n, sizeof(n), true), Box_free));

	OPTION_SOME: {
		Rc(Box(usize)) rc = Option_unwrap(o);
		usize *v;

		Rc_lock(rc);
		v = Cast(usize *, Box_ref(Rc_ref(rc)));
		*v = *v + n;
		Rc_unlock(rc);

		return Some(o, rc);
	}

	OPTION_UNREACHABLE:
		unreachable();
	}
}

int main(void) {
	Option(Rc(Box(usize))) o;

	info("Rust-like Rc of Box in Option example");
	info("=====================================");
	info("");

	o = sum(100);
	OPTION_MATCH(o) {
	OPTION_NONE:
		info("sum(0)=0");
		break;

	OPTION_SOME: {
		Rc(Box(usize)) rc = Option_unwrap(o);
		usize *v;

		Rc_lock(rc);
		v = Cast(usize *, Box_ref(Rc_ref(rc)));

		print("<I> rc=");
		Rc_display(rc);
		println("");
		info("sum(100)=%lu", *v);
		Rc_unlock(rc);

		Rc_drop(rc);
		break;
	}

	OPTION_UNREACHABLE:
		unreachable();
	}

	Option_drop(o);

	return 0;
}