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
 * \file lbp.h
   \brief Local Binary Patters.

DESCRIPTION:

	This file contains functions for calculating Local Binary Patters.

	T. Ojala, M. Pietikäinen, and T. Maenpaa. Multiresolution gray-scale and
	rotation invariant texture classification with local binary patterns. IEEE
	Transactions on Pattern Analysis and Machine Intelligence, 24(7):971–987,
	July 2002.
	
	\author Tomas Majtner <172786@mail.muni.cz>
	\date 2015

NOTE:
	An example of use of the Local Binary Patters can be found in
	the file '../../examples/lbptest.cc'.
  			
*/

#ifndef __LBP_H__
#define __LBP_H__

#include "image3d.h"
#include "algo_export.h"

/****************************************************************************\
*
*                     Local Binary Patterns
*
\****************************************************************************/

namespace i3d {

template <class T> I3D_ALGO_EXPORT
	void ComputeLBP(Image3d<T> &img, int P, int R, int RADIUS_STEP, int NUMBER_OF_R, std::vector<double> &feature_vector);

}

#endif