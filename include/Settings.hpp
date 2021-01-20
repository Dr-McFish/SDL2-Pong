#pragma once

enum Controler{KEYBOARD, MOUSE};

struct Settings {
private:
	Controler playerControler[2];
public:
	bool corrnerBouncesAllowed;

	Settings();
	Controler get_playerControler(int i);
	void set_playerControler(int i, Controler c);
};
