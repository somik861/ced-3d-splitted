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
 * \file lbpplaton.h
   \brief 3D LBP-platonic texture features.

DESCRIPTION:

	This file contains functions for calculating 3D LBP-platonic features.

	T. Majtner, D. Svoboda. Comparison of 3D Texture-based Image Descriptors
	in Fluorescence Microscopy. In 16th InternationalWorkshop on Combinatorial
	Image Analysis (IWCIA). Lecture Notes in Computer Science, Volume
	8466. Switzerland: Springer International Publishing, 2014. Pages 186–195,
	ISBN 978-3-319-07147-3.
	
	\author Tomas Majtner <172786@mail.muni.cz>
	\date 2015

NOTE:
	An example of use of the 3D LBP-platonic features can be found in
	the file '../../examples/lbpplatontest.cc'.
  			
*/

#ifndef __LBPPLATON_H__
#define __LBPPLATON_H__

#include "image3d.h"
#include "algo_export.h"

/****************************************************************************\
*
*                     3D LBP-platonic features
*
\****************************************************************************/

namespace i3d {

template <class T> I3D_ALGO_EXPORT
	void ComputeLBP_PLATON(const Image3d<T> &img_orig, int SOLID, std::vector<double> &feature_vector);

}

#endif