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
 \file bin.h
 Functions for binary image transformation
 
 \author David Svoboda (xsvobod2@fi.muni.cz) 2002 
 
  \defgroup bin Operations over binary images
  
 */

#ifndef _BIN_TOOLS_
#define _BIN_TOOLS_

#ifdef __GNUG__
#pragma interface
#endif

#include "image3d.h"
#include "neighbours.h"

namespace i3d {
 
/** 
 * \ingroup bin
 * 
 * Fill holes in a binary image. A hole is a background connected component not touching the image border.
 */
I3D_ALGO_EXPORT void BinFillHoles(Image3d<bool>& img, const Neighbourhood &nb = nb3D_6);

/** 
 * \ingroup bin
 * 
 * BinUnambiguous make the image so that this can be represented 
 * by the Freeman code
 */
I3D_ALGO_EXPORT void BinUnambiguous(Image3d<bool>& img);

/** 
 * \ingroup bin
 *
 * BinPartialConvex creates convex hull for each 2D crosssection separately.
 */
I3D_ALGO_EXPORT void BinPartialConvex(Image3d<bool>& img, size_t Range);

}

#endif
