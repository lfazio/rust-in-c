#include <al/print.h>

#include <rs/Rust.h>

trait(myapi) {
	Option(usize) (*sum)(void *self, usize n);
};

struct mystruct {
	usize n;

	impl(myapi);
};

struct mystruct2 {
	usize n;

	impl(myapi);
};

#define mystruct_new(v, ...) { .n = v, .instance(myapi) = __VA_ARGS__, }
#define mystruct2_new(v, ...) { .n = v, .instance(myapi) = __VA_ARGS__, }

static Option(usize) _sum(void *self, usize n)
{
	struct mystruct *s = Cast(struct mystruct *, self);
	Option(usize) o;

	if (n == 0) {
		dbgvar_fmt(s->n, "lu");
		return None(Option_new());
	}

	o = s->instance(myapi).sum(s, n - 1);
	OPTION_MATCH(o)	{
	OPTION_NONE:
		return Some(o, n);

	OPTION_SOME:
		return Some(o, Cast(void *, Option_unwrap(o) + n));

	OPTION_UNREACHABLE:
		unreachable();
	}
}

static Option(usize) _sum_sqr(void *self, usize n)
{
	struct mystruct *s = Cast(struct mystruct *, self);
	Option(usize) o;

	if (n == 0) {
		dbgvar_fmt(s->n, "lu");
		return None(Option_new());
	}

	o = s->instance(myapi).sum(s, n - 1);
	OPTION_MATCH(o)	{
	OPTION_NONE:
		return Some(o, n * n);

	OPTION_SOME:
		return Some(o, Cast(void *, Option_unwrap(o) + n * n));

	OPTION_UNREACHABLE:
		unreachable();
	}
}

int main(void)
{
	Option(usize) o;
	struct mystruct s = mystruct_new(100, { .sum = _sum, });

	struct mystruct2 s2 = mystruct2_new(100, { .sum = _sum_sqr, });


	info("Rust-like Trait example");
	info("========================");
	info("");

	o = s.instance(myapi).sum(&s, s.n);
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
		info("sum(%lu)=%lu", s.n, Cast(usize, Option_unwrap(o)));
		break;

	OPTION_UNREACHABLE:
		unreachable();
	}

	Option_drop(o);

	o = s2.instance(myapi).sum(&s2, s2.n);
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
		info("sum(%lu)=%lu", s2.n, Cast(usize, Option_unwrap(o)));
		break;

	OPTION_UNREACHABLE:
		unreachable();
	}

	Option_drop(o);


	return 0;
}