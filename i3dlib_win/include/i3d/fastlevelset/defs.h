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

/*
 * defs.h
 *
 * Generic types and basic functions
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_DEFS_H
#define FLS_DEFS_H

#include <algorithm>
#include <cmath>
#include <limits>

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                       Generic Types                         //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/**********************************************************************/

		/** Generic types. */
		namespace Type
		{
			/** Floating-point precision type. */
			typedef float Prec;
			/** Size type. */
			typedef size_t Size;
			/** Binary voxel type. */
			typedef bool BinVoxel;
			/** Label voxel type. */
			typedef unsigned short LabVoxel;
		}

		/**********************************************************************/

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                       Basic Functions                       //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/**********************************************************************/

		/** Get the minimum of two given values. */
		template <class T> T Min(T x, T y)
		{
			return std::min(x, y);
		}

		/**********************************************************************/

		/** Get the maximum of two given values. */
		template <class T> T Max(T x, T y)
		{
			return std::max(x, y);
		}

		/**********************************************************************/

		/** Get the square of a given value. */
		template <class T> T Sqr(T val)
		{
			return val * val;
		}

		/**********************************************************************/

		/** Get the square root of a given value. */
		inline Type::Prec Sqrt(Type::Prec val)
		{
			return std::sqrt(val);
		}

		/**********************************************************************/

		/** Get the absolute value of a given value. */
		inline Type::Prec Abs(Type::Prec val)
		{
			return std::fabs(val);
		}

		/**********************************************************************/

		/** Get the maximal value of the Precision type. */
		inline Type::Prec Max()
		{
			return std::numeric_limits<Type::Prec>::max();
		}

		/**********************************************************************/

		/** Get the minimal value of the Precision type. */
		inline Type::Prec Min()
		{
			return -Max();
		}

		/**********************************************************************/

		/** Get the epsilon value of the Precision type. */
		inline Type::Prec Epsilon()
		{
			return std::numeric_limits<Type::Prec>::epsilon();
		}

		/**********************************************************************/

		/** Check whether a given value is positive. */
		inline bool Positive(Type::Prec val)
		{
			return (val >= Epsilon());
		}

		/**********************************************************************/
		
		/** Positive division of a given value. */
		inline Type::Prec PosDiv(Type::Prec val, Type::Prec div)
		{
			if (Positive(div))
			{
				return val / div;
			}
			else
			{
				return val / Epsilon();
			}
		}

		/**********************************************************************/

		/** Get the positive reciprocal of a given value. */
		inline Type::Prec PosReciproc(Type::Prec val)
		{
			return PosDiv(Type::Prec(1), Abs(val)); 
		}

		/**********************************************************************/

		/** Get the reciprocal of a given value. */
		inline Type::Prec Reciproc(Type::Prec val)
		{
			return Type::Prec(1) / val; 
		}

		/**********************************************************************/

	} // namespace fls 

} // namespace i3d

#endif // FLS_DEFS_H

