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
 * lab_glob_reg_nha_routine.h
 *
 * Topology-preserving routine for the labelled global region-based version of the Nilsson-Heyden algorithm
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_LAB_GLOB_REG_NHA_ROUTINE_H
#define FLS_LAB_GLOB_REG_NHA_ROUTINE_H

#include "routine.h"
#include "lab_glob_reg_nha_base.h"
#include "lab_reg_nha_initializer.h"
#include "lab_nha_neighbourhood.h"
#include "reg_speed_function.h"
#include "lab_nha_curvature.h"
#include "lab_nha_result_creator.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                Class Lab_Glob_Reg_NHA_Routine               //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Topology-preserving routine for the labelled global region-based version of the Nilsson-Heyden algorithm. 
		  * The routine only preserves the topology of components with different labels. */
		class Lab_Glob_Reg_NHA_Routine : public Routine<int>
		{
			protected:
				/** Pointer to the Lab_Glob_Reg_NHA_Base object. */
				Lab_Glob_Reg_NHA_Base *m_base;
				/** Pointer to the ObjectManager object. */
				ObjectManager *m_obj_manager;
				/** Pointer to the Lab_Reg_NHA_Initializer object. */
				Lab_Reg_NHA_Initializer *m_initializer;
				/** Pointer to the Lab_NHA_Neighbourhood object. */
				Lab_NHA_Neighbourhood *m_neighbourhood;
				/** Pointer to the RegionSpeedFunction object. */
				const RegionSpeedFunction *m_speed_function;
				/** Pointer to the Lab_NHA_Curvature object. */
				Lab_NHA_Curvature *m_curvature;

			public:
				/** Constructor. */
				Lab_Glob_Reg_NHA_Routine(Lab_Glob_Reg_NHA_Base *base, ObjectManager *obj_manager, Lab_Reg_NHA_Initializer *initializer, Lab_NHA_Neighbourhood *neighbourhood, 
										 const RegionSpeedFunction *speed_function, Lab_NHA_Curvature *curvature, const Lab_NHA_ResultCreator *result_creator)
					: Routine<int>(base, result_creator), m_base(base), m_obj_manager(obj_manager), m_initializer(initializer), m_neighbourhood(neighbourhood), 
					  m_speed_function(speed_function), m_curvature(curvature) {};
				/** Destructor. */
				virtual ~Lab_Glob_Reg_NHA_Routine();
				/** Initialize the routine. */
				virtual void Initialize() { m_initializer -> Initialize(m_base -> m_interface); m_obj_manager -> Synchronize(); };
				/** Get the number of grid points belonging to the interface. */
				virtual Type::Size InterfaceSize() const { return m_base -> m_interface.size(); };
				/** Check whether the next iteration can be performed. */
				virtual bool Ready() const { return !m_base -> m_interface.empty(); };
				/** Perform one iteration. */
				virtual void PerformIteration();
				/** Check whether a convergence criterion has been reached. */
				virtual bool Converged() const { return m_obj_manager -> Converged(); };
				/** Show information about the routine on the standard output. By default, the status of the routine as well as the number of performed iterations is shown. 
				  * Information about foreground and background objects is shown as well. */ 
				virtual void Info() const { Routine<int>::Info(); m_obj_manager -> Info(); };
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_LAB_GLOB_REG_NHA_ROUTINE_H

