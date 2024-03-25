#ifdef WIN32
	#ifndef _DEBUG
		#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
	#endif
#endif

#include "game.h"

int main()
{
	runInstance();
	return 0;
}