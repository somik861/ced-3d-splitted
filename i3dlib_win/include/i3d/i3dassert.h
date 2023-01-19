/*
* i3dlib - image manipulation library
*
* Copyright (C) 2000-2006   Centre for Biomedical Image Analysis (CBIA)
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Library General Public
* License as published by the Free Software Foundation; either
* version 2 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Library General Public License for more details.
*
* You should have received a copy of the GNU Library General Public
* License along with this library; if not, write to the Free
* Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

/** \file i3dassert.h
Various useful itra-library assertion macros
*/

#ifndef __I3DASSERT_H__
#define __I3DASSERT_H__

#include <sstream>
#include <string>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tchar.h>
#else // #ifdef _WIN32
#include <iostream>
#include <cctype>
#endif // #ifdef _WIN32
#include "basic.h"

namespace i3d
{

	/** Handles various asserts, should not be used directly but through the macros defined below
	\param[in] expression	expression used for the asserion
	\param[in] description	additional description of the situation, can be NULL
	\param[in] file			file where the assertion takes place
	\param[in] function		function where the assertion takes place
	\param[in] line			line where the assertion takes place
	\param[in,out] hit		how many times should this assertion be checked - 0 means do not check, -1 or NULL pointer means always, or use positive integer that will be decreased
	\param[in] behavior		behavior of the assertion - 0 means return a value whether to break the execution, 1 means throw an internal exception, 2 means throw an IO exception
	\return					whether to break the execution or not
	*/
	inline bool i3dAssertFn(const char *expression, const char *description, const char *file, const char *function, int line, int *hit, int behavior)
	{
		// check and decrease hit count
		if (hit && *hit == 0)
			return false;
		else if (hit && *hit != -1)
			--*hit;
		// prepare the assertion message
		std::stringstream message;
		message << "Assertion (" << expression << ") failed in function " << function << " in file " << file << " at line " << line << ".";
		if (description)
			message << std::endl << "Description: " << description;
		// throw the message if requested to
		switch (behavior)
		{
		case 1:
			throw i3d::InternalException(message.str());
		case 2:
			throw i3d::IOException(message.str());
		}		
		// let the user decide whether to break or not
#ifdef _WIN32
		message << std::endl << "Break the execution?";
		UINT mbType;
		if (hit)
		{
			message << " Cancel ignores this assertion forever.";
			mbType = MB_YESNOCANCEL | MB_ICONERROR;
		}
		else
			mbType = MB_YESNO;
		switch (MessageBox(NULL, (LPCTSTR)(message.str().c_str()), _T("Assertion failed"), mbType))
		{
		case IDYES:
			return true;
		case IDNO:
			return false;
		case IDCANCEL:
			*hit = 0;
			return false;
		}
#else
		char c;
		std::cout << message.str() << std::endl;
		std::cout << "(B)reak, (C)ontinue";
		if (hit)
			std::cout << ", (I)gnore assertion forever";
		std::cout << "?" << std::endl;
		while (true)
		{
			std::cin >> c;
			switch (toupper(c))
			{
			case 'B':
				return true;
			case 'C':
				return false;
			case 'I':
				if (hit)
				{
					*hit = 0;
					return false;
				}
				break;
			}
		}
#endif // #ifdef _WIN32
		return false;
	}

	/// assertion macro (debug and release) that throws an internal exception
	#define I3DASSERT_ALWAYS_E(expression) \
	{ \
		if (!(expression)) \
			i3d::i3dAssertFn(#expression, NULL, __FILE__, I3DASSERT_FUNCTION_NAME, __LINE__, NULL, 1); \
	}

	/// assertion macro (debug and release) that throws an internal exception with some text
	#define I3DASSERT_ALWAYS_ET(expression, description) \
	{ \
		if (!(expression)) \
			i3d::i3dAssertFn(#expression, description, __FILE__, I3DASSERT_FUNCTION_NAME, __LINE__, NULL, 1); \
	}

	/// assertion macro (debug and release) that throws an IO exception
	#define I3DASSERT_ALWAYS_EI(expression) \
	{ \
		if (!(expression)) \
			i3d::i3dAssertFn(#expression, NULL, __FILE__, I3DASSERT_FUNCTION_NAME, __LINE__, NULL, 2); \
	}

	/// assertion macro (debug and release) that throws an IO exception with some text
	#define I3DASSERT_ALWAYS_EIT(expression, description) \
	{ \
		if (!(expression)) \
			i3d::i3dAssertFn(#expression, description, __FILE__, I3DASSERT_FUNCTION_NAME, __LINE__, NULL, 2); \
	}

#ifdef I3D_DEBUG

	/// assertion macro (debug only) that allows breaking of the execution
	#define I3DASSERT_B(expression) \
	{ \
		static int hitCount = -1; \
		if (!(expression)) \
			if (i3d::i3dAssertFn(#expression, NULL, __FILE__, I3DASSERT_FUNCTION_NAME, __LINE__, &hitCount, 0)) \
				{ I3DASSERT_DEBUG_BREAK; } \
	}

	/// assertion macro that allows breaking of the execution and prints out some text
	#define I3DASSERT_BT(expression, description) \
	{ \
		static int hitCount = -1; \
		if (!(expression)) \
			if (i3d::i3dAssertFn(#expression, description, __FILE__, I3DASSERT_FUNCTION_NAME, __LINE__, &hitCount, 0)) \
				{ I3DASSERT_DEBUG_BREAK; } \
	}

	/// assertion macro that throws an internal exception
	#define I3DASSERT_E(expression) \
	{ \
		if (!(expression)) \
			i3d::i3dAssertFn(#expression, NULL, __FILE__, I3DASSERT_FUNCTION_NAME, __LINE__, NULL, 1); \
	}

	/// assertion macro that throws an internal exception with some text
	#define I3DASSERT_ET(expression, description) \
	{ \
		if (!(expression)) \
			i3d::i3dAssertFn(#expression, description, __FILE__, I3DASSERT_FUNCTION_NAME, __LINE__, NULL, 1); \
	}

	/// assertion macro that throws an IO exception
	#define I3DASSERT_EI(expression) \
	{ \
		if (!(expression)) \
			i3d::i3dAssertFn(#expression, NULL, __FILE__, I3DASSERT_FUNCTION_NAME, __LINE__, NULL, 2); \
	}

	/// assertion macro that throws an IO exception with some text
	#define I3DASSERT_EIT(expression, description) \
	{ \
		if (!(expression)) \
			i3d::i3dAssertFn(#expression, description, __FILE__, I3DASSERT_FUNCTION_NAME, __LINE__, NULL, 2); \
	}

#else // #ifdef I3D_DEBUG

#define I3DASSERT_B(expression) ((void)0)
#define I3DASSERT_BT(expression, description) ((void)0)
#define I3DASSERT_E(expression) ((void)0)
#define I3DASSERT_ET(expression, description) ((void)0)
#define I3DASSERT_EI(expression) ((void)0)
#define I3DASSERT_EIT(expression, description) ((void)0)

#endif // #ifdef I3D_DEBUG

#ifdef _MSC_VER
#define I3DASSERT_FUNCTION_NAME __FUNCTION__
#define I3DASSERT_DEBUG_BREAK __debugbreak()
#else // #ifdef _MSC_VER
#define I3DASSERT_FUNCTION_NAME __PRETTY_FUNCTION__
#define I3DASSERT_DEBUG_BREAK asm("int $3;nop")
#endif // #ifdef _MSC_VER

} // namespace i3d

#endif // #ifndef __I3DASSERT_H__
