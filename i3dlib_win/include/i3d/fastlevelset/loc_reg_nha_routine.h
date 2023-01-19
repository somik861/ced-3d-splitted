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
 * loc_reg_nha_routine.h
 *
 * Routine for the local region-based version of the Nilsson-Heyden algorithm
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_LOC_REG_NHA_ROUTINE_H
#define FLS_LOC_REG_NHA_ROUTINE_H

#include "routine.h"
#include "loc_reg_nha_base.h"
#include "reg_nha_initializer.h"
#include "nha_neighbourhood.h"
#include "reg_speed_function.h"
#include "nha_curvature_base.h"
#include "nha_result_creator.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                 Class Loc_Reg_NHA_Routine                   //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Routine for the local region-based version of the Nilsson-Heyden algorithm. */
		class Loc_Reg_NHA_Routine : public Routine<int>
		{
			protected:
				/** Pointer to the Loc_Reg_NHA_Base object. */
				Loc_Reg_NHA_Base *m_base;
				/** Pointer to the ObjectManager object. */
				ObjectManager *m_obj_manager;
				/** Pointer to the Reg_NHA_Initializer object. */
				Reg_NHA_Initializer *m_initializer;
				/** Pointer to the NHA_Neighbourhood object. */
				NHA_Neighbourhood *m_neighbourhood;
				/** Pointer to the RegionSpeedFunction object. */
				const RegionSpeedFunction *m_speed_function;
				/** Pointer to the NHA_CurvatureBase object. */
				NHA_CurvatureBase *m_curvature;

			public:
				/** Constructor. */
				Loc_Reg_NHA_Routine(Loc_Reg_NHA_Base *base, ObjectManager *obj_manager, Reg_NHA_Initializer *initializer, NHA_Neighbourhood *neighbourhood, 
									const RegionSpeedFunction *speed_function, NHA_CurvatureBase *curvature, const NHA_ResultCreator *result_creator)
					: Routine<int>(base, result_creator), m_base(base), m_obj_manager(obj_manager), m_initializer(initializer), m_neighbourhood(neighbourhood), 
					  m_speed_function(speed_function), m_curvature(curvature) {};
				/** Destructor. */
				virtual ~Loc_Reg_NHA_Routine();
				/** Initialize the routine. */
				virtual void Initialize();
				/** Get the number of grid points belonging to the interface. */
				virtual Type::Size InterfaceSize() const { return m_base -> m_list.GetSize(); };
				/** Check whether the next iteration can be performed. */
				virtual bool Ready() const { return !m_base -> m_list.IsEmpty(); };
				/** Perform one iteration. */
				virtual void PerformIteration();
				/** Show information about the routine on the standard output. By default, the status of the routine as well as the number of performed iterations is shown. 
				  * Information about foreground and background objects is shown as well. */ 
				virtual void Info() const { Routine<int>::Info(); m_obj_manager -> Info(); };
		};

	} // namespace fls

} // namespace i3d

#endif // FLS_LOC_REG_NHA_ROUTINE_H

