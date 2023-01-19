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
 * FILE: fourier.h
 *
 * Image convolution
 *
 * David Svoboda <svoboda@fi.muni.cz> 2009
 */

/** \file 
 * Forward and backward Fourier transform
 *
 * \author David Svoboda <svoboda@fi.muni.cz> 
 * \date 2009
 */

#ifndef __FOURIER_H__
#define __FOURIER_H__

#ifdef __GNUG__
#pragma interface
#endif

#include <complex>
#include "image3d.h"
#include "algo_export.h"

namespace i3d {

//--------------------------------------------------------------------------
/** 
 * \ingroup transforms
 * \brief Handy function estimating size of memory required for one fftw buffer.
 *
 * \param[in] img_sz 		size of an image that should be submitted to fftw
 */
//--------------------------------------------------------------------------
template <class S> I3D_ALGO_EXPORT
size_t GetFFTWBufferSize(Vector3d<size_t> img_sz);

//--------------------------------------------------------------------------
/** 
 * \ingroup transforms
 * \brief Fast Fourier transform.
 *
 * This function implements the real to complex Fourier transform.
 * The output complex image is of half size as it is pointless
 * to store the whole image when it is symmetric (numbers are conjugated).
 *
 * \param[in] real_img 		input image (spatial domain)
 * \param[out] complex_img 	output image (frequency domain)
 * \param[in] normalize		whether to use normalized basis functions
 */
//--------------------------------------------------------------------------
template < class T, class PRECISION> I3D_ALGO_EXPORT
void FFT(const Image3d<T> &real_img, 
			Image3d< std::complex<PRECISION> /* */ > &complex_img,
			bool normalize = false);

//--------------------------------------------------------------------------
/** 
 * \ingroup transforms
 * \brief inverse Fast Fourier transform.
 *
 * This function implements the inverse complex to real Fourier transform.
 * The input complex image is of the half size as we expect this image
 * to be symmetric (numbers are conjugated).
 *
 * \param[in] in 		input image (frequency domain)
 * \param[out] out 		output image (spatial domain)
 * \param[in] normalize		whether to use normalized basis functions
 */
//--------------------------------------------------------------------------
template < class T, class PRECISION> I3D_ALGO_EXPORT
void IFFT(const Image3d< std::complex<PRECISION> /* */ > &in, 
			 Image3d<T> &out,
			 bool normalize = false);

//--------------------------------------------------------------------------
/** 
 * \ingroup transforms
 * \brief Time/Fourier domain shift.
 *
 * This function implements the shift of the signal according to the specified 
 * vector. If the data are shifted outside the image domain they "rotate",
 * i.e. their enter the image for the other side. This behaviour stems from
 * the fact, that the image is taken to be strictly periodical.
 *
 * \param[in,out] img 		image (time or frequency domain)
 * \param[in] shift			vector responsible for the data shift
 */
//--------------------------------------------------------------------------
template <class T> I3D_ALGO_EXPORT
void FFTshift(Image3d<T> &img, const Vector3d<int> &shift);

} // namespace i3d ends here

#endif // __FOURIER_H__
