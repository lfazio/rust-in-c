// SPDX Licence-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#include <al/mm.h>
#include <al/print.h>

#include <rs/Rust.h>
#include <rs/std/fmt/Display.h>

int main(void) {
	Option(usize) o;
	Vec(usize) v = Vec_new(usize, NULL);
	VecIter(usize) iter;
	let(i, usize);
	let(value, usize *);

	info("Rust-like Vec example");
	info("=====================");
	info("");

	info("* TEST: PUSH");
	info("  * Populating Vec...");
	for (i = 0; i < 100; i++) {
		info("Vec_push(%lu)=%lu", i, i);
		Vec_push(v, &i);
	}

	info("* TEST: POP");
	do {
		o = Vec_pop(v);
		if (Option_is_none(o)) {
			Option_drop(o);
			Vec_drop(v);
			break;
		}
		value = Cast(usize *, Option_unwrap(o));
		info("Vec_pop(%lu)", *value);
		Option_drop(o);
		mm_free(value);
	} while (true);

	info("* TEST: ITERATOR");
	info("  * Populating Vec...");
	v = Vec_with_capacity(usize, 100, NULL);
	for (i = 0; i < 100; i++) {
		info("Vec_push(%lu)=%lu", i, i);
		Vec_push(v, &i);
	}

	info("  * Iterating over Vec...");
	iter = VecIter_To(VecIter_From(Vec_IntoIterator(v), 20), 90);
	Vec_foreach(iter, usize) {
		value = Cast(usize *, Option_unwrap(o));
		info("VecIter_next(%lu)", *value);
	};
	VecIter_drop(iter);

	info("* TEST: ITERATOR");
	info("  * Iterating over Vec...");
	iter = VecIter_To(VecIter_From(Vec_IntoIterator(v), 20), 90);
	Vec_foreach(iter, usize) {
		value = Cast(usize *, Option_unwrap(o));
		*value *= 2;
		Vec_set(v, VecIter_enumerate(iter), value);
		info("Vec_set(%lu)", *value);
	};
	VecIter_drop(iter);

	iter = VecIter_To(VecIter_From(Vec_IntoIterator(v), 20), 90);
	Vec_foreach(iter, usize) {
		value = Cast(usize *, Option_unwrap(o));
		info("VecIter_next(%lu)=%lu", VecIter_enumerate(iter), *value);
	};
	VecIter_drop(iter);

	value = Vec_remove(v, 1);
	info("Vec_remove(1)=%lu", *value);
	mm_free(value);
	value = Vec_remove(v, 1);
	info("Vec_remove(1)=%lu", *value);
	mm_free(value);

	// let(zero, usize) = 0;
	// Vec_insert(v, 50, &zero);
	// Vec_insert(v, 52, &zero);

	iter = Vec_IntoIterator(v);
	Vec_foreach(iter, usize) {
		value = Cast(usize *, Option_unwrap(o));
		info("VecIter_next(%lu)=%lu", VecIter_enumerate(iter), *value);
	};
	VecIter_drop(iter);

	Vec_drop(v);

	return 0;
}