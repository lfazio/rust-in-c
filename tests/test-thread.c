// SPDX Licence-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#include <al/print.h>

#include <rs/Rust.h>

static int _thread1(void *arg) {
	let(t, Thread()) = Thread_current();

	for (int i = 0; i < 10; i++) {
		print("<I> thread=");
		Result_drop(Thread_display(t));
		println(": hi number %d from the spawned thread!", i);
		Thread_sleep(Duration_from_millis(10));
	}

	return 0;

	(void)arg;
}

int main(void) {
	let(t1, Thread());

	info("Rust-like Thread example");
	info("========================");
	info("");

	t1 = Thread_spawn_config("_thread1", _thread1, NULL);

	for (int i = 0; i < 5; i++) {
		info("hi number %d from the main thread!", i);
		Thread_sleep(Duration_from_millis(10));
	}

	Result_drop(Thread_join(t1));

	return 0;
}
