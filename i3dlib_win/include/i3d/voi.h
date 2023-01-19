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

/** \file voi.h
 Volume of interest. 
 
 This file is intended for classes, functions, and operators related 
 to VOI type, which represents volume of interest. 
 */

#ifndef __VOI_H__
#define __VOI_H__

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
	*                                  VOI
	*
	\***************************************************************************/
	/** Volume of interest. 
	VOI is a cuboidal area with offset and size of a certain type given by the 
	template parameter. This type knows nothing about the units, but it is expected 
	that offset and size are in the same units. 
	
	Useful operators are defined for this class	for natural combining several 
	VOIs and testing presence of points inside/outside the VOI.
	*/
	template <class UNIT> struct I3D_CORE_EXPORT VOI 
	{
		/** Definition of data-types */
		typedef typename UNIT::T_offset T_offset;
		typedef typename UNIT::T_size T_size;

		public:
			/** Origin of VOI */
			Vector3d<T_offset> offset; 

			/** Size of VOI */
			Vector3d<T_size> size;  

			/** Constructor  */
			VOI(T_offset off_x = 0, 
				 T_offset off_y = 0, 
				 T_offset off_z = 0, 
				 T_size sz_x = 0, 
				 T_size sz_y = 0,
				 T_size sz_z = 0)
				: offset(off_x,off_y,off_z), size(sz_x,sz_y,sz_z) 		
			{
				 if ((sz_x < 0) || (sz_y < 0) || (sz_z < 0))
					  throw LibException("i3d::VOI<>: you cannot define a negative size.");
			}

			/** Constructor */
			VOI(const Vector3d<T_offset> &offset_, const Vector3d<T_size> &size_)
				: offset(offset_), size(size_) 
			{
				 if ((size_.x < 0) || (size_.y < 0) || (size_.z < 0))
					  throw LibException("i3d::VOI<>: you cannot define a negative size.");
			}

			/** Conversion constructor. */
			template <class UNIT2> VOI(const VOI<UNIT2> &voi) // Conversion constructors of the Vector3d class are exploited
				: offset(voi.offset), size(voi.size) {};

			/** Desctructor */
            ~VOI() {};


			/** Is VOI empty? 
			\returns \p true if size.x == size.y == size.z == 0 */
			bool is_empty(void) const
			{
				 return ((size.x == 0) && (size.y == 0) && (size.z == 0)); 
			}

			/** Union of two VOIs */
			VOI &operator+= (const VOI &v) 
			{
				Vector3d<T_offset> pos = 
				  max(offset + static_cast<Vector3d<T_offset> >(size), 
					  v.offset + static_cast<Vector3d<T_offset> >(v.size));
				offset = min(offset, v.offset);
				size = static_cast<Vector3d<T_size> >(pos - offset);
				return *this;
			}

			/** Intersection of two VOIs */
			VOI &operator*= (const VOI &v) 
			{
				Vector3d<T_offset> pos = 
					min(offset + static_cast<Vector3d<T_offset> >(size),
								v.offset + static_cast<Vector3d<T_offset> >(v.size));
				offset = max(offset, v.offset);

				if ((pos.x < offset.x) || 
					 (pos.y < offset.y) || 
					 (pos.z < offset.z)) 
				{ 
					 size = 0; 
				} 
				else 
				{
					 size = static_cast<Vector3d<T_size> >(pos - offset);
				}
				return *this;
			}

			/** Get the VOI size. */
			T_size Size() const 
			{ 
				return size.x * size.y * size.z; 
			}

			/** Get the last position in the VOI. */
			i3d::Vector3d<T_offset> LastPos() const 
			{ 
				if (Size() > 0)
				{
					return offset + static_cast<Vector3d<T_offset> >(size - T_size(1));
				}

				throw InternalException("i3d::VOI<>: Empty VOI!");
			}
				
	}; // VOI

	//--------------------------------------------------------------------------
	// Operators between two VOIs
	//--------------------------------------------------------------------------
	/** Equality operator. Two VOIs are equal if they have the same offset as 
	well as the same size. */
	template <class UNIT> inline bool operator== (
		const VOI<UNIT> &v1, 
		const VOI<UNIT> &v2) 
	{
		return (
			v1.offset.x == v2.offset.x &&
			v1.offset.y == v2.offset.y &&
			v1.offset.z == v2.offset.z &&
			v1.size.x == v2.size.x &&
			v1.size.y == v2.size.y &&
			v1.size.z == v2.size.z);
	}

	/** Inequality operator. Two VOIs are different if they differ in at least one
	component of their offsets or sizes. */
	template <class UNIT> inline bool operator!= (
		const VOI<UNIT> &v1, 
		const VOI<UNIT> &v2) 
	{
		return (
			v1.offset.x != v2.offset.x ||
			v1.offset.y != v2.offset.y ||
			v1.offset.z != v2.offset.z ||
			v1.size.x != v2.size.x ||
			v1.size.y != v2.size.y ||
			v1.size.z != v2.size.z);
	}

	/** Intersection operator. Creates intersection of two VOIs. */
	template <class UNIT> inline VOI<UNIT> operator* (
		const VOI<UNIT> &v1, 
		const VOI<UNIT> &v2) 
	{
		VOI<UNIT> v(v1);
		v *= v2;
		return v;
	}

	/** Union operator. Creates union of two VOIs. */
	template <class UNIT> inline VOI<UNIT> operator+ (
		const VOI<UNIT> &v1, 
		const VOI<UNIT> &v2) 
	{
		VOI<UNIT> v(v1);
		v += v2;
		return v;
	}


	//--------------------------------------------------------------------------
	// Other operators
	//--------------------------------------------------------------------------
	/** Output operator. Writes information about the VOI into the stream. */
	template <class UNIT> inline 
	std::ostream& operator<<(std::ostream& os, const VOI<UNIT> &v)
	{
		os << "[" << v.offset << ";" << v.size << "]";
		return os;
	}

	//--------------------------------------------------------------------------
	// Functions
	//--------------------------------------------------------------------------
	/** Convertion of VOI to std::gslice. Function creates std::gslice that 
	describes the same set of voxels as \p voi in an image with size \p imgsize. 
	No checks are done, therefore the returned gslice can address voxels outside 
	the image. */
	I3D_CORE_EXPORT std::gslice VOItoGslice(const VOI<UPIXELS> &voi,
		const Vector3d<size_t> &imgsize);

	/** Is point inside VOI? 
	\returns \p true if \p voi.offset < point < voi.offset + voi.size. 
	\returns \p false otherwise. */
	template <class UNIT> inline 
	bool InOO(const VOI<UNIT> &voi, 
				 const Vector3d<typename UNIT::T_offset> &point)
	{ 
		return point.InOO(voi.offset, voi.offset + voi.size);
	}

	/** Is point inside VOI or on the right boundary? 
	\returns \p true if \p voi.offset < point <= voi.offset + voi.size. 
	\returns \p false otherwise. */
	template <class UNIT> inline 
	bool InOC(const VOI<UNIT> &voi, 
				 const Vector3d<typename UNIT::T_offset> &point)
	{ 
		return point.InOC(voi.offset, voi.offset + voi.size);
	}

	/** Is point inside VOI or on the left boundary? 
	\returns \p true if \p voi.offset <= point < voi.offset + voi.size. 
	\returns \p false otherwise. */
	template <class UNIT> inline 
	bool InCO(const VOI<UNIT> &voi, 
				 const Vector3d<typename UNIT::T_offset> &point)
	{ 
		return point.InCO(voi.offset, voi.offset + voi.size);
	}

	/** Is point inside VOI or on a boundary? 
	\returns \p true if \p voi.offset <= point <= voi.offset + voi.size. 
	\returns \p false otherwise. */
	template <class UNIT> inline 
	bool InCC(const VOI<UNIT> &voi, 
				 const Vector3d<typename UNIT::T_offset> &point)
	{ 
		return point.InCC(voi.offset, voi.offset + voi.size);
	}

} // i3d namespace

#endif
