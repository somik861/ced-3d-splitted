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
 * nha_point_inspector.h
 *
 * Point inspector used in the Nilsson-Heyden algorithm
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_NHA_POINT_INSPECTOR_H
#define FLS_NHA_POINT_INSPECTOR_H

#include "grid.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                     Class PointInspector                    //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Point inspector used in the Nilsson-Heyden algortihm. */
		class NHA_PointInspector
		{
			protected:
				/** Computational grid. */
				const Grid<int> &m_grid;

			public:
				/** Constructor. */
				NHA_PointInspector(const Grid<int> &grid) : m_grid(grid) {};
				/** Destructor. */
				virtual ~NHA_PointInspector() {};
				/** Verify whether the i-th grid point satisfies a given condition. */
				virtual bool Verify(Type::Size i) = 0;
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_NHA_POINT_INSPECTOR_H

