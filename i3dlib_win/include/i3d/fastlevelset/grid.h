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
 * grid.h
 *
 * Grid - computational domain for 2D as well as 3D routines
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_GRID_H
#define FLS_GRID_H

#include "grid_base.h"
#include "buffer.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                        Class Grid                           //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Grid - computational domain for 2D as well as 3D routines. 
		  * It stores the implicit function over which every routine performs its computation. */
		template <class T> class Grid : public GridBase
		{
			public:
				/** Buffer intended for storing the implicit function. */
				Buffer<T> m_implicit_function;

			public:
				/** Constructor. */
				Grid(Type::Size sx, Type::Size sy, Type::Size sz, Type::Prec res_x, Type::Prec res_y, Type::Prec res_z, T def_val) 
					: GridBase(sx, sy, sz, res_x, res_y, res_z), m_implicit_function(def_val, sx * sy * sz) {};
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_GRID_H

