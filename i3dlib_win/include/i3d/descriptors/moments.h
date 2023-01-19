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
 * \file moments.h
   \brief Central moments.

DESCRIPTION:

	This file contains functions for calculating Central moments.

	J. Flusser, B. Zitová, and T. Suk. Moments and Moment Invariants in Pattern
	Recognition. Wiley Publishing, 2009.
	
	\author Tomas Majtner <172786@mail.muni.cz>
	\date 2015

NOTE:
	An example of use of the Central moments can be found in
	the file '../../examples/momentstest.cc'.
  			
*/

#ifndef __MOMENTS_H__
#define __MOMENTS_H__

#include "image3d.h"
#include "algo_export.h"

/****************************************************************************\
*
*                     Central moments
*
\****************************************************************************/

namespace i3d {

template <class T> I3D_ALGO_EXPORT
	void ComputeMoments(Image3d<T> &img, std::vector<double> &feature_vector);

}

#endif