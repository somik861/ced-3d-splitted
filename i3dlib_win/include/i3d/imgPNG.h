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
 * FILE: imgPNG.h
 *
 * Structures and functions for reading/writing PNG image files.
 *
 * Maros Gonda (mano@mail.muni.cz) 2011
 *
 */

#ifndef _PNG_TOOLS_
#define _PNG_TOOLS_



extern "C" {
#include <stdio.h>
#include <png.h>
}

#include "imgfiles.h"



namespace i3d {

/** \ingroup io
 *
 * Class for reading PNG files */
class I3D_CORE_EXPORT PNGReader:public ImageReader
	{
	protected:
		/// file descriptor
		FILE *fd;

		/// main png image structure
		png_structp png_image_struct;
		/// png image information structure
		png_infop png_image_info_struct;
		
		/// loads image data from file
		template <class T> void LoadData(T *data);

	public:	
		PNGReader(const char *fname, const VOI<PIXELS> *voi);
	
		virtual void LoadImageInfo();
		virtual void LoadDescription();
		
		virtual void LoadImageData(GRAY8 *data) {LoadData(data);};
		virtual void LoadImageData(bool *data) {LoadData(data);};
		virtual void LoadImageData(RGB *data) {LoadData(data);};
		virtual void LoadImageData(GRAY16 *data) {LoadData(data);};
		virtual void LoadImageData(RGB16 *data) {LoadData(data);};
		virtual void LoadImageData(std::complex<float> *data) {
		  throw IOException("i3dlib: PNG format does not support "
							"handling complex data");
		};
		virtual void LoadImageData(std::complex<double> *data) {
			throw IOException("i3dlib: PNG format does not support "
							"handling complex data");
		};
		
		~PNGReader();
	};

/** \ingroup io
 *
 * Class for writing PNG files */
class I3D_CORE_EXPORT PNGWriter:public ImageWriter
	{
	protected:
		/// file descriptor
		FILE *fd;
		
		/// main png image structure
		png_structp png_image_struct;
		/// png image information structure
		png_infop png_image_info_struct;
		
		/// saves data into image
		template <class T> void SaveData(const T *data);
		
	public:	
		PNGWriter(const char *fname);
		
		/// Saves image information
		virtual void SaveImageInfo();
		
		/// saves image description
		virtual void SaveDescription();
		
		virtual void SaveImageData(const GRAY8 *data) {SaveData(data);};
		virtual void SaveImageData(const bool *data) {SaveData(data);};
		virtual void SaveImageData(const RGB *data) {SaveData(data);};
		virtual void SaveImageData(const GRAY16 *data) {SaveData(data);};
		virtual void SaveImageData(const RGB16 *data) {SaveData(data);};
		virtual void SaveImageData(const Vector3d<float> data) {
			throw IOException("i3dlib: PNG format does not support "
							"real data");
		};
		virtual void SaveImageData(const Vector3d<double> data) {
			throw IOException("i3dlib: PNG format does not support "
							"real data");
		};
		virtual void SaveImageData(const std::complex<float> *data) {
			throw IOException("i3dlib: PNG format does not support "
							"handling complex data");
		};
		virtual void SaveImageData(const std::complex<double> *data) {
			throw IOException("i3dlib: PNG format does not support "
							"handling complex data");
		};
		
		~PNGWriter();
	};

}

#endif
