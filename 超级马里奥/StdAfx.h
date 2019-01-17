// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__541C1472_570F_4A2C_AF8F_ABDD575CC66C__INCLUDED_)
#define AFX_STDAFX_H__541C1472_570F_4A2C_AF8F_ABDD575CC66C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cv.h>
#include <highgui.h>
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
DWORD WINAPI JumpSound(LPVOID x);
using namespace std;
#endif // _MSC_VER > 1000
// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__541C1472_570F_4A2C_AF8F_ABDD575CC66C__INCLUDED_)
