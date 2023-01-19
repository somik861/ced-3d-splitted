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
 * tp_reg_nha_initializer.h
 *
 * Initializer of the topology-preserving region-based version of the Nilsson-Heyden algorithm
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_TP_REG_NHA_INITIALIZER_H
#define FLS_TP_REG_NHA_INITIALIZER_H

#include "reg_nha_initializer.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                Class TP_Reg_NHA_Initializer                 //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Initializer of the topology-preserving region-based version of the Nilsson-Heyden algorithm for 2D grids. */
		class TP_Reg_NHA_Initializer : public Reg_NHA_Initializer
		{
			public:
				/** Constructor. */
				TP_Reg_NHA_Initializer(Grid<int> &grid, const Type::BinVoxel *mask, ObjectManager &obj_manager) : Reg_NHA_Initializer(grid, mask, obj_manager) {};
				/** Initialize the implicit function and find grid points belonging to the interface. */
				virtual void Initialize(std::vector<Type::Size> &initial_interface);
		};

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                Class TP_Reg_NHA_Initializer3D                //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Initializer of the topology-preserving region-based version of the Nilsson-Heyden algorithm for 3D grids. */
		class TP_Reg_NHA_Initializer3D : public TP_Reg_NHA_Initializer
		{
			public:
				/** Constructor. */
				TP_Reg_NHA_Initializer3D(Grid<int> &grid, const Type::BinVoxel *mask, ObjectManager &obj_manager) : TP_Reg_NHA_Initializer(grid, mask, obj_manager) {};
				/** Initialize the implicit function and find grid points belonging to the interface. */
				virtual void Initialize(std::vector<Type::Size> &initial_interface);
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_TP_REG_NHA_INITIALIZER_H

