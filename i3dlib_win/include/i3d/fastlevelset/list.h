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
 * list.h
 *
 * List data structure intended for finding a node of the minimal key
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_LIST_H
#define FLS_LIST_H

#include <list>
#include "node.h"
#include "speed_function.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                        Class List                           //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** List data structure intended for finding a node of the minimal key. */
		template <class KEY, class NODE = Node<KEY> > class List
		{
			private:
				/** List of nodes in the list. */
				std::list<NODE *> m_nodes;

			public:
				/** Constructor. */
				List() : m_nodes() {};
				/** Destructor. */
				~List() { Clear(); };
				/** Get the size of the list. */
				Type::Size GetSize() const { return m_nodes.size(); };
				/** Check whether the list is empty. */
				bool IsEmpty() const { return m_nodes.empty(); };
				/** Remove the node of the minimal key. An exception is thrown when the list is empty. */
				NODE *Pop(const SpeedFunction *speed_function);
				/** Insert a node at the beginning of the list. */
				void Insert(NODE *node) { m_nodes.push_front(node); };

			private:
				/** Clear the list of nodes in the list. */
				void Clear();
		};

	} // namespace fls

} // namespace i3d

#endif // FLS_LIST_H

