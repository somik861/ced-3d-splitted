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

/** \file watersheds_internal.h
\brief Part of mathematical morphology routines - header.

This file provides support functions for various watershed transformation functions.
*/

#ifndef __WATERSHEDS_INTERNAL_H__
#define __WATERSHEDS_INTERNAL_H__

#ifdef __GNUG__
#	pragma interface
#endif

#include "image3d.h"
#include "neighbours.h"

namespace i3d
{
	/** \addtogroup morph */
	///@{

	/** Creates marker image from the given input image using the regional minima as a markers. 
	\param input the input image
	\param marker the output marker image
	\param neighbourhood the neighbourhood used for the computation
	*/
	template <typename T>
	I3D_ALGO_EXPORT void WSInternalMarkerFromMinima(const Image3d<T> &input, Image3d<size_t> &marker, const Neighbourhood &neighbourhood);
	
	///@} end of morph group part

} // namespace i3d

#endif // #ifndef __WATERSHEDS_INTERNAL_H__
