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
 * lab_reg_nha_curvature.h
 *
 * Curvature used in the labelled versions of the Nilsson-Heyden algorithm
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_LAB_NHA_CURVATURE_H
#define FLS_LAB_NHA_CURVATURE_H

#include "nha_curvature_base.h"

namespace i3d 
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                   Class Lab_NHA_Curvature                   //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Curvature used in the labelled versions of the Nilsson-Heyden algorithm for 2D grids. */
		class Lab_NHA_Curvature : public NHA_CurvatureBase
		{
			protected:
				/** Buffer intended for storing labels. */
				const Buffer<Type::LabVoxel> &m_labels;

			public:
				/** Constructor. */
				Lab_NHA_Curvature(NHA_Grid &grid, const NHA_CircularNeighbourhood *circular_neigh, const Buffer<Type::LabVoxel> &labels) 
					: NHA_CurvatureBase(grid, circular_neigh), m_labels(labels) {};
				/** Estimate the curvature at the i-th grid point. */
				virtual void Estimate(Type::Size i);

			private:
				/** Update the curvature in a circular neighbourhood of the i-th grid point by given value. */
				virtual void Update(Type::Size i, int value);
		};

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                  Class Lab_NHA_Curvature3D                  //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Curvature used in the labelled versions of the Nilsson-Heyden algorithm for 3D grids. */
		class Lab_NHA_Curvature3D : public Lab_NHA_Curvature
		{
			public:
				/** Constructor. */
				Lab_NHA_Curvature3D(NHA_Grid &grid, const NHA_CircularNeighbourhood *circular_neigh, const Buffer<Type::LabVoxel> &labels) 
					: Lab_NHA_Curvature(grid, circular_neigh, labels) {};
				/** Estimate the curvature at the i-th grid point. */
				virtual void Estimate(Type::Size i);

			private:
				/** Update the curvature in a circular neighbourhood of the i-th grid point by given value. */
				virtual void Update(Type::Size i, int value);
		};

	} // namespace fls

} // namespace i3d

#endif // FLS_LAB_NHA_CURVATURE_H

