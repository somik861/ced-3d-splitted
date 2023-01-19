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
 * cv_speed_function.h
 *
 * Chan-Vese speed function
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_CV_SPEED_FUNCTION_H
#define FLS_CV_SPEED_FUNCTION_H

#include "reg_speed_function.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                 Class ChanVeseSpeedFunction                 //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Chan-Vese speed function. */
		class ChanVeseSpeedFunction : public RegionSpeedFunction
		{
			protected:
				/** Relative impact of the foreground. */
				Type::Prec m_foreground_impact;
				/** Relative impact of the background. */
				Type::Prec m_background_impact;

			public:
				/** Constructor. */
				ChanVeseSpeedFunction(const MeanCurvatureForce *curv_force, Type::Prec curv_impact, const ObjectManager *obj_manager, Type::Prec foreground_impact, Type::Prec background_impact)
					: RegionSpeedFunction(curv_force, curv_impact, obj_manager), m_foreground_impact(foreground_impact), m_background_impact(background_impact) {};
				/** Get the speed at the i-th grid point. */
				virtual Type::Prec Get(Type::Size i) const 
				{ 
					return MeanCurvatureSpeedFunction::Get(i) - m_foreground_impact * m_obj_manager -> SqrDevForeground(i) + m_background_impact * m_obj_manager -> SqrDevBackground(i);
				}
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_CV_SPEED_FUNCTION_H

