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
 * nha_curvature.h
 *
 * Curvature used in the Nilsson-Heyden algorithm
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_NHA_CURVATURE_H
#define FLS_NHA_CURVATURE_H

#include "nha_curvature_base.h"
#include "speed_function.h"
#include "heap.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                     Class NHA_Curvature                     //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Curvature used in the Nilsson-Heyden algorithm for 2D grids. */
		class NHA_Curvature : virtual public NHA_CurvatureBase
		{
			protected:
				/** Pointer to the SpeedFunction object. */
				const SpeedFunction *m_speed_function;
				/** Min-heap data structure. */
				MinHeap<Type::Prec, NHA_Node> &m_heap;

			public:
				/** Constructor. */
				NHA_Curvature(NHA_Grid &grid, const NHA_CircularNeighbourhood *circular_neigh, const SpeedFunction *speed_function, MinHeap<Type::Prec, NHA_Node> &heap) 
					: NHA_CurvatureBase(grid, circular_neigh), m_speed_function(speed_function), m_heap(heap) {};

			private:
				/** Update the curvature in a circular neighbourhood of the i-th grid point by given value. */
				virtual void Update(Type::Size i, int value);
		};

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                    Class NHA_Curvature3D                    //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Curvature used in the Nilsson-Heyden algorithm for 3D grids. */
		class NHA_Curvature3D : public NHA_Curvature, public NHA_CurvatureBase3D
		{
			public:
				/** Constructor. */
				NHA_Curvature3D(NHA_Grid &grid, const NHA_CircularNeighbourhood *circular_neigh, const SpeedFunction *speed_function, MinHeap<Type::Prec, NHA_Node> &heap) 
					: NHA_CurvatureBase(grid, circular_neigh), NHA_Curvature(grid, circular_neigh, speed_function, heap), NHA_CurvatureBase3D(grid, circular_neigh) {};
				/** Estimate the curvature at the i-th grid point. */
				//HELP remove me when the warning C4250 is no longer invoked
				virtual void Estimate(Type::Size i) { NHA_CurvatureBase3D::Estimate(i); };

			private:
				/** Update the curvature in a circular neighbourhood of the i-th grid point by given value. */
				virtual void Update(Type::Size i, int value);
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_NHA_CURVATURE_H

