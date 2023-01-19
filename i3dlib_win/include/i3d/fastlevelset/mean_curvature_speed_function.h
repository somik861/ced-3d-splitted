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
 * mean_curvature_speed_function.h
 *
 * Speed function intended for the mean curvature motion
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_MEAN_CURVATURE_SPEED_FUNCTION_H
#define FLS_MEAN_CURVATURE_SPEED_FUNCTION_H

#include "speed_function.h"
#include "mean_curvature_force.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//              Class MeanCurvatureSpeedFunction               //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Speed function intended for the mean curvature motion. */
		class MeanCurvatureSpeedFunction : public SpeedFunction
		{
			protected:
				/** Mean curvature force. */
				const MeanCurvatureForce *m_curv_force;
				/** Relative impact of the mean curvature force. */
				Type::Prec m_curv_impact;

			public:
				/** Constructor. */
				MeanCurvatureSpeedFunction(const MeanCurvatureForce *curv_force, Type::Prec curv_impact) : SpeedFunction(), m_curv_force(curv_force), m_curv_impact(curv_impact) {};
				/** Destructor. */
				virtual ~MeanCurvatureSpeedFunction() { delete m_curv_force; };
				/** Get the speed at the i-th grid point. */
				virtual Type::Prec Get(Type::Size i) const { return m_curv_impact * m_curv_force -> Get(i); };
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_MEAN_CURVATURE_SPEED_FUNCTION_H

