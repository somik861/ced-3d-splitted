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
 * FILE: metrics.h
 *
 * Image comparison
 *
 * Karel Lockenbauer 2014
 */

/** \file 
 * Several method for image comparison
 *
 * \author Karel Lockenbauer 
 * \date 2014
 */


#ifndef __METRICS_H__
#define __METRICS_H__

#ifndef _MSC_VER
#include <cmath>
#endif
#include "image3d.h"
#include "filters.h"
#include "fourier.h"
#include <valarray>
#include <complex>



namespace i3d{

	//--------------------------------------------------------------------------
	/** 
	 * \ingroup metrics
	 * \brief Mean Structural SIMilarity index
	 * 
	 * This metric uses difference in structure of images to assess their similarity.
	 * It uses gauss function to minimize impact of local distortions on result.
	 *
	 * \param[in] imageOriginal 	image used as original
	 * \param[in] imageDistorted 	image which is compared to original
	 * \param[in] gaussSigma 		sigma of gauss
	 * \param[in] gaussSize 		size of gauss window
	 * \param[in] constant1 		small constant to avoid instability when images are dark
	 * \param[in] constant2 		small constant to avoid instability when images have low contrast
	 */
	//--------------------------------------------------------------------------
	template<class VOXEL>
	double Mssim (const Image3d<VOXEL> imageOriginal, const Image3d<VOXEL> imageDistorted,
					double gaussSigma = 1.5, float gaussSize = 11, double constant1 = 0.01, double constant2 = 0.03);


	//--------------------------------------------------------------------------
	/** 
	 * \ingroup metrics
	 * \brief Mean Square Error
	 * 
	 * This metric computes comparison as squared difference of pixels in original
	 * and disorted image.
	 *
	 * \param[in] imageOriginal 	image used as original
	 * \param[in] imageDistorted 	image which is compared to original
	 * \param[in] linearStretch 	whether linear stretch should be used
	 */
	//--------------------------------------------------------------------------
	template<class VOXEL>
	double MSE (const Image3d<VOXEL> imageOriginal, const Image3d<VOXEL> imageDistorted, bool linearStretch);


	//--------------------------------------------------------------------------
	/** 
	 * \ingroup metrics
	 * \brief Peak Signal-to-Noise Ratio
	 * 
	 * It uses MSE. It adjust result of MSE to avoid big numbers.
	 * In this case it uses maximum intensity of original image.
	 *
	 * \param[in] imageOriginal 	image used as original
	 * \param[in] imageDistorted 	image which is compared to original
	 * \param[in] linearStretch 	whether linear stretch should be used in MSE
	 */
	//--------------------------------------------------------------------------
	template<class VOXEL>
	double PSNR (const Image3d<VOXEL> imageOriginal, const Image3d<VOXEL> imageDisorted, bool linearStrech);


	//--------------------------------------------------------------------------
	/** 
	 * \ingroup metrics
	 * \brief Fourier Shell Correlation
	 * 
	 * It uses Fourier transform to compare images.
	 *
	 * \param[in] imageOriginal 	image used as original
	 * \param[in] imageDistorted 	image which is compared to original
	 */
	//--------------------------------------------------------------------------
	template<class VOXEL>
	double FSC (const Image3d<VOXEL> imageOriginal, const Image3d<VOXEL> imageDistorted);

	
}

#endif