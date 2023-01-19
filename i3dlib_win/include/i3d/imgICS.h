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
 * FILE: imgICS.h
 *
 * Structures and functions for reading/writing ICS image files.
 *
 * David Svoboda <svoboda@fi.muni.cz> 2005
 * Petr Matula <pem@fi.muni.cz> 2005
 *
 */

#ifndef _ICS_TOOLS_
#define _ICS_TOOLS_

extern "C" {
typedef struct _ICS ICS;
}

#include "imgfiles.h"
#include "basic.h"


namespace i3d {

///////////////////////////////////////////////////////////////////////////
/** \ingroup io
 * 
 * Class for reading the ICS files 
 */
///////////////////////////////////////////////////////////////////////////
  class I3D_CORE_EXPORT ICSReader:public ImageReader 
  {
  protected:
    template <class T> void LoadData(T *data);
    template <class C> void LoadRGBData(RGB_generic<C> *data);
	 ICS *ip;
	 size_t *ics_crop_offset, *ics_crop_size;
	 int ndims;

  public:	
    ICSReader(const char *fname, const VOI<PIXELS> *voi = NULL);

	 virtual size_t GetFileNames(FileList &fl);

    virtual void LoadImageInfo();
		
    virtual void LoadImageData(GRAY8 *data) {LoadData(data);};
    virtual void LoadImageData(bool *data) {LoadData(data);}
    virtual void LoadImageData(RGB *data) {LoadRGBData(data);};
    virtual void LoadImageData(GRAY16 *data) {LoadData(data);};
    virtual void LoadImageData(RGB16 *data) {LoadRGBData(data);};
    virtual void LoadImageData(float *data) {LoadData(data);};
    virtual void LoadImageData(double *data) {LoadData(data);};
    virtual void LoadImageData(std::complex<float> *data) {LoadData(data);};
    virtual void LoadImageData(std::complex<double> *data) {LoadData(data);};
					
    ~ICSReader();
  };

///////////////////////////////////////////////////////////////////////////
/** \ingroup io
 *
 * Class for writing the ICS files 
 */
///////////////////////////////////////////////////////////////////////////
  class I3D_CORE_EXPORT ICSWriter:public ImageWriter
  {
  protected:
    template <class T> void SaveData(const T *data);
    template <class C> void SaveRGBData(const RGB_generic<C> *data);
	 ICS *ip;
	 int ndims;
		
  public:	
    ICSWriter(const char *fname, unsigned int version);

    virtual void SaveImageInfo();
		
    virtual void SaveImageData(const GRAY8 *data) {SaveData(data);};
    virtual void SaveImageData(const bool *data) {SaveData(data);}; 
    virtual void SaveImageData(const RGB *data) {SaveRGBData(data);};
    virtual void SaveImageData(const GRAY16 *data) {SaveData(data);};
    virtual void SaveImageData(const RGB16 *data) {SaveRGBData(data);};
    virtual void SaveImageData(const float *data) {SaveData(data);};
    virtual void SaveImageData(const double *data) {SaveData(data);};
    virtual void SaveImageData(const std::complex<float> *data) { SaveData(data);};
    virtual void SaveImageData(const std::complex<double> *data) { SaveData(data);};
	
    ~ICSWriter();
  };

}

#endif
