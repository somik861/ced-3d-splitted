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
 * nha_mean_curvature_force.h
 *
 * Mean curvature force used in the Nilsson-Heyden algorithm
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_NHA_MEAN_CURVATURE_FORCE_H
#define FLS_NHA_MEAN_CURVATURE_FORCE_H

#include "mean_curvature_force.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                Class NHA_MeanCurvatureForce                 //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Mean curvature force used in the Nilsson-Heyden algorithm. */
		class NHA_MeanCurvatureForce : public MeanCurvatureForce
		{
			private:
				/** Buffer intended for storing the curvature. */
				const int *m_curvature;
				/** Reciprocal size of a circular neighbourhood at which the curvature is approximated. */
				Type::Prec m_reciproc_size;

			public:
				/** Constructor. */
				NHA_MeanCurvatureForce(const int *curvature, Type::Prec reciproc_size) : MeanCurvatureForce(), m_curvature(curvature), m_reciproc_size(reciproc_size) {};
				/** Get the mean curvature force at the i-th grid point. */
				virtual Type::Prec Get(Type::Size i) const { return m_curvature[i] * m_reciproc_size - Type::Prec(0.5); };
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_NHA_MEAN_CURVATURE_FORCE_H

