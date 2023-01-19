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
 * result_creator.h
 *
 * Result creator
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_RESULT_CREATOR_H
#define FLS_RESULT_CREATOR_H

#include "defs.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                     Class ResultCreator                     //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Result creator. */
		class ResultCreator
		{
			public:
				/** Result type enumeration. */
				enum ResType
				{
					Interior = 0,
					Interface,
					Exterior,
					InteriorAndInterface,
					ExteriorAndInterface,
					InteriorAndExterior
				};

				/** Constructor. */
				ResultCreator() {};
				/** Destructor. */
				virtual ~ResultCreator() {};
				/** Get a binary mask for given result type. The last parameter determines whether the mask is computed over the whole 
				* image or only inside the domain. In the latter case, the mask image is only changed inside the domain. */
				void GetMask(Type::BinVoxel *mask, ResType type, bool only_in_domain = false) const;
				/** Get a labeled image of foreground components. The last parameter determines whether the labeled image is computed over 
				* the whole image or only inside the domain. In the latter case, the labeled image is only changed inside the domain. The
				* label 0 always corresponds to background components. */
				void GetLabels(Type::LabVoxel *labels, bool only_in_domain = false) const;

			private:
				/** Get a binary mask of the interior. */
				virtual void InteriorMask(Type::BinVoxel *mask) const = 0;
				/** Get a binary mask of the interior inside the domain. */
				virtual void InteriorMaskInDomain(Type::BinVoxel *mask) const = 0;
				/** Get a binary mask of the interface. */
				virtual void InterfaceMask(Type::BinVoxel *mask) const = 0;
				/** Get a binary mask of the interface inside the domain. */
				virtual void InterfaceMaskInDomain(Type::BinVoxel *mask) const = 0;
				/** Get a binary mask of the exterior. */
				virtual void ExteriorMask(Type::BinVoxel *mask) const = 0;
				/** Get a binary mask of the exterior inside the domain. */
				virtual void ExteriorMaskInDomain(Type::BinVoxel *mask) const = 0;
				/** Get a binary mask of the interior and the interface. */
				virtual void InteriorAndInterfaceMask(Type::BinVoxel *mask) const = 0;
				/** Get a binary mask of the interior and the interface inside the domain. */
				virtual void InteriorAndInterfaceMaskInDomain(Type::BinVoxel *mask) const = 0;
				/** Get a binary mask of the exterior and the interface. */
				virtual void ExteriorAndInterfaceMask(Type::BinVoxel *mask) const = 0;
				/** Get a binary mask of the exterior and the interface inside the domain. */
				virtual void ExteriorAndInterfaceMaskInDomain(Type::BinVoxel *mask) const = 0;
				/** Get a binary mask of the interior and the exterior. */
				virtual void InteriorAndExteriorMask(Type::BinVoxel *mask) const = 0;
				/** Get a binary mask of the interior and the exterior inside the domain. */
				virtual void InteriorAndExteriorMaskInDomain(Type::BinVoxel *mask) const = 0;
				/** Get a labelled image of foreground components. */
				virtual void Labels(Type::LabVoxel *labels) const = 0;
				/** Get a labelled image of foreground components inside the domain. */
				virtual void LabelsInDomain(Type::LabVoxel *labels) const = 0;
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_RESULT_CREATOR_H

