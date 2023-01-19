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
 * nha_graph.h
 *
 * Graph data structure intended for fast detection of simple points in 3D
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_NHA_GRAPH_H
#define FLS_NHA_GRAPH_H

namespace i3d
{
	namespace fls 
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                      Class NHA_Graph                        //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Graph with M vertices of given maximal degree. */
		template <int M, int Degree> class NHA_Graph
		{
			private:
				/** Vertex of given maximal degree. */
				struct Vertex
				{
					/** Vertex degree. */
					int degree;
					/** Indices of adjacent vertices. */
					int adj[Degree];

					/** Constructor. */
					Vertex() : degree(0) {};
					/** Add adjacent vertex of given index. */
					void Add(int index) { adj[degree] = index; ++degree; };
					/** Remove all adjacent vertices. */
					void Clear() { degree = 0; };
				};

				/** List of vertices. */
				Vertex m_vertices[M];
				/** List of flags determining whether a vertex has already been visited or not. */
				bool m_visited[M];
				/** Internal buffer for storing indices of accessible vertices. */
				int m_accessible[M];

			public:
				/** Constructor. */
				NHA_Graph() {};
				/** Add an edge between given source and target vertices. */
				void Edge(int source, int target) { m_vertices[source].Add(target); };
				/** Remove all edges as well as the visited flags for each vertex in the graph. */
				void Clear() { for (int i = 0; i < M; ++i) { m_vertices[i].Clear(); m_visited[i] = false; } };
				/** Verify whether the graph has given number of vertices accessible from the starting one. */
				bool AccessibleNeighbours(int start, int num);
				/** Verify whether the graph has given number of 6-neighbouring vertices accessible from the starting one. */
				bool AccessibleSixNeighbours(int start, int num);
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_NHA_GRAPH
