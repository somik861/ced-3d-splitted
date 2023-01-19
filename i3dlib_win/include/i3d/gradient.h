/*
 * \file gradient.h
 *
 * \brief gradient 
 * 
 * 
 *
 * \author Pavel Matula (pam@fi.muni.cz) 
 * \date 2007
 */

#ifndef __GRADIENT_H__
#define __GRADIENT_H__

#include "image3d.h"
#include "algo_export.h"

namespace i3d {
	/** 
		\brief computes image gradient

		computes gradient approximation using central differences 

		\param img		input image
		\param gimg		output gradient image
	*/
	template <class VOXEL_TYPE> void GradientMagnitude(const Image3d<VOXEL_TYPE> &img, Image3d<float> &gimg);

	/** 
		\brief computes square of image gradient

		computes gradient approximation using central differences

		\param img		input image
		\param gimg		output gradient image
	*/
	template <class VOXEL_TYPE> void GradientMagnitude2(const Image3d<VOXEL_TYPE> &img, Image3d<float> &gimg);

	/** 
		\brief computes the image gradient using central differences

		Computes gradient approximation using central differences

		Function assumes Neumann boundary contition, i.e. boundary voxels are set to zero.

		\param img		input image
		\param dx		computed derivative with respect to x
		\param dy		computed derivative with respect to y
		\param dz		computed derivative with respect to z
	*/
	template <class VOXEL_TYPE> I3D_ALGO_EXPORT void Gradient(const Image3d<VOXEL_TYPE> &img, Image3d<float> &dx, Image3d<float> &dy, Image3d<float> &dz);


	/** 
		\brief computes image x gradient using central difference scheme

		Computes image gradient using central difference scheme. Gradient is NOT normalized by grid constant.
		Normalization can be performed later by function MultiplyImage(img, 2 * img.GetResolutionX())

		Function assumes Neumann boundary contition, i.e. boundary voxels are set to zero.
		
		\param img		input image
		\param dx		derivative with respect to x
	*/
	template <class VOXEL_TYPE> I3D_ALGO_EXPORT void GradientX(const Image3d<VOXEL_TYPE> &img, Image3d<float> &dx);

	/** 
		\brief computes image y gradient using central difference scheme

		Computes image gradient using central difference scheme. Gradient is NOT normalized by grid constant.
		Normalization can be performed later by function MultiplyImage(img, 2 * img.GetResolutionY())

		Function assumes Neumann boundary contition, i.e. boundary voxels are set to zero.
		
		\param img		input image
		\param dy		derivative with respect to y
	*/
	template <class VOXEL_TYPE> I3D_ALGO_EXPORT void GradientY(const Image3d<VOXEL_TYPE> &img, Image3d<float> &dy);

	/** 
		\brief computes image z gradient using central difference scheme

		Computes image gradient using central difference scheme. Gradient is NOT normalized by grid constant.
		Normalization can be performed later by function MultiplyImage(img, 2 * img.GetResolutionZ())

		Function assumes Neumann boundary contition, i.e. boundary voxels are set to zero.
		
		\param img		input image
		\param dz		derivative with respect to z
	*/
	template <class VOXEL_TYPE> I3D_ALGO_EXPORT void GradientZ(const Image3d<VOXEL_TYPE> &img, Image3d<float> &dz);

	/**
		\brief multiplies each voxel by k

		Multiplies each voxel by the number k
		Value overflow is not tested...

		\param img input as well as output image
		\param k multiplication factor
	*/
	template <class VOXEL_TYPE> I3D_ALGO_EXPORT void MultiplyImage(Image3d<VOXEL_TYPE> &img, VOXEL_TYPE k);

	/**
		\brief square each voxel

		computes square of each voxel
		Value overflow is not tested...

		\param img input as well as output image
	*/
	template <class VOXEL_TYPE> I3D_ALGO_EXPORT void SquareImage(Image3d<VOXEL_TYPE> &img);

	/**
		\brief add images

		Add two images. The second image is added to the first one. Images must have the same size. If not InternalException 
		is raised

		\param img1 input as well as the output image
		\param img2 image to add up
	*/
	template <class VOXEL_TYPE> I3D_ALGO_EXPORT void AddImage(Image3d<VOXEL_TYPE> &img1, const Image3d<VOXEL_TYPE> &img2);

}
#endif

