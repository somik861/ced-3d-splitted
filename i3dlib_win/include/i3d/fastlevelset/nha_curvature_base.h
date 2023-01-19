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
 * nha_curvature_base.h
 *
 * Base class intended for approximating the curvature in various versions of the Nilsson-Heyden algorithm
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_NHA_CURVATURE_BASE_H
#define FLS_NHA_CURVATURE_BASE_H

#include "nha_grid.h"
#include "nha_circular_neighbourhood.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                   Class NHA_CurvatureBase                   //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Base class intended for approximating the curvature in various versions of the Nilsson-Heyden algorithm for 2D grids. */
		class NHA_CurvatureBase
		{
			protected:
				/** Computational grid used in the Nilsson-Heyden algorithm. */
				NHA_Grid &m_grid;
				/** Pointer to the circular neighbourhood at which the curvature is approximated. */
				const NHA_CircularNeighbourhood *m_circular_neigh;

			public:
				/** Constructor. */
				NHA_CurvatureBase(NHA_Grid &grid, const NHA_CircularNeighbourhood *circular_neigh) : m_grid(grid), m_circular_neigh(circular_neigh) {};
				/** Destructor. */
				virtual ~NHA_CurvatureBase() { delete m_circular_neigh; };
				/** Increment the curvature in a circular neighbourhood of the i-th grid point. */
				void Increment(Type::Size i) { Update(i, 1); };
				/** Decrement the curvature in a circular neighbourhood of the i-th grid point. */
				void Decrement(Type::Size i) { Update(i, -1); };
				/** Estimate the curvature at the i-th grid point. */
				virtual void Estimate(Type::Size i);

			private:
				/** Update the curvature in a circular neighbourhood of the i-th grid point by given value. */
				virtual void Update(Type::Size i, int value);
		};

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                  Class NHA_CurvatureBase3D                  //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Base class intended for approximating the curvature in various versions of the Nilsson-Heyden algorithm for 3D grids. */
		class NHA_CurvatureBase3D : virtual public NHA_CurvatureBase
		{
			public:
				/** Constructor. */
				NHA_CurvatureBase3D(NHA_Grid &grid, const NHA_CircularNeighbourhood *circular_neigh) : NHA_CurvatureBase(grid, circular_neigh) {};
				/** Estimate the curvature at the i-th grid point. */
				virtual void Estimate(Type::Size i);
			
			private:
				/** Update the curvature in a circular neighbourhood of the i-th grid point by given value. */
				virtual void Update(Type::Size i, int value);
		};

	} // namespace fls

} // namespace i3d

#endif // FLS_NHA_CURVATURE_BASE_H

