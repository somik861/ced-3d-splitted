/*
 * i3dlib - image manipulation library
 *
 * Copyright (C) 2000-2018   Centre for Biomedical Image Analysis (CBIA)
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
 * Binary 3D Skeletonization
 *
 * \author David Svoboda <svoboda@fi.muni.cz> 
 * \date 2018
 */

#ifndef __SKELETON_H__
#define __SKELETON_H__

//--------------------------------------------------------------------------
/** 
 * \ingroup if
 * \brief Skeletonization of binary 2d/3d images.
 *
 * An implementation of the algorithm from Lee et al. "Building skeleton models via 3-D 
 * medial surface/axis thinning algorithms. Computer Vision, Graphics, and 
 * Image Processing, 56(6):462–478, 1994." Adopted from the ITK version from
 * Hanno Homann:  http://hdl.handle.net/1926/1292 and FIJI plugin from 
 * Ignacio Arganda-Carreras: https://imagej.net/Skeletonize3D
 *
 * Imported and modified by: David Svoboda <svoboda@fi.muni.cz> August 2018
 *
 * \param[in] img 			input image
 * \param[out] skeleton 		output image, needn't be allocated
 *
 * \date August 2018
 */


namespace i3d {

I3D_ALGO_EXPORT
void Skeletonize(const i3d::Image3d<bool> &img, i3d::Image3d<bool> &skeleton);

} // namespace i3d

#endif // __SKELETON_H__



