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
 * nha_neighbourhood.h
 *
 * Neighbourhood used in the Nilsson-Heyden algorithm
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_NHA_NEIGHBOURHOOD_H
#define FLS_NHA_NEIGHBOURHOOD_H

#include "grid.h"
#include "neighbour_indices.h"
#include "nha_predicate.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                    Class NHA_Neighbourhood                  //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Neighbourhood used in the Nilsson-Heyden algorithm. */
		class NHA_Neighbourhood
		{
			protected:
				/** Computational grid. */
				const Grid<int> &m_grid;
				/** Neighbour indices. */
				NeighbourIndices *m_neigh_indices;
				/** Unary predicate intended for checking whether a grid point is internal. */
				const NHA_Predicate *m_pred_internal;
				/** Unary predicate intended for checking whether a grid point is external. */
				const NHA_Predicate *m_pred_external;
				/** Internal buffer intended for storing neighbour indices. */
				Type::Size *m_buffer;

			public:
				/** Constructor. The std::bad_alloc exception is thrown if the memory allocation fails. */
				NHA_Neighbourhood(const Grid<int> &grid, NeighbourIndices *neigh_indices, const NHA_Predicate *pred_internal, const NHA_Predicate *pred_external);
				/** Destructor. */
				virtual ~NHA_Neighbourhood();
				/** Get internal neighbours of the i-th grid point. */
				const Type::Size *InternalNeighbours(Type::Size i, Type::Size &num) { return Neighbours(i, m_pred_internal, num); };
				/** Get external neighbours of the i-th grid point. */
				const Type::Size *ExternalNeighbours(Type::Size i, Type::Size &num) { return Neighbours(i, m_pred_external, num); };
				/** Get the number of available neighbours, i.e. those with different label, of the i-th grid point. */
				virtual Type::Size NumAvail(Type::Size i);

			private:
				/** Get neighbours of the i-th grid point at which the implicit function satisfies given predicate. */
				virtual const Type::Size *Neighbours(Type::Size i, const NHA_Predicate *pred, Type::Size &num);
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_NHA_NEIGHBOURHOOD_H

