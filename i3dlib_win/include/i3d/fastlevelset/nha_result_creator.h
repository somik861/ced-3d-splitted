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
 * nha_result_creator.h
 *
 * Result creator used in the Nilsson-Heyden algorithm
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_NHA_RESULT_CREATOR_H
#define FLS_NHA_RESULT_CREATOR_H

#include "result_creator.h"
#include "grid.h"
#include "nha_predicate.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                   Class NHA_ResultCreator                   //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Result creator used in the Nilsson-Heyden algorithm for 2D grids. */
		class NHA_ResultCreator : public ResultCreator
		{
			protected:
				/** Computational grid. */
				const Grid<int> &m_grid;
				/** Unary predicate intended for the interior mask. */
				NHA_PredicateEqual<-1> m_interior;
				/** Unary predicate intended for the interface mask. */
				NHA_PredicateEqual<0> m_interface;
				/** Unary predicate intended for the exterior mask. */
				NHA_PredicateEqual<1> m_exterior;
				/** Unary predicate intended for the interior and interface mask. */
				NHA_PredicateLess<1> m_interior_interface;
				/** Unary predicate intended for the exterior and interface mask. */
				NHA_PredicateChoice<1, 0> m_exterior_interface;
				/** Unary predicate intended for the interior and exterior mask. */
				NHA_PredicateChoice<-1, 1> m_interior_exterior;

			public:
				/** Constructor. */
				NHA_ResultCreator(const Grid<int> &grid) 
					: ResultCreator(), m_grid(grid), m_interior(), m_interface(), m_exterior(), m_interior_interface(), m_exterior_interface(), m_interior_exterior() {};

			private:
				/** Get a binary mask of the interior. */
				virtual void InteriorMask(Type::BinVoxel *mask) const { ScanGrid(mask, &m_interior); };
				/** Get a binary mask of the interior inside the domain. */
				virtual void InteriorMaskInDomain(Type::BinVoxel *mask) const { ScanGridInDomain(mask, &m_interior); };
				/** Get a binary mask of the interface. */
				virtual void InterfaceMask(Type::BinVoxel *mask) const { ScanGrid(mask, &m_interface); };
				/** Get a binary mask of the interface inside the domain. */
				virtual void InterfaceMaskInDomain(Type::BinVoxel *mask) const { ScanGridInDomain(mask, &m_interface); };
				/** Get a binary mask of the exterior. */
				virtual void ExteriorMask(Type::BinVoxel *mask) const { ScanGrid(mask, &m_exterior); };
				/** Get a binary mask of the exterior inside the domain. */
				virtual void ExteriorMaskInDomain(Type::BinVoxel *mask) const { ScanGridInDomain(mask, &m_exterior); };
				/** Get a binary mask of the interior and the interface. */
				virtual void InteriorAndInterfaceMask(Type::BinVoxel *mask) const { ScanGrid(mask, &m_interior_interface); };
				/** Get a binary mask of the interior and the interface inside the domain. */
				virtual void InteriorAndInterfaceMaskInDomain(Type::BinVoxel *mask) const { ScanGridInDomain(mask, &m_interior_interface); };
				/** Get a binary mask of the exterior and the interface. */
				virtual void ExteriorAndInterfaceMask(Type::BinVoxel *mask) const { ScanGrid(mask, &m_exterior_interface); };
				/** Get a binary mask of the exterior and the interface inside the domain. */
				virtual void ExteriorAndInterfaceMaskInDomain(Type::BinVoxel *mask) const { ScanGridInDomain(mask, &m_exterior_interface); };
				/** Get a binary mask of the interior and the exterior. */
				virtual void InteriorAndExteriorMask(Type::BinVoxel *mask) const { ScanGrid(mask, &m_interior_exterior); };
				/** Get a binary mask of the interior and the exterior inside the domain. */
				virtual void InteriorAndExteriorMaskInDomain(Type::BinVoxel *mask) const { ScanGridInDomain(mask, &m_interior_exterior); };
				/** Get a labelled image of foreground components. */
				virtual void Labels(Type::LabVoxel *labels) const;
				/** Get a labelled image of foreground components inside the domain. */
				virtual void LabelsInDomain(Type::LabVoxel *labels) const;
				/** Scan a grid and check whether a grid point satisfies given predicate. */
				virtual void ScanGrid(Type::BinVoxel *mask, const NHA_Predicate *pred) const;
				/** Scan a grid inside the domain and check whether a grid point satisfies given predicate. */
				virtual void ScanGridInDomain(Type::BinVoxel *mask, const NHA_Predicate *pred) const;
		};

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                  Class NHA_ResultCreator3D                  //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Result creator used in the Nilsson-Heyden algorithm for 3D grids. */
		class NHA_ResultCreator3D : public NHA_ResultCreator
		{
			public:
				/** Constructor. */
				NHA_ResultCreator3D(const Grid<int> &grid) : NHA_ResultCreator(grid) {};

			private:
				/** Get a labelled image of foreground components. */
				virtual void Labels(Type::LabVoxel *labels) const;
				/** Get a labelled image of foreground components inside the domain. */
				virtual void LabelsInDomain(Type::LabVoxel *labels) const;
				/** Scan a grid and check whether a grid point satisfies given predicate. */
				virtual void ScanGrid(Type::BinVoxel *mask, const NHA_Predicate *pred) const;
				/** Scan a grid inside the computational domain and check whether a grid point satisfies given predicate. */
				virtual void ScanGridInDomain(Type::BinVoxel *mask, const NHA_Predicate *pred) const;
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_NHA_RESULT_CREATOR_H

