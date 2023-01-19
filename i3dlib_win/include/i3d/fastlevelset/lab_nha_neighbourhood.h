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
 * lab_nha_neighbourhood.h
 *
 * Neighbourhood used in the labelled versions of the Nilsson-Heyden algorithm
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_LAB_NHA_NEIGHBOURHOOD_H
#define FLS_LAB_NHA_NEIGHBOURHOOD_H

#include "nha_neighbourhood.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                  Class Lab_NHA_Neighbourhood                //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Neighbourhood used in the labelled versions of the Nilsson-Heyden algorithm. */
		class Lab_NHA_Neighbourhood : public NHA_Neighbourhood
		{
			protected:
				/** Buffer intended for storing labels. */
				const Buffer<Type::LabVoxel> &m_labels;

			public:
				/** Constructor. The std::bad_alloc exception is thrown if the memory allocation fails. */
				Lab_NHA_Neighbourhood(const Grid<int> &grid, NeighbourIndices *neigh_indices, const NHA_Predicate *pred_internal, 
					                  const NHA_Predicate *pred_external, const Buffer<Type::LabVoxel> &labels) 
					: NHA_Neighbourhood(grid, neigh_indices, pred_internal, pred_external), m_labels(labels) {}
				/** Get the number of available neighbours, i.e. those with different label, of the i-th grid point. */
				virtual Type::Size NumAvail(Type::Size i);
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_LAB_NHA_NEIGHBOURHOOD_H

