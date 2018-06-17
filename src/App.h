#pragma once
// singelton
struct AApp {
	void (*Init   )(void);
	void (*Release)(void);
	void (*Loop   )(void);
};

extern struct AApp AApp[1];

