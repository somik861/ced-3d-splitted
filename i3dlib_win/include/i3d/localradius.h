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
 * FILE : localradius.h
 *
 * Pavel Matula <pam@fi.muni.cz> 2009
 *
 */

#ifndef __LOCALRADIUS_H__
#define __LOCALRADIUS_H__

#ifdef __GNUG__
#pragma interface "localradius.h"
#endif

#include "basic.h"
#include "image3d.h"

#include "regions.h"
#include "LevelSet.h"

namespace i3d{
/** \defgroup lr Local radius measures */


/** \ingroup lr
  \brief This function computes Local Radius for flat nuclei from centroid. 

  <b>Definition of Local Radius:</b><br>
  This function computes local radius on every 2D slice and weight the results by the distance from the centroid.
  Useful for flat nuclei (e.g. see Uhlirova et. al. 2010)

 \author Pavel Matula pam@fi.muni.cz
  \date 2009
  */

	template <class LABEL, class VOXELOUT> I3D_ALGO_EXPORT void LocalRadiusFlat(
		const i3d::LabeledImage3d<LABEL, bool> &ImgIn, 
		Image3d<VOXELOUT> & ImgOut, 
		const i3d::Vector3d<size_t> &centroid);

/** \ingroup lr
  \brief This function calls LocalRadiusFlat for centroids for every seed and combines the results by voxel-wise 
	minima operator. 

  \author Pavel Matula pam@fi.muni.cz
  \date 2009
  */
	template <class LABEL, class VOXELOUT> I3D_ALGO_EXPORT void LocalRadiusFlat(
		const i3d::LabeledImage3d<LABEL, bool> &ImgIn, 
		Image3d<VOXELOUT> & ImgOut, 
		const i3d::SeedPointsVector &seeds);


};

#endif

