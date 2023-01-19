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
 * FILE: imgI3D.h
 *
 * Structures and functions for reading/writing I3D image files.
 *
 * David Svoboda <svoboda@fi.muni.cz> 2005
 *
 */

#ifndef _I3D_TOOLS_
#define _I3D_TOOLS_

#ifdef __GNUG__
#pragma interface
#endif

#include "imgfiles.h"

#define IMPLICIT_FORMAT IMG_TIFF

namespace i3d {

////////////////////////////////////////////////////////////////////////////
/** \ingroup io
 *
 * Image 3d (internal format of i3dlib) Reader */
  class I3D_CORE_EXPORT I3DReader:public SequenceReader
  {
  public:	
	 /// the constructor
	 I3DReader(const char *fname, const VOI<PIXELS> *voi = NULL);

	 /// read the basic image information (header)
    virtual void LoadImageInfo();

	 virtual size_t GetFileNames(FileList &fl);
  };

////////////////////////////////////////////////////////////////////////////
/** \ingroup io
 *
 * Image 3d (internal format of i3dlib) Writer */
  class I3D_CORE_EXPORT I3DWriter:public SequenceWriter
  {
  public:	
	 /// constructor
	 I3DWriter(const char *fname):SequenceWriter(fname, IMPLICIT_FORMAT) {};

	 /// write the basic image information (header)
    virtual void SaveImageInfo();
  };

////////////////////////////////////////////////////////////////////////////
// I3D_CORE_EXPORT bool ReadConfig(const char* fname, std::map<string,string> &items, const char sep='=');
}

#endif
