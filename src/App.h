#pragma once
// singelton
struct AApp {
	void (*Init)();
	void (*Loop)();
};

extern struct AApp AApp[1];

