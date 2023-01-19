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
 * tp_nha_routine.h
 *
 * Routine for the topology-preserving version of the Nilsson-Heyden algorithm
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_TP_NHA_ROUTINE_H
#define FLS_TP_NHA_ROUTINE_H

#include "nha_routine.h"
#include "nha_simple_point_inspector.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                   Class TP_NHA_Routine                      //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Routine for the topology-preserving version of the Nilsson-Heyden algorithm. */
		class TP_NHA_Routine : public NHA_Routine
		{
			protected:
				/** Pointer to the NHA_SimplePointInspector object. */
				NHA_SimplePointInspector *m_simple_point_inspector;

			public:
				/** Constructor. */
				TP_NHA_Routine(NHA_Base *base, NHA_Initializer *initializer, NHA_Neighbourhood *neighbourhood, const SpeedFunction *speed_function, 
							   NHA_Curvature *curvature, NHA_ResultCreator *result_creator, NHA_SimplePointInspector *simple_point_inspector)
					: NHA_Routine(base, initializer, neighbourhood, speed_function, curvature, result_creator), m_simple_point_inspector(simple_point_inspector) {};
				/** Destructor. */
				virtual ~TP_NHA_Routine() { delete m_simple_point_inspector; };
				/** Perform one iteration. */
				virtual void PerformIteration();
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_TP_NHA_ROUTINE_H

