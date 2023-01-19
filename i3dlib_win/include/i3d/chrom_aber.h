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

/**
* @file chrom_aber.h
* @brief %Chromatic aberration correction
*
* @author Marek Kašík (xkasik1@fi.muni.cz)
* @author Martin Maška (xmaska@fi.muni.cz)
* @date 2008
*/

#ifndef __CHROM_ABER_H__
#define __CHROM_ABER_H__

#include "algo_export.h"
#include "image3d.h"

namespace i3d 
{

	/////////////////////////////////////////////////////////////////
	//                                                             //
	//                   Struct ChromAberParams                    //
	//                                                             //
	/////////////////////////////////////////////////////////////////

	/** Surface parameters for a chromatic aberration correction. */
	struct I3D_ALGO_EXPORT ChromAberParams
	{
		double x_plane[3];
		double y_plane[3];
		double z_surf[6];

		/** Constructor. */
		ChromAberParams();
		/** Destructor. */
		~ChromAberParams();
		/** Set parameters in such a way that represent an identical transformation. */
		void SetIdentity();
		/** Do the parameters represent an identical transformation in 2D? */
		bool IsIdentity2D() const;
		/** Do the parameters represent an identical transformation in 3D? */
		bool IsIdentity3D() const;
	};

	/////////////////////////////////////////////////////////////////
	//                                                             //
	//              Function CorrectChromaticAberration            //
	//                                                             //
	/////////////////////////////////////////////////////////////////

	/** A template function for correcting chromatic aberrations of scalar images. This function can be efficiently
	  * used for both 2D and 3D images. The output image can be automatically cut to remove undesired black border of
	  * corrected image. Therefore, its size does not have to correspond to the input image one. */
	template <class T> I3D_ALGO_EXPORT void CorrectChromaticAberration(
		const i3d::Image3d<T> &input,			// input image
		i3d::Image3d<T> &output,				// corrected image
		const i3d::ChromAberParams &params,     // correction parameters
		bool cut								// shall we want to cut corrected image automatically?
	);

	/** A template function for correcting chromatic aberrations of multi-channel images. This function can be efficiently
	  * used for both 2D and 3D images. The output image can be automatically cut to remove undesired black border of
	  * corrected image. Therefore, its size does not have to correspond to the input image one. */
	template <class T> I3D_ALGO_EXPORT void CorrectChromaticAberration(
		const i3d::Image3d<i3d::RGB_generic<T> > &input,	// input image
		i3d::Image3d<i3d::RGB_generic<T> > &output,			// corrected image
		const i3d::ChromAberParams &red_params,				// correction parameters for the red channel
		const i3d::ChromAberParams &green_params,			// correction parameters for the green channel
		const i3d::ChromAberParams &blue_params,            // correction parameters for the blue channel
		bool cut											// shall we want to cut corrected image automatically?
	);

	/////////////////////////////////////////////////////////////////
	//                                                             //
	//                 Function GetCuttingPosition                 //
	//                                                             //
	/////////////////////////////////////////////////////////////////

	/** A function for computing a minimal and maximal cutting position of scalar images. This function can be 
	  * efficiently used for both 2D and 3D images. It detects undesirable black border in the input image 
	  * steming from its chromatic aberration correction. The zero-based indices for all axes are returned. 
	  * Since the input image data is not taken into account during the compuation, the input image is defined
	  * just using its offset, resolution and size. */
	I3D_ALGO_EXPORT void GetCuttingPosition(
		const i3d::Offset &img_offset,				// input image offset
		const i3d::Resolution &img_resolution,      // input image resolution
		const i3d::Vector3d<size_t> &img_size,      // input image size
		const i3d::ChromAberParams &params,         // correction parameters
		i3d::Vector3d<size_t> &minimum,		     	// minimal cutting position (in pixels, zero-based index)
		i3d::Vector3d<size_t> &maximum			    // maximal cutting position (in pixels, zero-based index)
	);

	/** A template function for computing a minimal and maximal cutting position of multi-channel images. This function can be 
	  * efficiently used for both 2D and 3D images. It detects undesirable black border in the input image steming from its 
	  * chromatic aberration correction. The zero-based indices for all axes are returned. * Since the input image data is not
	  * taken into account during the compuation, the input image is defined just using its offset, resolution and size. */
	I3D_ALGO_EXPORT void GetCuttingPosition(
		const i3d::Offset &img_offset,				  // input image offset
		const i3d::Resolution &img_resolution,        // input image resolution
		const i3d::Vector3d<size_t> &img_size,        // input image size
		const i3d::ChromAberParams &red_params,       // correction parameters for red channel
		const i3d::ChromAberParams &green_params,     // correction parameters for green channel
		const i3d::ChromAberParams &blue_params,      // correction parameters for blue channel
		i3d::Vector3d<size_t> &minimum,			      // minimal cutting position (in pixels, zero-based index)
		i3d::Vector3d<size_t> &maximum			      // maximal cutting position (in pixels, zero-based index)
	);

} // namespace i3d

#endif // __CHROM_ABER_H__
