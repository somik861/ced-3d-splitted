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
 * rd_speed_function.h
 *
 * Rousson-Deriche speed function
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_RD_SPEED_FUNCTION_H
#define FLS_RD_SPEED_FUNCTION_H

#include "reg_speed_function.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//              Class RoussonDericheSpeedFunction              //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Rousson-Deriche speed function. */
		class RoussonDericheSpeedFunction : public RegionSpeedFunction
		{
			public:
				/** Constructor. */
				RoussonDericheSpeedFunction(const MeanCurvatureForce *curv_force, Type::Prec curv_impact, const ObjectManager *obj_manager) 
					: RegionSpeedFunction(curv_force, curv_impact, obj_manager) {};
				/** Get the speed at the i-th grid point. */
				virtual Type::Prec Get(Type::Size i) const { return MeanCurvatureSpeedFunction::Get(i) - m_obj_manager -> VarForeground(i) + m_obj_manager -> VarBackground(i); };
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_RD_SPEED_FUNCTION_H

