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
 * geometric_speed_function.h
 *
 * Geometric speed function
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_GEOMETRIC_SPEED_FUNCTION_H
#define FLS_GEOMETRIC_SPEED_FUNCTION_H

#include "mean_curvature_speed_function.h"
#include "edge_stopping_function.h"
#include "inflation_force.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                Class GeometricSpeedFunction                 //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Geometric speed function. */
		class GeometricSpeedFunction : public MeanCurvatureSpeedFunction
		{
			protected:
				/** Edge-stopping function. */
				const EdgeStoppingFunction *m_edge_stopping_function;
				/** Inflation force. */
				const InflationForce *m_inf_force;

			public:
				/** Constructor. */
				GeometricSpeedFunction(const EdgeStoppingFunction *edge_stopping_function, const InflationForce *inf_force, const MeanCurvatureForce *curv_force, Type::Prec curv_impact)
					: MeanCurvatureSpeedFunction(curv_force, curv_impact), m_edge_stopping_function(edge_stopping_function), m_inf_force(inf_force) {};
				/** Destructor. */
				virtual ~GeometricSpeedFunction() { delete m_edge_stopping_function; delete m_inf_force; };
				/** Get the speed at the i-th grid point. */
				virtual Type::Prec Get(Type::Size i) const { return m_edge_stopping_function -> Get(i) * (m_inf_force -> Get(i) + MeanCurvatureSpeedFunction::Get(i)); };
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_GEOMETRIC_SPEED_FUNCTION_H

