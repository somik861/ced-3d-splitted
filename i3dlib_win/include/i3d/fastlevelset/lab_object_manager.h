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
 * lab_object_manager.h
 *
 * Manager responsible for efficient computation of multiple foreground and background object statistics
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_LAB_OBJECT_MANAGER_H
#define FLS_LAB_OBJECT_MANAGER_H

#include "object_manager.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                    Class LabObjectManager                   //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Manager responsible for efficient computation of multiple foreground and background object statistics. */
		class LabObjectManager : public ObjectManager
		{
			private:
				/** Buffer intended for storing labels. */
				const Type::LabVoxel *m_labels;

			public:
				/** Constructor. */
				LabObjectManager(const Type::Prec *data, const Type::LabVoxel *labels) : ObjectManager(data), m_labels(labels) {};

			private:
				/** Get a label of the foreground object to which the i-th grid point belongs to. */ 
				virtual Type::LabVoxel Label(Type::Size i) const { return m_labels[i]; };
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_LAB_OBJECT_MANAGER_H

