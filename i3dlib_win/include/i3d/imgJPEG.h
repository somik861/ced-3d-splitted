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
 * FILE: imgJPEG.h
 *
 * Structures and functions for reading/writing JPEG image files.
 *
 * David Svoboda (svoboda@fi.muni.cz) 2002 
 *
 */

#ifndef _JPEG_TOOLS_
#define _JPEG_TOOLS_

#include <stdio.h>
#include "imgfiles.h"

extern "C" {
struct jpeg_decompress_struct;
struct jpeg_compress_struct;
struct jpeg_error_mgr;
}

namespace i3d {

/** \ingroup io
 *
 * Class for reading JPEG files */
class I3D_CORE_EXPORT JPEGReader:public ImageReader
	{
	protected:
		FILE *fd;
		jpeg_decompress_struct *decomp_info;
		jpeg_error_mgr *jerr;
		  
		template <class T> void LoadData(T *data);

	public:	
		JPEGReader(const char *fname);
	
		virtual void LoadImageInfo();
		
		virtual void LoadImageData(GRAY8 *data) {LoadData(data);};
	   virtual void LoadImageData(bool *data) {LoadData(data);};
	   virtual void LoadImageData(RGB *data) {LoadData(data);};
		virtual void LoadImageData(GRAY16 *data) {LoadData(data);};
	   virtual void LoadImageData(RGB16 *data) {LoadData(data);};
      virtual void LoadImageData(std::complex<float> *data) 
  	   {
		  throw IOException("i3dlib: JPEG format does not support "
								  "handling complex data");
	   };
      virtual void LoadImageData(std::complex<double> *data) 
	   {
		  throw IOException("i3dlib: JPEG format does not support "
								  "handling complex data");
	   };
					
		~JPEGReader();
	};

/** \ingroup io
 *
 * Class for writing JPEG files */
class I3D_CORE_EXPORT JPEGWriter:public ImageWriter
	{
	protected:
		FILE *fd;
		jpeg_compress_struct *comp_info;
		jpeg_error_mgr *jerr;
		  
		template <class T> void SaveData(const T *data);

	public:	
		JPEGWriter(const char *fname);

		virtual void SaveImageInfo();
		
      virtual void SaveImageData(const GRAY8 *data) {SaveData(data);};
      virtual void SaveImageData(const bool *data) {SaveData(data);};
      virtual void SaveImageData(const RGB *data) {SaveData(data);};
      virtual void SaveImageData(const GRAY16 *data) {SaveData(data);};
      virtual void SaveImageData(const RGB16 *data) {SaveData(data);};
      virtual void SaveImageData(const std::complex<float> *data) 
	   {
		  throw IOException("i3dlib: JPEG format does not support "
								  "handling complex data");
	   };
      virtual void SaveImageData(const std::complex<double> *data) 
	   {
		  throw IOException("i3dlib: JPEG format does not support "
								  "handling complex data");
	   };

		~JPEGWriter();
	};

}

#endif
