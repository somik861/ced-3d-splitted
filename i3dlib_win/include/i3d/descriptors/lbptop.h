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
 * \file lbptop.h
   \brief 3D LBP-TOP texture features.

DESCRIPTION:

	This file contains functions for calculating 3D LBP-TOP features.

	G. Zhao and M. Pietikäinen. Dynamic Texture Recognition Using Local
	Binary Patterns with an Application to Facial Expressions. IEEE Transactions
	on Pattern Analysis and Machine Intelligence, 29(6):915–928, June
	2007.
	
	M. Pietikäinen, A. Hadid, G. Zhao, and T. Ahonen. Computer Vision Using
	Local Binary Patterns. Computational imaging and vision. Springer
	Verlag, London, 2011.
	
	\author Tomas Majtner <172786@mail.muni.cz>
	\date 2015

NOTE:
	An example of use of the LBP-TOP features can be found in
	the file '../../examples/lbptoptest.cc'.
  			
*/

#ifndef __LBPTOP_H__
#define __LBPTOP_H__

#include "image3d.h"
#include "algo_export.h"

/****************************************************************************\
*
*                     3D LBP-TOP features
*
\****************************************************************************/

namespace i3d {

template <class T> I3D_ALGO_EXPORT
	void ComputeLBP_TOP(const Image3d<T> &img_orig, std::vector<double> &feature_vector);

}

#endif