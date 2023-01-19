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
 * \file mpeg7ehd.h
   \brief 2D and 3D MPEG-7 EHD features.

DESCRIPTION:

	This file contains functions for calculating 2D/3D MPEG-7 EHD features.

	B. S. Manjunath, P. Salembier, and T. Sikora, editors. Introduction to
	MPEG-7: Multimedia Content Description Interface. Wiley & Sons, Inc.,
	New York, USA, Apr. 2002.
	
	T. Majtner, D. Svoboda. Texture Analysis Using 3D Gabor Features and
	3D MPEG-7 Edge Histogram Descriptor in Fluorescence Microscopy. In
	4th International Conference on 3D Imaging (IC3D). Los Alamitos, California,
	USA: IEEE Computer Society, 2014. Pages 1–7, ISBN 978-1-4799-8023-9.
	
	\author Tomas Majtner <172786@mail.muni.cz>
	\date 2015

NOTE:
	An example of use of MPEG-7 EHD features can be found in
	the file '../../examples/mpeg7ehdtest.cc'.
  			
*/

#ifndef __MPEG7EHD_H__
#define __MPEG7EHD_H__

#include "image3d.h"
#include "algo_export.h"

/****************************************************************************\
*
*                     2D & 3D MPEG-7 EHD features
*
\****************************************************************************/

namespace i3d {

template <class T> I3D_ALGO_EXPORT
	void Compute2DEHD(Image3d<T> &img, std::vector<double> &feature_vector);

template <class T> I3D_ALGO_EXPORT
	void Compute3DEHD(Image3d<T> &img, std::vector<double> &feature_vector);

}

#endif