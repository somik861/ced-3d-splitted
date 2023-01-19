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
 * FILE: contours.h
 *
 * Structures and functions for finding contours (isolines) in 2D image
 *
 * Honza Hubený (xhubeny@fi.muni.cz) 2004
 *
 */

#ifndef _CONTOURS_TOOLS_
#define _CONTOURS_TOOLS_

#include "image3d.h"
#include "draw.h"
#include "points.h"

namespace i3d 
{

/** Draws isolines of "Value" computed from "Image3d ImgIn" on the 2d
    slices of the "Image3d ImgOut" with colour "colour". The slice plane
    direction (xy, xz, yz) depends on the variable Axis, where the name
    of the axis is orthogonal to the slice plane. So AXIS_Z means that
    the isolines will be drawn in the xy slices. */
template <class VOXELIN, class VOXELOUT>
  I3D_ALGO_EXPORT void MarchingSquares (
		  i3d::Image3d<VOXELIN>& ImgIn, 
		  i3d::Image3d<VOXELOUT>& ImgOut,
        VOXELIN Value,Direction Axis  = AXIS_Z,
        VOXELOUT Colour  = std::numeric_limits<VOXELOUT>::max());

/** This functions finds isolines ofthe "VOXEL Value" in the "Image3d
    ImgIn" on the "size_t SliceNumber"-th slice orthogonal to the
    "Directin Axis". The isolines are saved in the referenced vector of
    Point3d<float>. There is no error detection (if the number of the slice is
    not out of the range, or if the vector of Point3d is initialized.)
    There should be some space reserved in the "std::vector<Point3d>&
    Lines" before calling this function. For example
    Lines.reserve(500) */
template <class VOXEL>
  I3D_ALGO_EXPORT void MarchingSquaresOneSlice(
		  i3d::Image3d<VOXEL>& ImgIn, VOXEL Value,
        Direction Axis, std::vector<Point3d<float> >& Lines,
        size_t SliceNumber);
}

#endif
