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
 * object.h
 *
 * Class representing an object used in the region-based models
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_OBJECT_H
#define FLS_OBJECT_H

#include "defs.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                        Class Object                         //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Class representing an object used in the region-based models. */
		class Object
		{
			private:
				/** Number of grid points. */
				Type::Size m_num;
				/** Sum of intensities at grid points. */
				Type::Prec m_intensity_sum;
				/** Sum of squared intensities at grid points. */
				Type::Prec m_sqr_intensity_sum;
				/** Average intensity obtained in the last synchronization. */
				Type::Prec m_avg;
				/** Variance obtained in the last synchronization. */
				Type::Prec m_variance;
				/** Difference in the average intensity obtained in the last synchronization. */
				Type::Prec m_last_diff;
				/** Accumulated differences in the average intensity. */
				Type::Prec m_diff_sum;

			public:
				/** Constructor. */
				Object() : m_num(0), m_intensity_sum(Type::Prec(0)), m_sqr_intensity_sum(Type::Prec(0)), m_avg(Type::Prec(0)), 
					       m_variance(Type::Prec(0)), m_last_diff(Type::Prec(0)), m_diff_sum(Type::Prec(0)) {};
				/** Get the average intensity. */
				Type::Prec AvgIntensity() const { return m_avg; };
				/** Get the variance. */
				Type::Prec Variance() const { return m_variance; };
				/** Get the size of the object. */
				Type::Size Size() const { return m_num; };
				/** Add a grid point of given intensity to the object. */
				void AddPoint(Type::Prec intensity) { ++m_num; m_intensity_sum += intensity; m_sqr_intensity_sum += intensity * intensity; };
				/** Remove a grid point of given intensity from the object. */
				void RemovePoint(Type::Prec intensity) { --m_num; m_intensity_sum -= intensity; m_sqr_intensity_sum -= intensity * intensity;};
				/** Object synchronization. Recompute the average intensity and accumulate the difference in the former and new average intensity. */
				void Synchronize();
				/** Get accumulated differences in the average intensity and reset the counter. */
				Type::Prec FlushDiff() { Type::Prec diff = m_diff_sum; m_diff_sum = Type::Prec(0); return diff; };
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_OBJECT_H

