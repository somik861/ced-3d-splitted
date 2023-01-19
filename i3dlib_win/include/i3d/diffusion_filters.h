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
 * diffusion_filters.h
 *
 * Diffusion filters
 *
 * Martin Maška (xmaska@fi.muni.cz) 2008 - 2011
 * 
 */

#ifndef DIFFUSION_FILTERS_H
#define DIFFUSION_FILTERS_H

#include "image3d.h"

namespace i3d
{
	/////////////////////////////////////////////////////////////////
	//                                                             //
	//                           Gauss_LOD                         //
	//                                                             //
	/////////////////////////////////////////////////////////////////

	/** Gaussian (Linear isotropic diffusion) filtering based on the LOD (locally one-dimensional) scheme. The sigma parameter determines the standard deviation of the 
	  * Gaussian filter. Total time of the diffusion process T is given as T = (sigma * sigma) / 2. A time step for one iteration is computed as T / num_iter. The LOD 
	  * scheme is unconditionally stable, i.e. scale-space properties such as the min-max principle or average gray value are preserved for an arbitrary time step. 
	  * However, to obtain a good compromise between efficiency and accuracy, the time step of one iteration should be less than 5. 
	  *
	  * Note: This function is intended only for floating-point scalar images. */
	template <class VOXEL> void Gauss_LOD(Image3d<VOXEL> &img, VOXEL sigma, size_t num_iter);

	/////////////////////////////////////////////////////////////////
	//                                                             //
	//                         GrayGauss_LOD                       //
	//                                                             //
	/////////////////////////////////////////////////////////////////

	/** Gaussian (Linear isotropic diffusion) filtering based on the LOD (locally one-dimensional) scheme. A wrapper of the Gauss_LOD() function for grayscale scalar images. */
	template <class VOXEL, class PRECISION> void GrayGauss_LOD(Image3d<VOXEL> &img, PRECISION sigma, size_t num_iter);

	/////////////////////////////////////////////////////////////////
	//                                                             //
	//                             EED_AOS                         //
	//                                                             //
	/////////////////////////////////////////////////////////////////

	/** Edge-enhancing diffusion filtering based on the semi-implicit AOS-stabilized scheme. The sigma parameter determines the standard deviation of 
	  * the Gaussian filter that is applied before the gradient estimation. The lambda parameter determines a threshold contrast for edges. The tau 
	  * parameter determines a time step of one iteration.
	  *
	  * Note: This function is intended only for floating-point scalar images. */
	template <class VOXEL> void EED_AOS(Image3d<VOXEL> &img, VOXEL sigma, VOXEL lambda, VOXEL tau, size_t num_iter);

	/////////////////////////////////////////////////////////////////
	//                                                             //
	//                           GrayEED_AOS                       //
	//                                                             //
	/////////////////////////////////////////////////////////////////

	/** Edge-enhancing diffusion filtering based on the semi-implicit AOS-stabilized scheme. A wrapper of the EED_AOS() function for grayscale scalar images. */
	template <class VOXEL, class PRECISION> void GrayEED_AOS(Image3d<VOXEL> &img, PRECISION sigma, PRECISION lambda, PRECISION tau, size_t num_iter);
	
	/////////////////////////////////////////////////////////////////
	//                                                             //
	//                             CED_AOS                         //
	//                                                             //
	/////////////////////////////////////////////////////////////////

	/** Coherence-enhancing diffusion filtering based on the semi-implicit AOS-stabilized scheme. The sigma parameter determines the standard deviation of 
	  * the Gaussian filter that is applied before the gradient estimation. The rho parameter determines the standard deviation of the Gaussian filter that
	  * is applied in order to smooth structure tensors. The tau parameter determines a time step of one iteration.
	  *
	  * Note: This function is intended only for floating-point scalar images. */
	template <class VOXEL> void CED_AOS(Image3d<VOXEL> &img, VOXEL sigma, VOXEL rho, VOXEL tau, size_t num_iter);

	/////////////////////////////////////////////////////////////////
	//                                                             //
	//                           GrayCED_AOS                       //
	//                                                             //
	/////////////////////////////////////////////////////////////////

	/** Coherence-enhancing diffusion filtering based on the semi-implicit AOS-stabilized scheme. A wrapper of the CED_AOS() function for grayscale scalar images. */
	template <class VOXEL, class PRECISION> void GrayCED_AOS(Image3d<VOXEL> &img, PRECISION sigma, PRECISION rho, PRECISION tau, size_t num_iter);

} // namespace i3d

#endif // DIFFUSION_FILTERS_H

