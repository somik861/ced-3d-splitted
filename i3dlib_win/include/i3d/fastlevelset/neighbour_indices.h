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
 * neighbour_indices.h
 *
 * Neighbour indices intended for various computational grids
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_NEIGHBOUR_INDICES_H
#define FLS_NEIGHBOUR_INDICES_H

#include "grid_base.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                    Class NeighbourIndices                   //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Neighbour indices intended for various computational grids. */
		class NeighbourIndices
		{
			protected:
				/** Computational grid. */
				const GridBase &m_grid;
				/** Number of neighbour indices. */
				Type::Size m_num;
				/** Internal buffer intended for storing neighbour indices. */
				Type::Size *m_buffer;

			public:
				/** Constructor. The std::bad_alloc exception is thrown if the memory allocation fails. */
				NeighbourIndices(const GridBase &grid, Type::Size num) : m_grid(grid), m_num(num), m_buffer(NULL) { m_buffer = new Type::Size[num]; };
				/** Destructor. */
				virtual ~NeighbourIndices() { delete [] m_buffer; };
				/** Get the number of neighbour indices. */
				Type::Size Number() const { return m_num; };
				/** Get the neighbour indices of the i-th grid point. */
				const Type::Size *Indices(Type::Size i, Type::Size &num) { ApplyShifts(i); num = m_num; return m_buffer; };

			private:
				/** Apply neighbour shifts on the i-th grid point. */
				virtual void ApplyShifts(Type::Size i) = 0;
		};

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                  Class NeighbourIndices2D_4                 //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Neighbour indices intended for 4-neighbourhoods in 2D computational grids. */
		class NeighbourIndices2D_4 : public NeighbourIndices
		{
			public:
				/** Constructor. The std::bad_alloc exception is thrown if the memory allocation fails. */
				NeighbourIndices2D_4(const GridBase &grid) : NeighbourIndices(grid, 4) {};

			private:
				/** Apply neighbour shifts on the i-th grid point. */
				virtual void ApplyShifts(Type::Size i);
		};

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                  Class NeighbourIndices2D_8                 //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Neighbour indices intended for 8-neighbourhoods in 2D computational grids. */
		class NeighbourIndices2D_8 : public NeighbourIndices
		{
			public:
				/** Constructor. The std::bad_alloc exception is thrown if the memory allocation fails. */
				NeighbourIndices2D_8(const GridBase &grid) : NeighbourIndices(grid, 8) {};
				
			private:
				/** Apply neighbour shifts on the i-th grid point. */
				virtual void ApplyShifts(Type::Size i);

		};

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                  Class NeighbourIndices3D_6                 //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Neighbour indices intended for 6-neighbourhoods in 3D computational grids. */
		class NeighbourIndices3D_6 : public NeighbourIndices
		{
			public:
				/** Constructor. The std::bad_alloc exception is thrown if the memory allocation fails. */
				NeighbourIndices3D_6(const GridBase &grid): NeighbourIndices(grid, 6) {};
				
			private:
				/** Apply neighbour shifts on the i-th grid point. */
				virtual void ApplyShifts(Type::Size i);

		};

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                  Class NeighbourIndices3D_18                //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Neighbour indices intended for 18-neighbourhoods in 3D computational grids. */
		class NeighbourIndices3D_18 : public NeighbourIndices
		{
			public:
				/** Constructor. The std::bad_alloc exception is thrown if the memory allocation fails. */
				NeighbourIndices3D_18(const GridBase &grid): NeighbourIndices(grid, 18) {};
				
			private:
				/** Apply neighbour shifts on the i-th grid point. */
				virtual void ApplyShifts(Type::Size i);

		};

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                  Class NeighbourIndices3D_26                //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Neighbour indices intended for 26-neighbourhoods in 3D computational grids. */
		class NeighbourIndices3D_26 : public NeighbourIndices
		{
			public:
				/** Constructor. The std::bad_alloc exception is thrown if the memory allocation fails. */
				NeighbourIndices3D_26(const GridBase &grid) : NeighbourIndices(grid, 26) {};
				
			private:
				/** Apply neighbour shifts on the i-th grid point. */
				virtual void ApplyShifts(Type::Size i);

		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_NEIGHBOUR_INDICES_H

