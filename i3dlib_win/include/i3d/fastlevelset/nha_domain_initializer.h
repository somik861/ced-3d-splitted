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
 * nha_domain_initializer.h
 *
 * Initializer of the Nilsson-Heyden algorithm with respect to given domain
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_NHA_DOMAIN_INITIALIZER_H
#define FLS_NHA_DOMAIN_INITIALIZER_H

#include "nha_initializer.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                 Class NHA_DomainInitializer                 //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Initializer of the Nilsson-Heyden algorithm for 2D grids with respect to given domain. */
		class NHA_DomainInitializer : public NHA_Initializer
		{
			protected:
				/** Domain definition. */
				const Type::BinVoxel *m_domain;

			public:
				/** Constructor. */
				NHA_DomainInitializer(Grid<int> &grid, const Type::BinVoxel *mask, const Type::BinVoxel *domain) : NHA_Initializer(grid, mask), m_domain(domain) {};
				/** Initialize the implicit function and find grid points belonging to the interface. */
				virtual void Initialize(std::vector<Type::Size> &initial_interface);
		};

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                Class NHA_DomainInitializer3D                //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Initializer of the Nilsson-Heyden algorithm for 3D grids with respect to given domain. */
		class NHA_DomainInitializer3D : public NHA_DomainInitializer
		{
			public:
				/** Constructor. */
				NHA_DomainInitializer3D(Grid<int> &grid, const Type::BinVoxel *mask, const Type::BinVoxel *domain) : NHA_DomainInitializer(grid, mask, domain) {};
				/** Initialize the implicit function and find grid points belonging to the interface. */
				virtual void Initialize(std::vector<Type::Size> &initial_interface);
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_NHA_DOMAIN_INITIALIZER_H

