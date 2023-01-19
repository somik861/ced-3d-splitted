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
 * FILE: edge.h
 *
 * 2D/3D edge detection operators
 *
 * Marek Kasik (xkasik1@fi.muni.cz) 2003
 */

#ifndef __EDGE_H__
#define __EDGE_H__

#ifdef __GNUG__
#pragma interface
#endif

#include "image3d.h"
#include "algo_export.h"

namespace i3d {

/** \defgroup edge Edge detection filters */
///@{

#ifdef WITH_FFTW
/** 
    Apply 3D Canny edge detector on input image
    in is input image
    out is output image
    sigma is standard deviation of Gauss filter
    scale scales resulting values 
*/
template <class VOXEL> I3D_ALGO_EXPORT void Canny3D(const Image3d<VOXEL>& in,Image3d<VOXEL>& out,float sigma,float scale);
#endif //fftw


/**
    Apply compass version of 3D Sobel filter on input image
    in is input image
    out is output image
*/
template <class VOXEL> I3D_ALGO_EXPORT void CompassSobel3D(const Image3d<VOXEL>& in,Image3d<VOXEL>& out);


/**
    Apply simple 3D edge operator on input image
    in is input image
    out is output image
	clamp - stretch side voxels
*/
template <class VOXEL> I3D_ALGO_EXPORT void EstimateGradient1_3D(const Image3d<VOXEL>& in,Image3d<VOXEL>& out,bool clamp);


/**
    Apply simple 3D edge operator on input image
    in is input image
    out is output image
    clamp - stretch side voxels
*/
template <class VOXEL> I3D_ALGO_EXPORT void EstimateGradient2_3D(const Image3d<VOXEL>& in,Image3d<VOXEL>& out,bool clamp);

/** Estimate the gradient magnitude of given image using the central difference scheme. The central differences are 
    substituted with the right or left ones on the image border.
*/
I3D_ALGO_EXPORT void EstimateGradientMagnitude(const Image3d<float> &in, Image3d<float> &out);

/**
    Apply 3D Kirsch filter on input image
    in is input image
    out is output image
*/
template <class VOXEL> I3D_ALGO_EXPORT void Kirsch3D(const Image3d<VOXEL>& in,Image3d<VOXEL>& out);


/**
    Apply 3D Laplace filter on input image
    in is input image
    out is output image
*/
template <class VOXEL> I3D_ALGO_EXPORT void Laplace3D(const Image3d<VOXEL>& in,Image3d<VOXEL>& out);


/**
    Apply 3D Marr-Hildreth edge detector on input image
		This edge detector doesn't respect anisotropic image
    in is input image
    out is output image
    sigma1 is standard deviation of Gauss filter
    sigma2 is standard deviation of Gauss filter
*/
template <class VOXEL> I3D_ALGO_EXPORT void MarrHildreth3D(const Image3d<VOXEL>& in,Image3d<VOXEL>& out,double sigma1, double sigma2);


/**
    Apply 3D Prewitt filter on input image
    in is input image
    out is output image
*/
template <class VOXEL> I3D_ALGO_EXPORT void Prewitt3D(const Image3d<VOXEL>& in,Image3d<VOXEL>& out);


/**
    Apply 3D Roberts filter on input image
    in is input image
    out is output image
*/
template <class VOXEL> I3D_ALGO_EXPORT void Roberts3D(const Image3d<VOXEL>& in,Image3d<VOXEL>& out);


/**
    Apply 3D Robinson filter on input image
    in is input image
    out is output image
*/
template <class VOXEL> I3D_ALGO_EXPORT void Robinson3D(const Image3d<VOXEL>& in,Image3d<VOXEL>& out);


/**
    Apply 3D Shen-Castan edge detector on input image
		This edge detector doesn't respect anisotropic image
    in is input image
    out is output image
    p is parameter to ISEF filter
    WinHalfSize is half-size of window for adaptive gradient function
*/
template <class VOXEL> I3D_ALGO_EXPORT void ShenCastan3D(const Image3d<VOXEL>& in,Image3d<VOXEL>& out,double p,int WinHalfSize);


/**
    Apply 3D Sobel filter on input image
    in is input image
    out is output image
*/
template <class VOXEL> I3D_ALGO_EXPORT void Sobel3D(const Image3d<VOXEL>& in,Image3d<VOXEL>& out);


#ifdef WITH_FFTW
/**
    Apply 2D Canny edge detector on input image separately for each slice
    in is input image
    out is output image
    sigma is standard deviation of Gauss filter
    scale scales resulting values 
*/
template <class VOXEL> I3D_ALGO_EXPORT void Canny2D(const Image3d<VOXEL>& in,Image3d<VOXEL>& out,float sigma,float scale);
#endif //fftw


/**
    Apply compass version of 2D Sobel filter on input image separately for each slice
    in is input image
    out is output image
*/
template <class VOXEL> I3D_ALGO_EXPORT void CompassSobel2D(const Image3d<VOXEL>& in,Image3d<VOXEL>& out);


/**
    Apply simple 2D edge operator on input image separately for each slice in
    in is input image
    out is output image
    clamp - stretch side voxels
*/
template <class VOXEL> I3D_ALGO_EXPORT void EstimateGradient1_2D(const Image3d<VOXEL>& in,Image3d<VOXEL>& out,bool clamp);


/**
    Apply simple 2D edge operator on input image separately for each slice
    in is input image
    out is output image
    clamp - stretch side voxels
*/
template <class VOXEL> I3D_ALGO_EXPORT void EstimateGradient2_2D(const Image3d<VOXEL>& in,Image3d<VOXEL>& out,bool clamp);


/**
    Apply 2D Kirsch filter on input image separately for each slice 
    in is input image
    out is output image
*/
template <class VOXEL> I3D_ALGO_EXPORT void Kirsch2D(const Image3d<VOXEL>& in,Image3d<VOXEL>& out);


/**
    Apply 2D Laplace filter on input image separately for each slice 
    in is input image
    out is output image
*/
template <class VOXEL> I3D_ALGO_EXPORT void Laplace2D(const Image3d<VOXEL>& in,Image3d<VOXEL>& out);


/**
    Apply 2D Marr-Hildreth edge detector on input image separately for each slice
		This edge detector doesn't respect anisotropic image
    in is input image
    out is output image
    sigma1 is standard deviation of Gauss filter
    sigma2 is standard deviation of Gauss filter
*/
template <class VOXEL> I3D_ALGO_EXPORT void MarrHildreth2D(const Image3d<VOXEL>& in,Image3d<VOXEL>& out,double sigma1, double sigma2);


/**
    Apply 2D Prewitt filter on input image separately for each slice 
    in is input image
    out is output image
*/
template <class VOXEL> I3D_ALGO_EXPORT void Prewitt2D(const Image3d<VOXEL>& in,Image3d<VOXEL>& out);


/**
    Apply 2D Shen-Castan edge detector on input image separately for each slice
		This edge detector doesn't respect anisotropic image
    in is input image
    out is output image
    p is parameter to ISEF filter
    WinHalfSize is half-size of window for adaptive gradient function
*/
template <class VOXEL> I3D_ALGO_EXPORT void ShenCastan2D(const Image3d<VOXEL>& in,Image3d<VOXEL>& out,double p,int WinHalfSize);


/**
    Apply 2D Sobel filter on input image separately for each slice 
    in is input image
    out is output image
*/
template <class VOXEL> I3D_ALGO_EXPORT void Sobel2D(const Image3d<VOXEL>& in,Image3d<VOXEL>& out);


/**
    Apply 2D Roberts filter on input image separately for each slice 
    in is input image
    out is output image
*/
template <class VOXEL> I3D_ALGO_EXPORT void Roberts2D(const Image3d<VOXEL>& in,Image3d<VOXEL>& out);


/**
    Apply 2D Robinson filter on input image separately for each slice
    in is input image
    out is output image
*/
template <class VOXEL> I3D_ALGO_EXPORT void Robinson2D(const Image3d<VOXEL>& in,Image3d<VOXEL>& out);


/**
    Apply 3D hysteresis threshold on input image
    data is input image and output image
    lowThreshold is lower value of threshold
    highThreshold is higher value of threshold
*/
template <class VOXEL> I3D_ALGO_EXPORT void hystThres3D(Image3d<VOXEL>& data,unsigned short lowThreshold,unsigned short highThreshold);


/**
    Apply 2D hysteresis threshold on input image separately for each slice
    data is input image and output image
    lowThreshold is lower value of threshold
    highThreshold is higher value of threshold
*/
template <class VOXEL> I3D_ALGO_EXPORT void hystThres2D(Image3d<VOXEL>& data,unsigned short lowThreshold,unsigned short highThreshold);


///@} end of edge detection group

} // i3d namespace

#endif
