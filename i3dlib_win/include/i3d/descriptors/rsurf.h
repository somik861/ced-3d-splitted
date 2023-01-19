/*
 * i3dlib - image manipulation library
 *
 * Copyright (C) 2000-2015   Centre for Biomedical Image Analysis (CBIA)
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
 * License along with this library; if not, write to the Freere
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
 
/** 
 * \file rsurf.h
   \brief 2D and 3D RSurf features.

DESCRIPTION:

	This file contains functions for calculating 2D/3D RSurf features.

	T. Majtner, R. Stoklasa, D. Svoboda. RSurf – The Efficient Texture-based
	Descriptor for Fluorescence Microscopy Images of HEp-2 Cells. In 22nd
	International Conference on Pattern Recognition (ICPR). Los Alamitos, California,
	USA: IEEE Computer Society, 2014. Pages 1194–1199, ISBN 978-1-
	4799-5208-3.
	
	\author Tomas Majtner <172786@mail.muni.cz>
	\date 2015

NOTE:
	An example of use of the RSurf features can be found in
	the file '../../examples/rsurftest.cc'.
  			
*/

#ifndef __RSURF_H__
#define __RSURF_H__

#include "image3d.h"
#include "algo_export.h"

/****************************************************************************\
*
*                     2D & 3D RSurf features
*
\****************************************************************************/

namespace i3d {

template <class T> I3D_ALGO_EXPORT
	void ComputeRSurf(Image3d<T> &img, std::vector<double> &feature_vector);

}

#endif