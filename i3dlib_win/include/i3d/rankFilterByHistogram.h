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
* FILE: RankFilterByHistogram.h
*
* Image filtering using rank filters
*
* Radoslav Stefanik <256711@mail.muni.cz> 2010
*/

/** \file rankFilterByHistogram.h
* Rank-filters based image filtering functions.
*/

#ifndef RANKFILTERBYHISTOGRAM_H_INCLUDED
#define RANKFILTERBYHISTOGRAM_H_INCLUDED

#include "image3d.h"
#include "neighbours.h"

namespace i3d {

    /** \ingroup if
	\brief Apply rank filter on image.

	Applies rank filter on the input image using given neighbourhood. Result is stored in the output image (this image is going to be resized according to the input).

	\param[in] imgIn	input image to be filtered
	\param[out] imgOut	filtered output of the input image
	\param[in] SEin		Structural Element of rank filter in whitch we look for the desired value for each image element
    \param[in] rank     order of element we choose from Structural Element

	\author Radoslav Stefanik (256711@mail.muni.cz)
	\date 2010
	*/

    template<typename T> I3D_ALGO_EXPORT
    void rankFilterByHistogram(const i3d::Image3d<T>& imgIn, i3d::Image3d<T>& imgOut,
             Neighbourhood& SEin, int rank);

}

#endif // RANKFILTERBYHISTOGRAM_H_INCLUDED
