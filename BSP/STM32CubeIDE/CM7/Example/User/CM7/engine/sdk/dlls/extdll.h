/***
*
*	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*	
*	This product contains software technology licensed from Id 
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/
#pragma once
#if !defined(EXTDLL_H)
#define EXTDLL_H

#define NO_VOICEGAMEMGR 1

//
// Global header file for extension DLLs
//

// Allow "DEBUG" in addition to default "_DEBUG"
#if _DEBUG
#define DEBUG 1
#endif

// Silence certain warnings
#if _MSC_VER
#pragma warning(disable : 4244)		// int or float down-conversion
#pragma warning(disable : 4305)		// int or float data truncation
#pragma warning(disable : 4201)		// nameless struct/union
#pragma warning(disable : 4514)		// unreferenced inline function removed
#pragma warning(disable : 4100)		// unreferenced formal parameter
#endif

// Prevent tons of unused windows definitions
#if _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOWINRES
#define NOSERVICE
#define NOMCX
#define NOIME
#define HSPRITE HSPRITE_win32
#include <windows.h>
#undef HSPRITE
#else // _WIN32
#if !defined(FALSE)
#define FALSE 0
#endif
#if !defined(TRUE)
#define TRUE (!FALSE)
#endif
#include <limits.h>
#include <stdarg.h>
typedef unsigned int ULONG;
typedef unsigned char BYTE;
typedef int BOOL;
#define MAX_PATH PATH_MAX
#if !defined(PATH_MAX)
#define PATH_MAX 4096
#endif
#endif //_WIN32

// Misc C-runtime library headers
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#if HAVE_CMATH
#include <cmath>
#else
#include <math.h>
#endif

#if !defined(M_PI_F)
#define M_PI_F          (float)M_PI
#endif

#if __LP64__ || __LLP64__ || _WIN64 || (__x86_64__ && !__ILP32__) || _M_X64 || __ia64 || _M_IA64 || __aarch64__ || __powerpc64__
  #define XASH_64BIT	1
#endif

// Header file containing definition of globalvars_t and entvars_t
typedef unsigned int func_t;
typedef int string_t;				// from engine's pr_comp.h;
typedef float vec_t;				// needed before including progdefs.h

// Vector class
#include "vector.h"

// Defining it as a (bogus) struct helps enforce type-checking
#define vec3_t Vector

// Shared engine/DLL constants
#include "../common/const.h"
#include "../engine/progdefs.h"
#include "../engine/edict.h"

// Shared header describing protocol between engine and DLLs
#include "../engine/eiface.h"

// Shared header between the client DLL and the game DLLs
#include "cdll_dll.h"
#if !defined(Q_min)
#define Q_min(a,b)  (((a) < (b)) ? (a) : (b))
#endif
#if !defined(Q_max)
#define Q_max(a,b)  (((a) > (b)) ? (a) : (b))
#endif

#endif //EXTDLL_H
