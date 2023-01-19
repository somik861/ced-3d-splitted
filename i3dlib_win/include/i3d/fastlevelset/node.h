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
 * node.h
 *
 * Heap node
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_NODE_H
#define FLS_NODE_H

#include "defs.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                       Struct Node                           //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Heap node. */
		template <class KEY> struct Node
		{
			/** Zero-based index of a grid point. */
			Type::Size  m_index;
			/** Key of the node. Nodes are sorted in the ascending order of their keys. */
			KEY m_key;

			/** Constructor. */
			Node(Type::Size  index, KEY key) : m_index(index), m_key(key) {};
			/** Destructor. */
			virtual ~Node() {};
			/** Update the key of the node. Return true if the key was changed. */
			virtual bool Update(KEY value);
		};

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                       Struct NHA_Node		               //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Heap node used in the Nilsson-Heyden algorithm. The key corresponds to the time at which the interface is propagated from a grid point to its neighbours. */
		struct NHA_Node : public Node<Type::Prec>
		{
			/** Time at which the interface arrived to a grid point. */
			Type::Prec m_arrival_time;
			/** Speed at a grid point. */
			Type::Prec m_speed;

			/** Constructor intended for creating a partial object for which the speed is unknown. The speed is set to the maximal possible value. */
			NHA_Node(Type::Size index, Type::Prec arrival_time); 
			/** Constructor intended for creating a full object. */
			NHA_Node(Type::Size index, Type::Prec arrival_time, Type::Prec speed);
			/** Update the key of the node. Return true if the key was changed. */
			virtual bool Update(Type::Prec value);
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_NODE_H

