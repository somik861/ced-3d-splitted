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

/** \file 
 * Image convolution.
 *
 * \author David Svoboda <svoboda@fi.muni.cz> 
 * \date 2009
 */

#ifndef __CONVOLUTION_H__
#define __CONVOLUTION_H__

#ifdef __GNUG__
#pragma interface
#endif

#include "image3d.h"
#include "algo_export.h"

namespace i3d {

	enum BoundaryConditionType {
		BoundaryDirichlet,
		BoundaryNeumann
	};
//--------------------------------------------------------------------------
/** 
 * \ingroup if
 * \brief Convolution implemented via Fast Fourier transform.
 *
 * This function implements the Fourier transform based convolution. The main
 * idea originates from convolution theorem which says that convolution 
 * in image domain corresponds to point-wise multiplication in Fourier 
 * domain. The Fourier domain is realized via FFTW package (www.fftw.org).
 *
 * Moreover, if the image and kernel are too huge to be processed
 * in the computer memory, the image and kernel are tiled into smaller 
 * pieces and the convolution is performed over these small portions. 
 * Finally, the portions are sewed together.
 *
 * The size of the portions is set to be optimal with respect to FFTW.
 *
 * \param[in] img_in 		input image
 * \param[in] kernel 		convolution kernel (image)
 * \param[out] img_out 		output (convolved) image, needn't be allocated
 * \param[in] normalize_kernel ... query whether the kernel is to be normalized (optional parameter)
 *
 * \author David Svoboda <svoboda@fi.muni.cz>
 * \date October 2009
 */
template < class PRECISION, class T_in, class T_out > I3D_ALGO_EXPORT
void Convolution (const Image3d < T_in > &img_in,
						const Image3d < T_in > &kernel,
						Image3d < T_out > &img_out,
						bool normalize_kernel = true,
						BoundaryConditionType boundary_condition = BoundaryDirichlet);

} //namespace i3d ends here

#endif // __CONVOLUTION_H__
