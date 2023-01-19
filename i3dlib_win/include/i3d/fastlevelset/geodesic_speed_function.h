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
 * geodesic_speed_function.h
 *
 * Geodesic speed function
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_GEODESIC_SPEED_FUNCTION_H
#define FLS_GEODESIC_SPEED_FUNCTION_H

#include "geometric_speed_function.h"
#include "advection_force.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                Class GeodesicSpeedFunction                  //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Geodesic speed function. */
		class GeodesicSpeedFunction : public GeometricSpeedFunction
		{
			protected:
				/** Advection force. */
				const AdvectionForce *m_adv_force;
				/** Relative impact of the advection force. */
				Type::Prec m_adv_impact;

			public:
				/** Constructor. */
				GeodesicSpeedFunction(const EdgeStoppingFunction *edge_stopping_function, const InflationForce *inf_force, const MeanCurvatureForce *curv_force, 
					                  Type::Prec curv_impact, const AdvectionForce *adv_force, Type::Prec adv_impact)
					: GeometricSpeedFunction(edge_stopping_function, inf_force, curv_force, curv_impact), m_adv_force(adv_force), m_adv_impact(adv_impact) {};
				/** Destructor. */
				virtual ~GeodesicSpeedFunction() { delete m_adv_force; };
				/** Get the speed at the i-th grid point. */
				virtual Type::Prec Get(Type::Size i) const { return GeometricSpeedFunction::Get(i) + m_adv_impact * m_adv_force -> Get(i); };
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_GEODESIC_SPEED_FUNCTION_H

