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

/** \file  basic.h  
  \brief Basic types and macros - header. 

  This file is included in every file in i3dlib, therefore it is a good place for 
  the declaration of symbols that are needed in all files. However, think twice whether 
  it is really needed before you put something in.

  It is intended for the declarations of some macros that are needed for cross-platform 
  compilation. It also contains, for historical reasons, basic voxel types supported in i3dlib 
  (i3d::GRAY8, i3d::GRAY16, i3d::RGB, i3d::RGB16, ...) and exceptions that are 
  raised by the library (i3d::InternalException and i3d::IOException). 

  One of the most important macros is I3D_ALGO_EXPORT (in the context of the algorithm library) that is put
  before all symbols exported from the library. It is needed for creating and using a dynamic
  library on MS Windows. It is defined blank on other platforms or if dll library is not being 
  built and/or used. The I3D_CORE_EXPORT acts similarily for the core library.

  \todo Move voxel types and exceptions to own files.
  \version $Id: basic.h,v 1.5 2009/02/02 08:52:26 david Exp $

  \author Petr Mejzlík (mejzlik@fi.muni.cz) 2000
  \author Petr Matula (pem@fi.muni.cz), 2001

*/
#ifndef __BASIC_H__
#define __BASIC_H__

#include <string>
#include <iostream>
#include <limits>
#include <complex>
#include <limits.h>
#include <algorithm>

#include "i3d_config.h"

/***************************************************************************\
*
*                            Macro definitions
*
\***************************************************************************/

//--------------------------------------------------------------------------
// Macros for making or using i3dcore as a DLL
//--------------------------------------------------------------------------
#if defined(_MSC_VER) // MSVC.NET compiler
#	if defined(I3D_CORE_SHOULD_EXPORT) // export symbols (when creating shared library)
#		define I3D_CORE_EXPORT __declspec(dllexport)
#		define I3D_CORE_EXPORT_DATA(type) __declspec(dllexport) type
#	else // import symbols (when using library)
#		define I3D_CORE_EXPORT __declspec(dllimport)
#		define I3D_CORE_EXPORT_DATA(type) __declspec(dllimport) type
#	endif
#else // compiler doesn't support __declspec(), e.g. Linux gcc
#	define I3D_CORE_EXPORT
#	define I3D_CORE_EXPORT_DATA(type) type
#endif

//--------------------------------------------------------------------------
// Undefine some harmful macros
//--------------------------------------------------------------------------
#ifdef RGB
#	undef RGB
#endif

//--------------------------------------------------------------------------
// Define macros or functions missing on some platforms
//--------------------------------------------------------------------------
#ifdef _MSC_VER
#	ifndef M_PI
#		define M_PI 3.1419526535
#	endif
#endif

//--------------------------------------------------------------------------
// Other macros
//--------------------------------------------------------------------------
#ifdef __KCC
#	define restrict restrict
#else
#	define restrict
#endif



/***************************************************************************\
*
*                           Basic voxel types
*
\***************************************************************************/
namespace i3d {

#if CHAR_BIT == 8
	typedef unsigned char byte;
	typedef unsigned short word;
#endif

	//--------------------------------------------------------------------------
	// GRAY8
	//--------------------------------------------------------------------------
	/** 8-bit unsigned grayscale type. 
	This type is intended for 8-bit unsigned grayscale 
	images with range [0..255]. 
	*/
	typedef byte GRAY8;


	//--------------------------------------------------------------------------
	// GRAY16
	//--------------------------------------------------------------------------
	/** 16-bit unsigned grayscale type. 
	This type is intended for 16-bit unsigned grayscale  
	images with range [0..65535]. 
	*/
	typedef unsigned short GRAY16;

	//--------------------------------------------------------------------------
	// RGB template
	//--------------------------------------------------------------------------
	/** Generic RGB type.
	This template is a generic RGB type that has three components of type T (red, 
	green, and blue). All RGB types in the library use this template.

	\todo Rename this class to RGB and current RGB class to RGB8. 
	*/
	template <class T>
	struct I3D_CORE_EXPORT RGB_generic
	{
		/** Data type of each component. */
		typedef T ELEMENT_TYPE;

		/** Red component. */
		ELEMENT_TYPE red;
		/** Green component. */
		ELEMENT_TYPE green;
		/** Blue component. */
		ELEMENT_TYPE blue;

		/** Default constructor. */
		RGB_generic()
			: red(0), green(0), blue(0)	
		{};

		/** Constructor. 
		This constructor initializes all components to the same value \p v. */
		RGB_generic(const T &v)
			: red(v), green(v), blue(v)	
		{};

		template <class S> RGB_generic(const S &v)
			  : red(T(v)), green(T(v)), blue(T(v))
		{};

		/** Constructor. 
		This constructor initializes RGB type with the given component values. */
		RGB_generic(const T &r, const T &g, const T &b)
			: red(r), green(g), blue(b)	
		{};

		/** Addition operator.  
		It adds value \p rgb to the class component-wise. */
		RGB_generic<T>& operator+= (const RGB_generic<T> &rgb) {
			red   += rgb.red;
			green += rgb.green;
			blue  += rgb.blue;
			return *this;
		};

		/** Subtraction operator.  
		It subtracts value \p rgb from the class component-wise. */
		RGB_generic<T>& operator-= (const RGB_generic<T> &rgb) {
			red   -= rgb.red;
			green -= rgb.green;
			blue  -= rgb.blue;
			return *this;
		};

		/** Return component value. */
		T GetComponent(int i);

		/** Conversion operator from RGB to GRAY. 
		It combines the RGB values according to NTCS standard. */
		operator T () const { return T(.2989 * red + .5870 * green + .1141 * blue); };
	}; // RGB_generic

	/** Equality operator. 
	\returns \a true if all three components are the same, \a false otherwise
	*/
	template <class T> inline bool operator== (
		const RGB_generic<T> & x, 
		const RGB_generic<T> & y
		) {
			return (x.red == y.red && x.green == y.green && x.blue == y.blue);
		};

	/** Inequality operator. 
	\returns \a true if at least one component in \a x differs from the 
	corresponding component in \a y, \a false otherwise
	*/
	template <class T> inline bool operator!= (
		const RGB_generic<T> & x, 
		const RGB_generic<T> & y
		) {
			return (x.red != y.red || x.green != y.green || x.blue != y.blue);
		};

	/** Sumation operator.  
	Sums two RGB values. */
	template <class T> RGB_generic<T> operator+ (
		const RGB_generic<T> &x, 
		const RGB_generic<T> &y
		) {
			RGB_generic<T> result = x;
			result += y;
			return result;
		};

	/** Subtraction operator.  
	Subtracts two RGB values. */
	template <class T> RGB_generic<T> operator- (
		const RGB_generic<T> &x, 
		const RGB_generic<T> &y
		) {
			RGB_generic<T> result = x;
			result -= y;
			return result;
		};

	/** Comparison operators.
	Compares two RGB values component-wise. */
	template <class T> inline bool operator< (
		const RGB_generic<T> &x, 
		const RGB_generic<T> &y
		) {
			return (x.red < y.red || x.green < y.green || x.blue < y.blue);
		};

	template <class T> inline bool operator<= (
		const RGB_generic<T> &x, 
		const RGB_generic<T> &y
		) {
			return (x.red <= y.red || x.green <= y.green || x.blue <= y.blue);
		};

	template <class T> inline bool operator> (
		const RGB_generic<T> &x, 
		const RGB_generic<T> &y
		) {
			return (x.red > y.red || x.green > y.green || x.blue > y.blue);
		};

	template <class T> inline bool operator>= (
		const RGB_generic<T> &x, 
		const RGB_generic<T> &y
		) {
			return (x.red >= y.red || x.green >= y.green || x.blue >= y.blue);
		};

	/** Minimum operator. */
	template <class T> inline RGB_generic<T> min(
		const RGB_generic<T> &x, 
		const RGB_generic<T> &y
		) {
			return RGB_generic<T>(std::min(x.red, y.red), std::min(x.green, y.green), std::min(x.blue, y.blue));
		};

	/** Maximum operator. */
	template <class T> inline RGB_generic<T> max(
		const RGB_generic<T> &x, 
		const RGB_generic<T> &y
		) {
			return RGB_generic<T>(std::max(x.red, y.red), std::max(x.green, y.green), std::max(x.blue, y.blue));
		};

	//--------------------------------------------------------------------------
	// Specific RGB types
	//--------------------------------------------------------------------------
	/** RGB type with 8-bit components.
	This type is intended for unsigned 24-bit RGB images, i.e. with 8-bit components. 
	*/
	typedef RGB_generic<GRAY8> RGB;

	/** RGB type with 16-bit components.
	This type is intended for unsigned 48-bit RGB images, i.e. with 16-bit components.
	*/
	typedef RGB_generic<GRAY16> RGB16;


	//--------------------------------------------------------------------------
	// VOI basic types
	//--------------------------------------------------------------------------
	/**
	 * This is an VOI internal structure. It serves the purpose to wrap information about
	 * VOI's offset and size types.
	 */
	template <class T1, class T2> struct T_pair
	{
		 typedef T1 T_offset;
		 typedef T2 T_size;
	};

	/**
	 * These are two preferred VOI basic types for integer coordinates and sizes.
	 * It forces the compiler to warn when one uses signed type for size element of VOI type.
	 */
	typedef T_pair<int, size_t> PIXELS;
	typedef T_pair<size_t, size_t> UPIXELS;

	/// This is a preferred VOI basic type for real-valued coordinates and sizes.
	typedef T_pair<float, float> MICRONS;


	//--------------------------------------------------------------------------
	// Functions handling voxel types
	//--------------------------------------------------------------------------
	/** Color inversion.
	This template does color inversion (complementation) of the input value. 
	Maximal value of the datatype is used for the complementation. 

	\todo fix color inversion of RGB types. Current implementation rely on a functional 
	numeric_limits< RGB<T> > that are, however, not currently available.
	*/
	template <class T> I3D_CORE_EXPORT T ColorInversion(const T &v);


	/** A type-safe square function. */
	template <class T> inline T Sqr(T value)
	{
		return value * value;
	}

	/***************************************************************************\
	*
	*                                 Exceptions
	*
	\***************************************************************************/
	//--------------------------------------------------------------------------
	// Classes
	//--------------------------------------------------------------------------
	/** Generic exception class. 
	This is a base class of all exceptions raised by functions in %i3d library. It contains 
	attribute \c what of type \c std::string, which holds more information about the problem 
	that caused the exception.
	*/
	class I3D_CORE_EXPORT LibException {
	public:
		/** Message string. */
		std::string what;

		/** Constructor. It initializes the message string.  */
		LibException(std::string s = ""): what(s) {}
	};

	/** IO Exception. 	
	This exception is typically raised on exceptional situations in 
	I/O functions. \sa LibException.
	*/
	class I3D_CORE_EXPORT IOException: public LibException {
	public: 
		/** Constructor. 
		It sets the message string. */
		IOException(std::string s = ""): LibException(s) {}
	};

	/** Internal exception. 
	This class is raised on internal errors of the library. They typically happen
	if a library function or a template is misused (bad parameters, bad instantiation, etc.).
	\sa LibException
	*/
	class I3D_CORE_EXPORT InternalException: public LibException {
	public: 
		/** Constructor. 
		It sets the message string. */
		InternalException(std::string s = ""): LibException(s) {}
	};

	//--------------------------------------------------------------------------
	// Output operators
	//--------------------------------------------------------------------------
	/** Output operator for IOException. 
	It writes information about the exception \p e into the	output stream \p o. 
	\returns The modified stream. */
	I3D_CORE_EXPORT std::ostream& operator<<(std::ostream& o, const IOException& e);

	/** Output operator for InternalException. 
	It writes information about the exception \p e into the	output stream \p o. 
	\returns The modified stream. */
	I3D_CORE_EXPORT std::ostream& operator<<(std::ostream& o, const InternalException& e);
} // i3d namespace

#endif // __BASIC_H__
