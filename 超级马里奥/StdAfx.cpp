// stdafx.cpp : source file that includes just the standard includes
//	’˝ Ω≈‡—µ2.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
DWORD WINAPI JumpSound(LPVOID x)
{
	PlaySound(".\\vic\\Free-Converter.com-jump-3171640.wav",NULL,SND_FILENAME | SND_ASYNC );
	//mciSendString(TEXT("play .\\vic\\jump.mp3 "),NULL,0,NULL);
	return 0;
}
