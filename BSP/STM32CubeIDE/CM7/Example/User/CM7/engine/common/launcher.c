/*
launcher.c - direct xash3d launcher
Copyright (C) 2015 Mittorn

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/

#ifdef SINGLE_BINARY

#include "platform/fatfs/ff.h"

#include "build.h"
#include "common.h"
#ifdef XASH_SDLMAIN
#include "SDL.h"
#endif

#if XASH_EMSCRIPTEN
#include <emscripten.h>
#elif XASH_WIN32

#endif

#define E_GAME	"XASH3D_GAME" // default env dir to start from
#ifndef XASH_GAMEDIR
#define XASH_GAMEDIR	"valve"
#endif

static char        szGameDir[128]; // safe place to keep gamedir
static int         szArgc;
static char        **szArgv;

static void Sys_ChangeGame( const char *progname )
{
	// a1ba: may never be called within engine
	// if platform supports execv() function
	Q_strncpy( szGameDir, progname, sizeof( szGameDir ) - 1 );
	Host_Shutdown( );
	exit( Host_Main( szArgc, szArgv, szGameDir, 1, &Sys_ChangeGame ) );
}

void Debug_Ls(const char* path)
{
	DIR dir;
	UINT BytesWritten;
	char string[128];

	int res = f_opendir(&dir, path);

	#ifdef DBG
	if (res != FR_OK)
	  printf("res = %d f_opendir\n", res);
	#endif

	if (res == FR_OK)
	{
	  while(1)
	  {
		FILINFO fno;

		res = f_readdir(&dir, &fno);

	#ifdef DBG
		if (res != FR_OK)
		  printf("res = %d f_readdir\n", res);
	#endif

		if ((res != FR_OK) || (fno.fname[0] == 0))
		  break;

		sprintf(string, "%c%c%c%c %10d %s/%s",
		  ((fno.fattrib & AM_DIR) ? 'D' : '-'),
		  ((fno.fattrib & AM_RDO) ? 'R' : '-'),
		  ((fno.fattrib & AM_SYS) ? 'S' : '-'),
		  ((fno.fattrib & AM_HID) ? 'H' : '-'),
		  (int)fno.fsize, path, fno.fname);

		puts(string);
	  }
	}
}

int Sys_Start( void )
{
	int ret;
	const char *game = getenv( E_GAME );

	if( !game )
		game = "valve";

	printf("--------------------\n");
	printf("-- Starting xash3d...\n");
	printf("--------------------\n");

	FATFS fs;
	int res = f_mount(&fs, "", 0);
	if (res != FR_OK)
	{
		printf("Mount result: %d\n", res);
		return -1;
	}

	//Debug_Ls("valve");

	Q_strncpy( szGameDir, game, sizeof( szGameDir ));
#if XASH_EMSCRIPTEN
#ifdef EMSCRIPTEN_LIB_FS
	// For some unknown reason emscripten refusing to load libraries later
	COM_LoadLibrary("menu", 0 );
	COM_LoadLibrary("server", 0 );
	COM_LoadLibrary("client", 0 );
#endif
#if XASH_DEDICATED
	// NodeJS support for debug
	EM_ASM(try{
		FS.mkdir('/xash');
		FS.mount(NODEFS, { root: '.'}, '/xash' );
		FS.chdir('/xash');
	}catch(e){};);
#endif
#elif XASH_IOS
	{
		void IOS_LaunchDialog( void );
		IOS_LaunchDialog();
	}
#endif

	//return -1;

	ret = Host_Main( szArgc, szArgv, game, 0, Sys_ChangeGame );

	return ret;
}

#if !XASH_WIN32
#if 1
int start_hl( int argc, char **argv )
{
#if XASH_PSVITA
	// inject -dev -console into args if required
	szArgc = PSVita_GetArgv( argc, argv, &szArgv );
#else
	szArgc = argc;
	szArgv = argv;
#endif // XASH_PSVITA
	return Sys_Start();
}
#endif
#else
int __stdcall WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmdLine, int nShow)
{
	LPWSTR* lpArgv;
	int ret, i;

	szArgc = 0;

	
	//lpArgv = CommandLineToArgvW( GetCommandLineW(), &szArgc );
	szArgv = ( char** )malloc( (szArgc + 1) * sizeof( char* ));
	/*
	for( i = 0; i < szArgc; ++i )
	{
		size_t size = wcslen(lpArgv[i]) + 1;

		// just in case, allocate some more memory
		szArgv[i] = ( char * )malloc( size * sizeof( wchar_t ));
		wcstombs( szArgv[i], lpArgv[i], size );
	}

	LocalFree( lpArgv );

	*/
	szArgv[szArgc] = 0;
	ret = Sys_Start();

	//for( ; i < szArgc; ++i )
	//	free( szArgv[i] );
	free( szArgv );

	return ret;
}
#endif // XASH_WIN32


#endif
