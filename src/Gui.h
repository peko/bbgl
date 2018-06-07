#pragma once

//Singelton
struct AGui {
	void (*Init   )();
	void (*Release)();
	void (*Update )();
	void (*Render )();
};

extern struct AGui AGui[1];
