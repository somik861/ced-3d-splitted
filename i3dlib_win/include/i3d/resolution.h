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


#ifndef __RESOLUTION_H__
#define __RESOLUTION_H__

#ifdef __GNUG__
#pragma interface
#endif

#include <cstdio>
#include <iostream>
#include <valarray>

#include "basic.h"
#include "vector3d.h"

namespace i3d {

	/***************************************************************************\
	*
	*                           Default Resolution
	*
	\***************************************************************************/
	/** Default resolution. 
	This resolution is used in library functions if an image has undefined 
	resolution. */
	const Vector3d<float> DefaultResolution(10,10,10);


	/***************************************************************************\
	*
	*                               Resolution
	*
	\***************************************************************************/
	/** 3D image resolution. 
	Resolution has three components in pixels per micron. 
	If any component is set to zero, the resolution is set to undefined.
	*/
	class I3D_CORE_EXPORT Resolution {

	public:
		//--------------------------------------------------------------------------
		// Constructors and operators
		//--------------------------------------------------------------------------
		/** Constructor */
		Resolution(float x = 0, float y = 0, float z = 0);

		/** Copy constructor */
		Resolution(const Vector3d<float> &res);

		/** Assignment operator from a vector. */
		Resolution &operator= (const Vector3d<float> &v);

		//--------------------------------------------------------------------------
		// Set functions
		//--------------------------------------------------------------------------
		/** Set resulution in 'x' axis */
		void SetX(float x);

		/** Set resulution in 'y' axis */
		void SetY(float y);

		/** Set resulution in 'z' axis */
		void SetZ(float z);

		//--------------------------------------------------------------------------
		// Get functions
		//--------------------------------------------------------------------------
		/** Get resolution in 'x' axis */
		float GetX(void) const { return res.x; }

		/** Get resolution in 'y' axis */
		float GetY(void) const { return res.y; }

		/** Get resolution in 'z' axis */
		float GetZ(void) const { return res.z; }

		/** Get resolution as a vector. \returns Stored resolution or DefaultResolution 
		if the resolution is undefined. */
		Vector3d<float> GetRes() const { return res; };

		//--------------------------------------------------------------------------
		// Other member functions
		//--------------------------------------------------------------------------
		/** Set resolution undefined */
		void Undefine(); 

		/** \returns \p true if the resolution is defined, \p false otherwise.*/
		bool IsDefined() const { return defined; };

	private:
		bool defined; 
		Vector3d<float> res;

	}; // Resolution


	/***************************************************************************\
	*
	*                            Conversion functions
	*
	\***************************************************************************/
	/** Convert vector in microns to a vector in pixels using the given resolution.
	If the resolution is not defined, default resolution is used. */
	inline Vector3d<PIXELS::T_offset> MicronsToPixels(
		const Vector3d<float> &v,
		const Resolution &r) 
	{
		Vector3d<float> res = r.GetRes();
		return Vector3d<PIXELS::T_offset>(static_cast<PIXELS::T_offset>(roundf(v.x * res.x)),
										  static_cast<PIXELS::T_offset>(roundf(v.y * res.y)),
										  static_cast<PIXELS::T_offset>(roundf(v.z * res.z)));
	}

	/** Convert vector in pixels to a vector in microns using the given resolution.
	If the resolution is not defined, default resolution is used. */
	template <class T> I3D_CORE_EXPORT inline Vector3d<float> PixelsToMicrons(
		const Vector3d<T> &v,
		const Resolution &r) 
	{
		return Vector3d<float>(v) / r.GetRes();
	}

}

#endif
