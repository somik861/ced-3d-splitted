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

/** \file vector3d.h
	\brief 3D vector representation - header

	This file defines a struct of three-component vector. This can be used 
	for representation of 3D vectors as well as 3D points. 

	i3dlib contains also similar class Point3d in points.h, which was added to 
	the library	slightly later. 

	\todo Check properties of Vector3d and Point3d classes and try to unify them 
	somehow. The goal is to have only one 3D point/vector class.

	\todo Better layout out of vector3d.h and vector3d.cc

	\author Petr Matula (pem@fi.muni.cz) 2001, 
	\author Petr Mejzlík (mejzlik@fi.muni.cz) 2001
 */

#ifndef __VECTOR3D_H__
#define __VECTOR3D_H__

#include <iostream>
#include <stdlib.h>
#ifndef _MSC_VER
#include <cmath>
#endif
#include <valarray>
#include "basic.h"

#ifdef HAVE_SSTREAM
#include <sstream>
#else
#include <strstream>
#define istringstream istrstream
#endif

#ifdef __GNUG__
#pragma interface
#include <typeinfo>
#endif


namespace i3d 
{
	/** General structure for 3D coordinations manipulation */
	template <class T> struct I3D_CORE_EXPORT Vector3d {
	public:

		/// the particular coordinates
		T x, y, z;

		/// constructor
		Vector3d(T val = 0): x(val),y(val),z(val) {};

		/// constructor
		Vector3d(T x_ , T y_ , T z_)
			: x(x_), y(y_), z(z_) {}

		~Vector3d() {}

		/// conversion constructor
		template <class T2> Vector3d(const Vector3d<T2>& v)
			: x(static_cast<T>(v.x)),y(static_cast<T>(v.y)),z(static_cast<T>(v.z)) {}

		/// left addition  
		Vector3d<T> &operator+= (const Vector3d<T>& v);

		/// left subtraction
		Vector3d<T> &operator-= (const Vector3d<T>& v);

		/// left multiplication by another vector
		Vector3d<T> &operator*= (const Vector3d<T>& v);

		/// left division by another vector
		Vector3d<T> &operator/= (const Vector3d<T>& v);

		/// left multiplication by scalar
		Vector3d<T> &operator*= (const T& s) { x *= s; y *= s; z *= s;return *this;};

		/// left division by scalar
		Vector3d<T> &operator/= (const T& s) { x /= s; y /= s; z /= s;return *this;};

		/// unary minus = negate
		Vector3d<T> operator-() const { return Vector3d<T>(-x,-y,-z); }

		/// is the vector in the interval [a,b)?
		bool InCO(const Vector3d<T>& a, const Vector3d<T>& b) const {
			return (a.x <= x && a.y <= y && a.z <= z &&
				b.x >  x && b.y >  y && b.z >  z);
		}

		/// is the vector in the interval (a,b)?
		bool InOO(const Vector3d<T>& a, const Vector3d<T>& b) const {
			return (a.x < x && a.y < y && a.z < z &&
				b.x >  x && b.y >  y && b.z >  z);
		}

		/// is the vector in the interval (a,b]?
		bool InOC(const Vector3d<T>& a, const Vector3d<T>& b) const {
			return (a.x < x && a.y < y && a.z < z &&
				b.x >=  x && b.y >=  y && b.z >=  z);
		}

		/// is the vector in the interval [a,b]?
		bool InCC(const Vector3d<T>& a, const Vector3d<T>& b) const {
			return (a.x <= x && a.y <= y && a.z <= z &&
				b.x >=  x && b.y >=  y && b.z >=  z);
		}

		T& operator [] (size_t i)
		{ 
			switch(i) {
			case 0: return(this->x);
			case 1: return(this->y);
			case 2: return(this->z);
			default: throw InternalException("Accessing n-th member of Vector3d where n is not either 0,1 or 2!");
			}
			/* original code
			if (i < 3)
			{ 
				return  *(((T*) (this))+i);
			}
			else
			{
				throw InternalException("Accessing the n-th member of Vector3d "
												"and n is greater than 3!");
			}
			*/
		}

		const T& operator [] (size_t i) const { 
			switch(i) {
			case 0: return(this->x);
			case 1: return(this->y);
			case 2: return(this->z);
			default: throw InternalException("Accessing n-th member of Vector3d where n is not either 0,1 or 2!");
			}
		}
	};

	/// Euclidean norm:
	template <class T> T Norm(const Vector3d<T>& v) {return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);}

	/// Square of euclidean norm
	template <class T> T Norm2(const Vector3d<T>& v) {return v.x*v.x + v.y*v.y + v.z*v.z;}

	/// Dot product
	template <class T> T Dot(const Vector3d<T>& u, const Vector3d<T> &v) { return u.x*v.x + u.y*v.y + u.z*v.z; }

	/// Cross product
	template <class T> Vector3d<T> Cross(const Vector3d<T>& u, const Vector3d<T> &v) 
	{ 
		 return Vector3d<T>(u.y*v.z - u.z*v.y,
								  u.z*v.x - u.x*v.z,
								  u.x*v.y - u.y*v.x);
	}

	/// minimum
	template <class T> Vector3d<T> max(const Vector3d<T> &v1,
		const Vector3d<T> &v2) {
			return Vector3d<T>( std::max(v1.x,v2.x),
				std::max(v1.y,v2.y),
				std::max(v1.z,v2.z)); }

	/// maximum
	template <class T> Vector3d<T> min(const Vector3d<T> &v1,
		const Vector3d<T> &v2) {
			return Vector3d<T>(	std::min(v1.x,v2.x),
				std::min(v1.y,v2.y),
				std::min(v1.z,v2.z)); }

	// arithmetic operations with vectors

	template <class T> inline Vector3d<T> operator+ (const Vector3d<T>& v1,
		const Vector3d<T>& v2) {
			Vector3d<T> v = v1; v += v2; return v; }
	template <class T> inline Vector3d<T> operator- (const Vector3d<T>& v1,
		const Vector3d<T>& v2) {
			Vector3d<T> v = v1; v -= v2; return v; }
	template <class T> inline Vector3d<T> operator* (const Vector3d<T>& v1,
		const Vector3d<T>& v2) {
			Vector3d<T> v = v1; v *= v2; return v; }
	template <class T> inline Vector3d<T> operator/ (const Vector3d<T>& v1,
		const Vector3d<T>& v2) {
			Vector3d<T> v = v1; v /= v2; return v; }

	// arithmetic operations with scalars
	template <class T> inline Vector3d<T> operator+ (const Vector3d<T>& v, T s) {
		return Vector3d<T>(v.x + s, v.y + s, v.z + s); }
	template <class T> inline Vector3d<T> operator- (const Vector3d<T>& v, T s) {
		return Vector3d<T>(v.x - s, v.y - s, v.z - s); }
	template <class T> inline Vector3d<T> operator* (const Vector3d<T>& v, T s) {
		return Vector3d<T>(v.x * s, v.y * s, v.z * s); }
	template <class T> inline Vector3d<T> operator/ (const Vector3d<T>& v, T s) {
		return Vector3d<T>(v.x / s, v.y / s, v.z / s); }
	template <class T> inline Vector3d<T> operator+ (T s, const Vector3d<T>& v) {
		return Vector3d<T>(s + v.x, s + v.y, s + v.z); }
	template <class T> inline Vector3d<T> operator- (T s, const Vector3d<T>& v) {
		return Vector3d<T>(s - v.x, s - v.y, s - v.z); }
	template <class T> inline Vector3d<T> operator* (T s, const Vector3d<T>& v) {
		return Vector3d<T>(s * v.x, s * v.y, s * v.z); }
	template <class T> inline Vector3d<T> operator/ (T s, const Vector3d<T>& v) {
		return Vector3d<T>(s / v.x, s / v.y, s / v.z); }

	/**
 	* Addition for the case when offset to an opposite corner of some VOI is required.
 	*
 	* That is when voi_variable<PIXELS>.offset + voi_variable<PIXELS>.size needs to be evaluated.
 	*
 	* The other way round is to convert both i3d::PIXELS::T_offset and T_size, which are infact
 	* i3d::vectord3d<int> and i3d::vector3d<size_t>, to i3d::MICRONS::T_offset and T_size, respectively,
	* using fixed resolution and pixel to microns conversion helper functions.
 	* They shall become i3d::vector3d<float> afterwards, sum them and convert the result back to PIXELS::T_offset.
 	*/
	inline Vector3d<PIXELS::T_offset> operator+ (const Vector3d<PIXELS::T_offset>& v1,
		const Vector3d<PIXELS::T_size>& v2) {
			return( Vector3d<PIXELS::T_offset>(v1.x + static_cast<PIXELS::T_offset>(v2.x),
						   	v1.y + static_cast<PIXELS::T_offset>(v2.y),
						   	v1.z + static_cast<PIXELS::T_offset>(v2.z)) );
	}

	// output/input from stream 
	template <class T> I3D_CORE_EXPORT std::ostream& operator<< (std::ostream& os,
		const Vector3d<T> &v);
	template <class T> I3D_CORE_EXPORT std::istream& operator>> (std::istream& is,
		Vector3d<T> &v);

	template <class T> inline Vector3d<T> abs(const Vector3d<T> &v) {
		return Vector3d<T>(::abs(v.x), ::abs(v.y), ::abs(v.z));
	}

	// comparations 
	template <class T> inline bool operator== (const Vector3d<T>& v1,
		const Vector3d<T>& v2) {
			return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);
	}
	template <class T> inline bool operator!= (const Vector3d<T>& v1,
		const Vector3d<T>& v2) {
			return (v1.x != v2.x) || (v1.y != v2.y) || (v1.z != v2.z);
	}

	// Lexicografical ordering
	template <class T> inline bool operator> (const Vector3d<T>& v1,
		const Vector3d<T>& v2)
	{
		return ((v1.x > v2.x) ||
			(v1.x == v2.x && v1.y > v2.y) ||
			(v1.x == v2.x && v1.y == v2.y && v1.z > v2.z));
	}

	template <class T> inline bool operator< (const Vector3d<T>& v1,
		const Vector3d<T>& v2)
	{
		return ((v1.x < v2.x) ||
			(v1.x == v2.x && v1.y < v2.y) ||
			(v1.x == v2.x && v1.y == v2.y && v1.z < v2.z));
	}

	/// Element-by-element partial ordering:
	template <class T> inline bool le(const Vector3d<T>& v1, const Vector3d<T>& v2)
	{
		return (v1.x <= v2.x && v1.y <= v2.y && v1.z <= v2.z);
	}


	/** Convert char * to Vector3d, returns true on success */  
	template <class T> inline bool StrToVector3d(const char *from, Vector3d<T> &v)
	{
		std::istringstream is(from);
		is >> v;
		return is.good();
	}

	/* Gets reference to x,y,z component of vector v according to
	type of the first parameter
	e.g. GetRef<_X_>(v) is same as v.x (useful when using templates)
	*/
	class I3D_CORE_EXPORT _X_ {};
	class I3D_CORE_EXPORT _Y_ {};
	class I3D_CORE_EXPORT _Z_ {};

	template <class C, class T> inline T& GetRef(Vector3d<T> &v)
	{
		if (typeid(C) == typeid(_X_))
			return v.x;
		else if (typeid(C) == typeid(_Y_))
			return v.y;
		else if (typeid(C) == typeid(_Z_))
			return v.z;
		else
			throw InternalException("Unknown component");
	}

	template <class C, class T> inline T GetComp(const Vector3d<T> &v)
	{
		if (typeid(C) == typeid(_X_))
			return v.x;
		else if (typeid(C) == typeid(_Y_))
			return v.y;
		else if (typeid(C) == typeid(_Z_))
			return v.z;
		else
			throw InternalException("Unknown component");
	}

	/// data type representing real coordinates (with floating point)
	typedef Vector3d<float> Offset;

	/// data type representing coordinates without floating point
	typedef Vector3d<int> Coords;
}

#endif
