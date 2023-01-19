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
 ****************************************************************************/

/*
 * \file algo_export.h
 * \brief Import/export macro definition
 *
 * \author Martin Maška (xmaska@fi.muni.cz)
 * \date 2010
 */

#ifndef __ALGO_EXPORT_H__
#define __ALGO_EXPORT_H__

#include "i3d_config.h"

/***************************************************************************\
*
*                            Macro definitions
*
\***************************************************************************/

//--------------------------------------------------------------------------
// Macros for making or using i3dalgo as a DLL
//--------------------------------------------------------------------------
#if defined(_MSC_VER) // MSVC.NET compiler
#	if defined(I3D_ALGO_SHOULD_EXPORT)	// export symbols (when creating shared library)
#		define I3D_ALGO_EXPORT __declspec(dllexport)
#		define I3D_ALGO_EXPORT_DATA(type) __declspec(dllexport) type
#	else // import symbols (when using library)
#		define I3D_ALGO_EXPORT __declspec(dllimport)
#		define I3D_ALGO_EXPORT_DATA(type) __declspec(dllimport) type
#	endif
#else // compiler doesn't support __declspec(), e.g. Linux gcc
#	define I3D_ALGO_EXPORT
#	define I3D_ALGO_EXPORT_DATA(type) type
#endif

#endif // __ALGO_EXPORT_H__
