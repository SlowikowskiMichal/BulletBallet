#pragma once

#include <Windows.h>

class Error
{
public:
	enum { font, music, sfx, texture, window };
	Error(int);
	void err();
private:
	int kod;
};


