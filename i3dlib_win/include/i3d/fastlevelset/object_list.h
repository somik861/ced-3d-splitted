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
 * object_list.h
 *
 * Class representing a list of objects used in the region-based models
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_OBJECT_LIST_H
#define FLS_OBJECT_LIST_H

#include <map>
#include "object.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                      Class ObjectList                       //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Class representing a list of objects used in the region-based models. The list always contains at least the background object with the label 0. Foreground objects have positive labels. */
		class ObjectList
		{
			private:
				/** A list of objects. */
				std::map<Type::LabVoxel, Object> m_list;

			public:
				/** Constructor. */
				ObjectList() : m_list() { m_list[0]; };
				/** Get a reference to an object with given label. If such an object does not exist, new one is created using a default constructor. */
				Object &AdvRef(Type::LabVoxel label) { return m_list[label]; };
				/** Get a reference to an object with given label. If such an object does not exist, a std::out_of_range exception is thrown. */
				Object &Ref(Type::LabVoxel label) { return m_list.at(label); };
				/** Get a const reference to an object with given label. If such an object does not exist, a std::out_of_range exception is thrown. */
				const Object &Ref(Type::LabVoxel label) const { return m_list.at(label); };
				/** Synchronize foreground and background objects and return the sum of absolute values of their differences in the average intensity since the previous synchronization. */
				void Synchronize();
				/** Get accumulated differences in the average intensity of foreground and background objects and reset their counters. */
				Type::Prec FlushDiff();
				/** Show information about foreground and background obejcts on the standard output. */
				void Info() const;
		};

	} // namespace fls

} // namespace i3d

#endif // FLS_OBJECT_LIST_H

