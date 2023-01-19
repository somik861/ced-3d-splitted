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
 * nha_circular_neighbourhood.h
 *
 * Circular neighbourhood used in the Nilsson-Heyden algorithm for approximating the curvature
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_NHA_CIRCULAR_NEIGHBOURHOOD_H
#define FLS_NHA_CIRCULAR_NEIGHBOURHOOD_H

#include "grid_base.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//               Class NHA_CircularNeighbourhood               //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Circular neighbourhood used in the Nilsson-Heyden algorithm for approximating the curvature. */
		class NHA_CircularNeighbourhood
		{
			protected:
				/** Computational grid. */
				const GridBase &m_grid;
				/** Radius of a circular neighbourhood in the x axis with respect to the grid resolution. */
				Type::Size m_radius_x;
				/** Radius of a circular neighbourhood in the y axis with respect to the grid resolution. */
				Type::Size m_radius_y;
				/** Radius of a circular neighbourhood in the z axis with respect to the grid resolution. */
				Type::Size m_radius_z;

			public:
				/** Constructor. The radius in each axis is adapted to the grid resolution. */
				NHA_CircularNeighbourhood(const GridBase &grid, Type::Size radius);
				/** Destructor. */
				virtual ~NHA_CircularNeighbourhood() {};
				/** Get the size of the circular neighbourhood. */
				Type::Size Size() const { return (2 * m_radius_x + 1) * (2 * m_radius_y + 1) * (2 * m_radius_z + 1); };
				/** Get the reciprocal size of the circular neighbourhood. */
				Type::Prec ReciprocSize() const { return Reciproc(Type::Prec(Size())); };
				/** Get limits of the circular neighbourhood in the x axis for the i-th grid point. */
				void LimitsX(Type::Size i, Type::Size &min, Type::Size &max) const;
				/** Get limits of the circular neighbourhood in the y axis for the i-th grid point. */
				void LimitsY(Type::Size i, Type::Size &min, Type::Size &max) const;
				/** Get limits of the circular neighbourhood in the z axis for the i-th grid point. */
				void LimitsZ(Type::Size i, Type::Size &min, Type::Size &max) const;
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_NHA_CIRCULAR_NEIGHBOURHOOD_H

