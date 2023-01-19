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
 * lab_reg_nha_initializer.h
 *
 * Initializer of the labelled region-based version of the Nilsson-Heyden algorithm
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_LAB_REG_NHA_INITIALIZER_H
#define FLS_LAB_REG_NHA_INITIALIZER_H

#include <vector>
#include "grid.h"
#include "object_manager.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                Class Lab_Reg_NHA_Initializer                //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Initializer of the labelled region-based version of the Nilsson-Heyden algorithm for 2D grids. */
		class Lab_Reg_NHA_Initializer
		{
			protected:
				/** Computational grid. */
				Grid<int> &m_grid;
				/** Buffer intended for storing labels. */
				Buffer<Type::LabVoxel> &m_labels;
				/** Manager for efficient computation of foreground and background object statistics. */
				ObjectManager *m_obj_manager;
				/** Mask definition. */
				const Type::LabVoxel *m_mask;
				
			public:
				/** Constructor. */
				Lab_Reg_NHA_Initializer(Grid<int> &grid, Buffer<Type::LabVoxel> &labels, ObjectManager *obj_manager, const Type::LabVoxel *mask) 
					: m_grid(grid), m_labels(labels), m_obj_manager(obj_manager), m_mask(mask) {};
				/** Destructor. */
				virtual ~Lab_Reg_NHA_Initializer() {};
				/** Initialize the implicit function and find grid points belonging to the interface. */
				virtual void Initialize(std::vector<Type::Size> &initial_interface);
		};

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//               Class Lab_Reg_NHA_Initializer3D               //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Initializer of the labelled region-based version of the Nilsson-Heyden algorithm for 3D grids. */
		class Lab_Reg_NHA_Initializer3D : public Lab_Reg_NHA_Initializer
		{
			public:
				/** Constructor. */
				Lab_Reg_NHA_Initializer3D(Grid<int> &grid, Buffer<Type::LabVoxel> &labels, ObjectManager *obj_manager, const Type::LabVoxel *mask) 
					: Lab_Reg_NHA_Initializer(grid, labels, obj_manager, mask) {};
				/** Initialize the implicit function and find grid points belonging to the interface. */
				virtual void Initialize(std::vector<Type::Size> &initial_interface);
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_LAB_REG_NHA_INITIALIZER_H

