#include "Error.h"

Error::Error(int blad)
{
	kod = blad;
}

void Error::err()
{
	switch (kod)
	{
	case font:
		MessageBoxA(NULL, "Nie udalo sie wczytac fonta.", "ERROR", MB_OK);
		exit(-1);
		break;
	case music:
		MessageBoxA(NULL, "Nie udalo sie wczytac muzyki.", "ERROR", MB_OK);
		exit(-2);
		break;
	case sfx:
		MessageBoxA(NULL, "Nie udalo sie wczytac efektu dzwiekowego.", "ERROR", MB_OK);
		exit(-3);
		break;
	case texture:
		MessageBoxA(NULL, "Nie udalo sie wczytac tekstury", "ERROR", MB_OK);
		exit(-4);
		break;
	default:
		MessageBoxA(NULL, "Nieznany blad", "ERROR", MB_OK);
		exit(-5);
		break;
	}
}