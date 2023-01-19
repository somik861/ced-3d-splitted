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
 * grid_base.h
 *
 * Base computational domain for 2D as well as 3D routines
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_GRID_BASE_H
#define FLS_GRID_BASE_H

#include "defs.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                      Class GridBase                         //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Base computational domain for 2D as well as 3D routines. */
		class GridBase
		{
			public:
				/** Grid size in the x axis. */
				Type::Size m_sx;
				/** Grid size in the y axis. */
				Type::Size m_sy;
				/** Grid size in the z axis. */
				Type::Size m_sz;
				/** Number of grid points in the xy plane. */
				Type::Size m_slice;
				/** Number of grid points in the grid. */
				Type::Size m_size;
				/** Grid resolution in the x axis (in grid points per micron). */
				Type::Prec m_res_x;
				/** Grid resolution in the y axis (in grid points per micron). */
				Type::Prec m_res_y;
				/** Grid resolution in the z axis (in grid points per micron). */
				Type::Prec m_res_z;

			public:
				/** Constructor. */
				GridBase(Type::Size sx, Type::Size sy, Type::Size sz, Type::Prec res_x, Type::Prec res_y, Type::Prec res_z) 
					: m_sx(sx), m_sy(sy), m_sz(sz), m_slice(sx * sy), m_size(sx * sy * sz), m_res_x(res_x), m_res_y(res_y), m_res_z(res_z){};
				/** Destructor. */
				virtual ~GridBase() {};
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_GRID_BASE_H

