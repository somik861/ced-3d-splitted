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
 * FILE: i3dio.h
 *
 * input/output manipulation routines for variaous image formats
 * 
 * David Svoboda <svoboda@fi.muni.cz> 2005
 * Maros Gonda (mano@mail.muni.cz) 2011
 *
 */

#ifndef _I3DIO_
#define _I3DIO_

#ifdef __GNUG__
#pragma interface
#endif

#include "i3d_config.h"

#ifdef WITH_TIFF
	#include "imgTIFF.h"
#endif

#ifdef WITH_TARGA
	#include "imgTGA.h"
#endif 

#ifdef WITH_PNG
	#include "imgPNG.h"
#endif

#ifdef WITH_JPEG
	#include "imgJPEG.h"
#endif

#ifdef WITH_METAIO
	#include "imgMETAIO.h"
#endif

#ifdef WITH_ICS
	#include "imgICS.h"
#endif

#ifdef WITH_HDF5
	#include "imgHDF5.h"
#endif

#ifdef WITH_DCM
	#include "imgDCM.h"
#endif

// internal format for i3dlib - included anyway
#include "imgI3D.h"

namespace i3d {

/////////////////////////////////////////////////////////////////////////
/** \ingroup io
 * general ImageReader creator */
I3D_CORE_EXPORT ImageReader* CreateReader(const char *, 
		const VOI<PIXELS> *voi = NULL, 
		bool is_regex = false);

/** \ingroup io
 * general ImageReader destructor */
I3D_CORE_EXPORT void DestroyReader(ImageReader *);
	
/////////////////////////////////////////////////////////////////////////
/** \ingroup io
 * general ImageWriter creator */
I3D_CORE_EXPORT ImageWriter* CreateWriter(const char *, FileFormat ft, Vector3d<size_t> sz, const VOI<PIXELS> *voi = NULL);

/** \ingroup io
 * general ImageWriter destructor */
I3D_CORE_EXPORT void DestroyWriter(ImageWriter *);

/////////////////////////////////////////////////////////////////////////
}

#endif
