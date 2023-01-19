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
 * nha_routine.h
 *
 * Routine for the Nilsson-Heyden algorithm
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_NHA_ROUTINE_H
#define FLS_NHA_ROUTINE_H

#include "routine.h"
#include "nha_base.h"
#include "nha_initializer.h"
#include "nha_neighbourhood.h"
#include "speed_function.h"
#include "nha_curvature.h"
#include "nha_result_creator.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                     Class NHA_Routine                       //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Routine for the Nilsson-Heyden algorithm. */
		class NHA_Routine : public Routine<int>
		{
			protected:
				/** Pointer to the NHA_Base object. */
				NHA_Base *m_base;
				/** Pointer to the NHA_Initializer object. */
				NHA_Initializer *m_initializer;
				/** Pointer to the NHA_Neighbourhood object. */
				NHA_Neighbourhood *m_neighbourhood;
				/** Pointer to the SpeedFunction object. */
				const SpeedFunction *m_speed_function;
				/** Pointer to the NHA_Curvature object. */
				NHA_Curvature *m_curvature;

			public:
				/** Constructor. */
				NHA_Routine(NHA_Base *base, NHA_Initializer *initializer, NHA_Neighbourhood *neighbourhood, const SpeedFunction *speed_function, 
					NHA_Curvature *curvature, const NHA_ResultCreator *result_creator)
					: Routine<int>(base, result_creator), m_base(base), m_initializer(initializer), m_neighbourhood(neighbourhood), m_speed_function(speed_function), m_curvature(curvature) {};
				/** Destructor. */
				virtual ~NHA_Routine();
				/** Initialize the routine. */
				virtual void Initialize();
				/** Get the number of grid points belonging to the interface. */
				virtual Type::Size InterfaceSize() const { return m_base -> m_heap.GetSize(); };
				/** Check whether the next iteration can be performed. */
				virtual bool Ready() const { return !m_base -> m_heap.IsEmpty(); };
				/** Perform one iteration. */
				virtual void PerformIteration();
		};

	} // namespace fls

} // namespace i3d

#endif // FLS_NHA_ROUTINE_H

