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

/** \file toolbox.h
	\brief General purpose functions - header.
 
	The intended purpose of this file is to provide several useful (often
	simple) functions of general use that can slightly simplify programming. 

	\todo 
 
	\author Petr Mejzlík (mejzlik@fi.muni.cz) 2000
	\author Petr Matula (pem@fi.muni.cz) 2001 - added functions: Trim, BeforeLast, AfterLast, 
	GetExtension, GetPath, SplitFilename, num_digits, cmp_nocase

 */
#ifndef __TOOLBOX_H__
#define __TOOLBOX_H__

#ifdef __GNUG__
#pragma interface
#endif

#include <string>
#include <vector>
#include <iostream>

#include "basic.h"
#include "imgfiles.h"


namespace i3d {
	/***************************************************************************\
	*
	*                           String related functions
	*
	\***************************************************************************/
	/** Int to string conversion. 
	Write integer value to a string. */
	I3D_CORE_EXPORT std::string itos(int n);

	/** String to int conversion. 
	Convert string to an integer value. \returns \p true on success*/
	I3D_CORE_EXPORT bool StrToInt (const std::string & s, int &i);
	
	/** String to float conversion.
	Convert string to a float value. \returns \p true on success*/
	I3D_CORE_EXPORT bool StrToFloat (const std::string & s, float &f);

	/** Split a string to the vector of tokens. */
	I3D_CORE_EXPORT void Tokenize (
		const std::string & str, 
		std::vector < std::string > &tokens, 
		const std::string & delimiters = " "
		);

	/** \returns string without leading and tailing whitespaces */
	I3D_CORE_EXPORT std::string Trim(const std::string &s);

	/** \returns string after last occurence of \p sep. If \p sep is not found, "" is returned*/
	I3D_CORE_EXPORT std::string AfterLast(const std::string &s, char sep);

	/** \returns string before last occurence of \p sep. If \p sep is not found, "" is returned */
	I3D_CORE_EXPORT std::string BeforeLast(const std::string &s, char sep);

	/** No case string comparison. 
	\returns -1 if \p s1 < \p s2
	\returns 1 if \p s1 > \p s2
	\returns 0 if \p s1 == \p s2.*/
	I3D_CORE_EXPORT int cmp_nocase(const std::string &s1, const std::string &s2);

	/** \returns number of digits of \p number in specified base
	if number==0 then 1 is returned */
	template <class T> I3D_CORE_EXPORT size_t num_digits(T number, int base = 10);

	/** \return the given number formatted in human readable code */
	I3D_CORE_EXPORT std::string human_readable (double number, unsigned precision = 2);

	/** \return the given number formatted in human readable code */
	I3D_CORE_EXPORT std::string human_readable (unsigned long long number);

	/**************************************************************************\
	*
	*                   File and directory related functions
	*
	\**************************************************************************/
	/** Returns the extension of given filename */
	I3D_CORE_EXPORT void GetExtension(const std::string &fn, std::string &ext);

	/** Returns the path part of given filename - i.e. the string before and including 
        the last slash. Both types of slashes are accepted as path deliminators. */
	I3D_CORE_EXPORT void GetPath(const std::string &fn, std::string &path);

	/** Splits filename fn using functions above, name is string between
	last dot and last slash */
	I3D_CORE_EXPORT void SplitFilename(
		const std::string &fn, 
		std::string &path, 
		std::string &name, 
		std::string &ext);

	/** Get current working directory. 
	\throws IOException if there is a problem.  */
	I3D_CORE_EXPORT std::string GetDir();

	/** Set working directory */
	I3D_CORE_EXPORT void SetDir(const char* dir);

	/** \todo Documentation */
	I3D_CORE_EXPORT size_t MaskExpand(
		const char *mask, 
		FileList &namelist, 
		bool expand = true);


	/**************************************************************************\
	*
	*                           Stream functions
	*
	\**************************************************************************/
	/** Set a stream to throw ios::failure after an unsuccessful IO operation. */
	I3D_CORE_EXPORT void SetBadIOException(std::ios& io);

	/** Read 4 bytes in least-significant byte first order into a long. */
	I3D_CORE_EXPORT unsigned long LSBFirstReadLong(std::istream& file);

	/** Write a long value as 4 bytes in the least-significant byte first order. */
	I3D_CORE_EXPORT void LSBFirstWriteLong(std::ostream& file, unsigned long value);

	/** Read 2 bytes in least-significant byte first order into a short int. */
	I3D_CORE_EXPORT unsigned short LSBFirstReadShort(std::istream& file);

	/** Write a short int as 2 bytes in least-significant byte first order. */
	I3D_CORE_EXPORT void LSBFirstWriteShort(std::ostream& file, unsigned short value);

	/**************************************************************************\
	*
	*                   CPU management
	*
	\**************************************************************************/
	/** The function returns the number of available processros/cores. */
	I3D_CORE_EXPORT size_t GetNumberOfProcessors();

	/**************************************************************************\
	*
	*                   Memory management
	*
	\**************************************************************************/
	/** The function returns the amount of all available memory. */
	I3D_CORE_EXPORT unsigned long long GetFreeMemory();
	
	/** The function returns the amount of all physical memory (RAM). */
	I3D_CORE_EXPORT unsigned long long GetTotalMemory();

	/**************************************************************************\
	*
	*                            Conversion functions
	*
	\**************************************************************************/
	/** Convert 4 bytes in least-significant byte first order into a long int. */
	I3D_CORE_EXPORT unsigned long LSBFirstToLong(byte buf[4]);

	/** Convert a long int into 4 bytes in least-significant byte first order. */
	I3D_CORE_EXPORT void LongToLSBFirst(byte buf[4], unsigned long value);

	/** Convert 2 bytes in least-significant byte first order into a short int. */
	I3D_CORE_EXPORT unsigned short LSBFirstToShort(byte buf[2]);

	/** Convert a short int into 2 bytes in least-significant byte first order. */
	I3D_CORE_EXPORT void ShortToLSBFirst(byte buf[2], unsigned short value);

	/** Convert a voxel value of a type T1 to a type T2. The conversion is performed without any checks.*/
	template <class T1, class T2> class I3D_CORE_EXPORT VoxelConversion
	{
		public:
			static T2 Convert(T1 src) { return static_cast<T2>(src); };
	};

	/** Partial specialization of the base VoxelConversion class intended for the binary output type. */
	template <class T1> class I3D_CORE_EXPORT VoxelConversion<T1, bool>
	{
		public:
			static bool Convert(T1 src) { return (src > static_cast<T1>(0)); };
	};

	/**************************************************************************\
	*
	*                         Container related functions
	*
	\**************************************************************************/
	/** Normalization of containers. 
	This template divides values between iterators \p first (included) and \p last 
	(excluded) by the sum of all values between these iterators. */
	template <typename ITERATOR> inline
		void normalize(ITERATOR first, ITERATOR last)
	{
		long double sum=0.0;
		ITERATOR it;

		for (it=first; it<last; it++)
			sum += *it;

		for (it=first; it<last; it++)
			*it /= sum;
	}

	/** Normalization of containers. 
	It is equivalent to normalize(first, first + count). */
	template <typename ITERATOR> inline
		void normalize(ITERATOR first, const long int count)
	{
		normalize(first, first+count);
	}
	
	/**************************************************************************\
	*
	*                  Image data organization related functions
	*
	\**************************************************************************/
	/** Changes the order of lines in the memory. */
	template < class T > I3D_CORE_EXPORT 
	void SwapVert (size_t width, size_t height, T * data);

	/** Changes the order of columns in the memory. */
	template < class T > I3D_CORE_EXPORT 
	void SwapHoriz (size_t width, size_t height, T * data);

	/** Reversing colors in image */
	template <class T> I3D_CORE_EXPORT 
	void ReverseColors(size_t width, size_t height, T *data);

	/**************************************************************************\
	*
	*                 Eigenvalue decomposition related functions
	*
	\**************************************************************************/
	/** Find the dominant eigenvalue of a 2x2 symmetric matrix M = [a b; b c]. */
	template <class T> I3D_CORE_EXPORT T DominantEigenValue(T a, T b, T c);

	/** Find the dominant eigenvalue of a 3x3 symmetric matrix M = [a b c; b d e; c e f]. */
	template <class T> I3D_CORE_EXPORT T DominantEigenValue(T a, T b, T c, T d, T e, T f);

} // i3d namespace

#endif
