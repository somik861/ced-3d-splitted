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
 * heap.h
 *
 * Min-heap data structure
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_HEAP_H
#define FLS_HEAP_H

#include <vector>
#include "node.h"
#include "buffer.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                     Class MinHeap                           //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Min-heap data structure. */
		template <class KEY, class NODE = Node<KEY> > class MinHeap
		{
			public:
				/** The value indicating that a grid point is not on the heap. */
				static const Type::Size NOT_ON_HEAP;

			private:
				/** List of nodes on the heap. The nodes are sorted in the ascending order of their keys. */
				std::vector<NODE *> m_nodes; 
				/** List of back-pointers to the heap. It stores positions of grid points on the heap. */
				Buffer<Type::Size> m_back_pointers;

			public:
				/** Constructor. Create the heap for given size of the grid. 
				  * The std::bad_alloc exception is thrown if the memory allocation fails. */
				MinHeap(Type::Size size) : m_nodes(), m_back_pointers(NOT_ON_HEAP, size) {};
				/** Destructor. */
				~MinHeap() { Clear(); };
				/** Get the size of the heap. */
				Type::Size GetSize() const { return m_nodes.size(); };
				/** Check whether the heap is empty. */
				bool IsEmpty() const { return m_nodes.empty(); };
				/** Get the heap position of the i-th grid point. Return NOT_ON_HEAP if the i-th grid point is not on the heap. */
				Type::Size GetPosition(Type::Size i) const { return m_back_pointers[i]; };
				/** Remove the root of the heap and rebalance the heap. An exception is thrown when the heap is empty. */
				NODE *Pop();
				/** Insert a node into the heap and rebalance the heap. */
				void Insert(NODE *node);
				/** Update the key of the i-th node and rebalance the heap. */
				void Update(Type::Size i, KEY value);

			private:
				/** Comparison function. Return true if the key of the i-th node is smaller than the key of the j-th one. */
				bool Compare(Type::Size i, Type::Size j) const { return m_nodes[i] -> m_key < m_nodes[j] -> m_key; };
				/** Rebalance the heap upward starting from the i-th node. */
				void BalanceUp(Type::Size i);
				/** Rebalance the heap downward starting from the i-th node. */
				void BalanceDown(Type::Size i);
				/** Clear the list of nodes on the heap. */
				void Clear();
		};

	} // namespace fls

} // namespace i3d

#endif // FLS_HEAP_H

