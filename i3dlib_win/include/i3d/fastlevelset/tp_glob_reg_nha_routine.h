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
 * tp_glob_reg_nha_routine.h
 *
 * Topology-preserving routine for the global region-based version of the Nilsson-Heyden algorithm
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_TP_GLOB_REG_NHA_ROUTINE_H
#define FLS_TP_GLOB_REG_NHA_ROUTINE_H

#include "glob_reg_nha_routine.h"
#include "nha_simple_point_inspector.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                Class TP_Glob_Reg_NHA_Routine                //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Topology-preserving routine for the global region-based version of the Nilsson-Heyden algorithm. */
		class TP_Glob_Reg_NHA_Routine : public Glob_Reg_NHA_Routine
		{
			protected:
				/** Pointer to the NHA_SimplePointInspector object. */
				NHA_SimplePointInspector *m_simple_point_inspector;

			public:
				/** Constructor. */
				TP_Glob_Reg_NHA_Routine(Glob_Reg_NHA_Base *base, ObjectManager *obj_manager, Reg_NHA_Initializer *initializer, NHA_Neighbourhood *neighbourhood, 
										const RegionSpeedFunction *speed_function, NHA_CurvatureBase *curvature, const NHA_ResultCreator *result_creator, 
										NHA_SimplePointInspector *simple_point_inspector)
					: Glob_Reg_NHA_Routine(base, obj_manager, initializer, neighbourhood, speed_function, curvature, result_creator), m_simple_point_inspector(simple_point_inspector) {};
				/** Destructor. */
				virtual ~TP_Glob_Reg_NHA_Routine() { delete m_simple_point_inspector; };
				/** Perform one iteration. */
				virtual void PerformIteration();
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_TP_GLOB_REG_NHA_ROUTINE_H

