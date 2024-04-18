// SPDX Licence-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#include <al/mm.h>
#include <al/print.h>

#include <rs/Rust.h>

trait(myapi) {
	Option(usize) (*sum)(void *self, usize n);
};

struct mystruct {
	usize n;

	impl(myapi);
	impl(Default);
};

struct mystruct2 {
	usize n;

	impl(myapi);
	impl(Default);
};

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

void *_mystruct_default(Ref(self))
{	
	struct mystruct *s = Cast(struct mystruct *, self);

	if (!s)
		return NULL;

	s->n = 100;
	s->instance(myapi).sum = _sum;
	s->instance(Default).Default = _mystruct_default;

	return self;
}

void *_mystruct_new(void)
{	
	struct mystruct *s = mm_malloc(sizeof(struct mystruct));
	return _mystruct_default(s);
}

void *_mystruct2_default(Ref(self))
{	
	struct mystruct *s = Cast(struct mystruct *, self);

	if (!s)
		return NULL;

	s->n = 100;
	s->instance(myapi).sum = _sum_sqr;
	s->instance(Default).Default = _mystruct2_default;

	return self;
}

void *_mystruct2_new(void)
{	
	struct mystruct *s = mm_malloc(sizeof(struct mystruct));
	return _mystruct2_default(s);
}

int main(void)
{
	Option(usize) o;
	struct mystruct *s = Cast(struct mystruct *, _mystruct_new());
	struct mystruct2 *s2 = Cast(struct mystruct2 *, _mystruct2_new());

	info("Rust-like Trait example");
	info("========================");
	info("");

	o = s->instance(myapi).sum(s, s->n);
	OPTION_MATCH(o) {
	OPTION_NONE:
		print("<I> o=");
		Result_drop(fmt_display(Option, o));
		println("");
		info("sum(0)=0");
		break;

	OPTION_SOME:
		print("<I> o=");
		Result_drop(fmt_display(Option, o));
		println("");
		info("sum(%lu)=%lu", s->n, Cast(usize, Option_unwrap(o)));
		break;

	OPTION_UNREACHABLE:
		unreachable();
	}

	Option_drop(o);
	mm_free(s);

	o = s2->instance(myapi).sum(s2, s2->n);
	OPTION_MATCH(o) {
	OPTION_NONE:
		print("<I> o=");
		Result_drop(fmt_display(Option, o));
		println("");
		info("sum(0)=0");
		break;

	OPTION_SOME:
		print("<I> o=");
		Result_drop(fmt_display(Option, o));
		println("");
		info("sum(%lu)=%lu", s2->n, Cast(usize, Option_unwrap(o)));
		break;

	OPTION_UNREACHABLE:
		unreachable();
	}

	Option_drop(o);
	mm_free(s2);

	return 0;
}