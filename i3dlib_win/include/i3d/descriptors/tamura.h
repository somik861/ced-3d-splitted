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
 * \file tamura.h
   \brief 2D and 3D Tamura texture features.

DESCRIPTION:

	This file contains functions for calculating 2D/3D Tamura features.

	H. Tamura, S. Mori, and T. Yamawaki. Textural features corresponding to
	visual perception. IEEE Transactions on Systems, Man and Cybernetics,
	8(6):460–473, 1978.
	
	T. Majtner, D. Svoboda. Extension of Tamura Texture Features for 3D Fluorescence
	Microscopy. In 2nd Joint 3DIM/3DPVT Conference: 3D Imaging,
	Modeling, Processing, Visualization and Transmission (3DimPVT). Los Alamitos,
	California, USA: IEEE Computer Society, 2012. Pages 301–307, ISBN
	978-0-7695-4873-9.
	
	\author Tomas Majtner <172786@mail.muni.cz>
	\date 2015

NOTE:
	An example of use of the class TamuraFeatures<> can be found in
	the file '../../examples/tamuratest.cc'.
  			
*/

#ifndef __TAMURA_H__
#define __TAMURA_H__

#include "image3d.h"
#include "algo_export.h"

/****************************************************************************\
*
*                     2D & 3D Tamura features
*
\****************************************************************************/

namespace i3d {

template <class T> I3D_ALGO_EXPORT
	double Neighbours2D (const Image3d<T> &img, int from_y, int to_y, int from_x, int to_x, int min_val, int normal);

template <class T> I3D_ALGO_EXPORT
	double Neighbours3D (const Image3d<T> &img, int from_z, int to_z, int from_y, int to_y, int from_x, int to_x, int min_val, int normal);

template <class T> I3D_ALGO_EXPORT
	void ComputeTamura2D (const Image3d<T> &img, std::vector<double> &feature_vector);

template <class T> I3D_ALGO_EXPORT
	void ComputeTamura3D (const Image3d<T> &img_orig, std::vector<double> &feature_vector);

}

#endif