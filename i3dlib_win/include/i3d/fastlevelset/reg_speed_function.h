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
 * reg_speed_function.h
 *
 * Region-based speed function
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_REG_SPEED_FUNCTION_H
#define FLS_REG_SPEED_FUNCTION_H

#include "mean_curvature_speed_function.h"
#include "object_manager.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                  Class RegionSpeedFunction                  //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Region-based speed function. */
		class RegionSpeedFunction : public MeanCurvatureSpeedFunction
		{
			protected:
				/** Manager for efficient computation of foreground and background object statistics. 
				  * This class is abstract and cannot be instantiated. */
				const ObjectManager *m_obj_manager;

			public:
				/** Constructor. */
				RegionSpeedFunction(const MeanCurvatureForce *curv_force, Type::Prec curv_impact, const ObjectManager *obj_manager) 
					: MeanCurvatureSpeedFunction(curv_force, curv_impact), m_obj_manager(obj_manager) {};
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_REG_SPEED_FUNCTION_H

