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
 * nha_initializer.h
 *
 * Initializer of the Nilsson-Heyden algorithm
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_NHA_INITIALIZER_H
#define FLS_NHA_INITIALIZER_H

#include <vector>
#include "grid.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                   Class NHA_Initializer                     //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Initializer of the Nilsson-Heyden algorithm for 2D grids. */
		class NHA_Initializer
		{
			protected:
				/** Computational grid. */
				Grid<int> &m_grid;
				/** Mask definition. */
				const Type::BinVoxel *m_mask;

			public:
				/** Constructor. */
				NHA_Initializer(Grid<int> &grid, const Type::BinVoxel *mask) : m_grid(grid), m_mask(mask) {};
				/** Destructor. */
				virtual ~NHA_Initializer() {};
				/** Initialize the implicit function and find grid points belonging to the interface. */
				virtual void Initialize(std::vector<Type::Size> &initial_interface);
		};

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                  Class NHA_Initializer3D                    //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Initializer of the Nilsson-Heyden algorithm for 3D grids. */
		class NHA_Initializer3D : public NHA_Initializer
		{
			public:
				/** Constructor. */
				NHA_Initializer3D(Grid<int> &grid, const Type::BinVoxel *mask) : NHA_Initializer(grid, mask) {};
				/** Initialize the implicit function and find grid points belonging to the interface. */
				virtual void Initialize(std::vector<Type::Size> &initial_interface);
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_NHA_INITIALIZER_H

