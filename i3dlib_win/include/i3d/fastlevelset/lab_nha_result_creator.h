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
 * lab_nha_result_creator.h
 *
 * Result creator used in the labelled versions of the Nilsson-Heyden algorithm
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_LAB_NHA_RESULT_CREATOR_H
#define FLS_LAB_NHA_RESULT_CREATOR_H

#include "nha_result_creator.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                 Class Lab_NHA_ResultCreator                 //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Result creator used in the labelled versions of the Nilsson-Heyden algorithm for 2D grids. */
		class Lab_NHA_ResultCreator : public NHA_ResultCreator
		{
			protected:
				/** Buffer intended for storing labels. */
				const Buffer<Type::LabVoxel> &m_lab;

			public:
				/** Constructor. */
				Lab_NHA_ResultCreator(const Grid<int> &grid, const Buffer<Type::LabVoxel> &lab) : NHA_ResultCreator(grid), m_lab(lab) {};

			private:
				/** Get a labelled image of foreground components. */
				virtual void Labels(Type::LabVoxel *labels) const;
				/** Get a labelled image of foreground components inside the domain. */
				virtual void LabelsInDomain(Type::LabVoxel *labels) const;
		};

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                Class Lab_NHA_ResultCreator3D                //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Result creator used in thelabelled version of the Nilsson-Heyden algorithm for 3D grids. */
		class Lab_NHA_ResultCreator3D : public Lab_NHA_ResultCreator
		{
			public:
				/** Constructor. */
				Lab_NHA_ResultCreator3D(const Grid<int> &grid, const Buffer<Type::LabVoxel> &lab) : Lab_NHA_ResultCreator(grid, lab) {};

			private:
				/** Get a labelled image of foreground components. */
				virtual void Labels(Type::LabVoxel *labels) const;
				/** Get a labelled image of foreground components inside the domain. */
				virtual void LabelsInDomain(Type::LabVoxel *labels) const;
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_LAB_NHA_RESULT_CREATOR_H

