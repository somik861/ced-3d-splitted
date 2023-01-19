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
 * buffer.h
 *
 * Buffer - a non-resizable array of items of given type
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_BUFFER_H
#define FLS_BUFFER_H

#include "defs.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                       Class Buffer                          //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/* Non-resizable array of items of given type. */
		template <class T> class Buffer
		{
			private:
				/** Items in the array. */
				T *m_array;
				/** Size of the array. */
				Type::Size m_size;

			public:
				/** Constructor. Create the array of given size. The items are constructed using their default constructor. 
				  * The std::bad_alloc exception is thrown if the memory allocation fails. */
				Buffer(Type::Size size) : m_array(NULL), m_size(0) { Alloc(size); };
				/** Constructor. Create the array of given size. The items are set to given value. 
				  * The std::bad_alloc exception is thrown if the memory allocation fails. */
				Buffer(const T &value, Type::Size size) : m_array(NULL), m_size(0) { Alloc(size); Set(value); };
				/** Destructor. */
				~Buffer() { delete [] m_array; };
				/** Get a pointer to the first item in the array. */
				T *begin() { return m_array; };
				/** Get a pointer to the first item in the array. */
				const T *begin() const { return m_array; };
				/** Get a pointer to the i-th item in the array. */
				T *ptr(Type::Size i) { return m_array + i; };
				/** Get a pointer to the i-th item in the array. */
				const T *ptr(Type::Size i) const { return m_array + i; };
				/** Get a reference to the i-th item in the array. */
				T &operator[](Type::Size i) { return *(m_array + i); };
				/** Get a reference to the i-th item in the array. */
				const T &operator[](Type::Size i) const { return *(m_array + i); };

			private:
				/** Memory allocation. The std::bad_alloc exception is thrown if the memory allocation fails. */
				void Alloc(Type::Size size)
				{
					m_array = new T[size];
					m_size = size;
				}

				/** Set each item in the array to given value. */
				void Set(const T &value)
				{
					for (Type::Size i = 0; i < m_size; ++i)
					{
						m_array[i] = value;
					}
				}
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_BUFFER_H

