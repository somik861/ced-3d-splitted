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
 * mean_shift.h
 *
 * Mean shift algorithms
 *
 * Martin Maška (xmaska@fi.muni.cz) 2009
 */

#ifndef __MEAN_SHIFT_H__
#define __MEAN_SHIFT_H__

#include "image3d.h"
#include "algo_export.h"

namespace i3d
{
	/** Mean shift filtering algorithm. */
	template <class T> I3D_ALGO_EXPORT void MeanShiftFiltering(const i3d::Image3d<T> &in, i3d::Image3d<T> &out, 
		                                                       double spatial_kernel_size, double range_kernel_size, bool optimized);

} // namespace i3d

#endif // __MEAN_SHIFT_H__

