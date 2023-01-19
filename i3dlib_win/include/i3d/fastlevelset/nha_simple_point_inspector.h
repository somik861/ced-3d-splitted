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
 * nha_simple_point_inspector.h
 *
 * Simple point inspector used in the topology-preserving version of the Nilsson-Heyden algorithm
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_NHA_SIMPLE_POINT_INSPECTOR_H
#define FLS_NHA_SIMPLE_POINT_INSPECTOR_H

#include "nha_point_inspector.h"
#include "nha_graph.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                Class NHA_SimplePointInspector               //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Simple point inspector used in the topology-preserving version of the Nilsson-Heyden algorithm for 2D grids. 
		  * The implementation considers the 4-adjacency for the background and the 8-adjacency for the foreground. */
		class NHA_SimplePointInspector : public NHA_PointInspector
		{
			public:
				/** Constructor. */
				NHA_SimplePointInspector(const Grid<int> &grid) : NHA_PointInspector(grid) {};
				/** Verify whether the i-th grid point satisfies a given condition. */
				virtual bool Verify(Type::Size i);
		};

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//               Class NHA_SimplePointInspector3D              //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Simple point inspector used in the topology-preserving version of the Nilsson-Heyden algorithm for 3D grids. 
		  * The implementation considers the 6-adjacency for the background and the 26-adjacency for the foreground. */
		class NHA_SimplePointInspector3D : public NHA_SimplePointInspector
		{
			private:
				/** Graph of the background in the 26-neighbourhood of a grid point. */
				NHA_Graph<18, 4> m_background_graph;
				/** Graph of the foreground in the 26-neighbourhood of a grid point. */
				NHA_Graph<26, 16> m_foreground_graph;
				/** Internal buffer of the 26-neighbourhood of a grid point. */
				bool m_neigh[26];

			public:
				/** Constructor. */
				NHA_SimplePointInspector3D(const Grid<int> &grid) 
					: NHA_SimplePointInspector(grid), m_background_graph(), m_foreground_graph() {};
				/** Verify whether the i-th grid point satisfies a given condition. */
				virtual bool Verify(Type::Size i);

			private:
				/** Verify whether the number of background components is equal to one. */
				bool VerifyBackground();
				/** Verify whether the number of foreground components is equal to one. */
				bool VerifyForeground();
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_NHA_SIMPLE_POINT_INSPECTOR_H

