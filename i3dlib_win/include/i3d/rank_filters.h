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
* FILE: rank_filters.h
*
* Image filtering using rank filters
*/

/** \file 
* Rank-filters based image filtering functions.
*/

#ifndef __RANK_FILTERS_H__
#define __RANK_FILTERS_H__

#ifdef __GNUG__
#pragma interface
#endif

#include "image3d.h"
#include "neighbours.h" 

namespace i3d {

	/** \ingroup if
	\brief Apply median filter on image.

	Applies median filter on the input image using given neighbourhood. Result is stored in the output image (this image is going to be resized according to the input).
	Boundary conditions are not solved in any way (just the available voxels are used for computation), if you wish to use for example neuman boundary condition, you have to padd the input image yourself.
	This function is currently faster than the one taking lat_radius and axi_radius (tested on the classical 3D 27-neighbourhood (26 + 1)).

	\param[in] img_in	input image to be filtered
	\param[out] img_out	filtered output of the input image
	\param[in] neib		neighbourhood in whitch to look for the median value for each image element
	*/
	template <class T> I3D_ALGO_EXPORT 
		void MedianFilter(const Image3d<T>& img_in, Image3d<T>& img_out,
		const Neighbourhood& neib);

	/// Computes exact median filter using the "box" neighbourhood of given size (lat_radius = radius in xy; axi_radius = radius in z)
	template <class T> I3D_ALGO_EXPORT
		void MedianFilter(const i3d::Image3d<T> &input, i3d::Image3d<T> &output, int lat_radius = 1, int axi_radius = 1);

	/// Computes median filter approximation - if you wish to have exact result, use MedianFilter function (doesn't matter which one)
	template <class T> I3D_ALGO_EXPORT
		void SeparableMedianFilter(const i3d::Image3d<T> &input, i3d::Image3d<T> &output, int lat_radius = 1, int axi_radius = 1);

} //namespace i3d ends here

#endif // __RANK_FILTERS_H__
