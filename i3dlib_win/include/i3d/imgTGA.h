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
 * FILE: imgTGA.h
 *
 * Structures and functions for reading/writing TGA image files.
 *
 * David Svoboda <svoboda@fi.muni.cz> 2005
 * Petr Mejzlík (mejzlik@fi.muni.cz) 2002 
 *
 */

#ifndef _TARGA_TOOLS_
#define _TARGA_TOOLS_

#include "imgfiles.h"


namespace i3d {
		  
enum TGAType {  TGAColormap=    1,
                TGARGB=         2,
                TGAGray=        3,
                TGALEColormap=  9,
                TGALERGB=       10,
                TGALEGray=      11};

struct I3D_CORE_EXPORT TGAHeader {
                byte    id_length,
                colormap_type,
                image_type;
				unsigned short
                colormap_index,
                colormap_length,
                x_origin,
                y_origin;
				byte colormap_size,
        	    attributes;
};

/// Targa attribue
const int TGA_ATTRIB_ABITS = 0x0f;
/// Targa attribue - horizontal orientation
const int TGA_ATTRIB_HORIZONTAL = 0x10;
/// Targa attribue - vertical orientation
const int TGA_ATTRIB_VERTICAL = 0x20;

//I3D_CORE_EXPORT void SetBuf(FILE *fd, long cacheSize, char* IOcache);

/** \ingroup io
 *
 * Class for reading TGA files */
class I3D_CORE_EXPORT TGAReader:public ImageReader
	{
	protected:
		FILE	*fd;
		int	abpp;
		TGAHeader	info_tga;

		unsigned short _tsize; 
		/* Length (in bytes) of a space at the end of the image file
		 * used for storing the image histogram and its description
		 * (FISH extension) */
		
		template <class T> void LoadData(T *data);

		template <class T> void ReadPixels(T *data);
	public:
		TGAReader(const char *fname);

		virtual void LoadImageInfo();

      virtual void LoadImageData(GRAY8 *data) {LoadData(data);};
      virtual void LoadImageData(bool *data) {LoadData(data);};
      virtual void LoadImageData(RGB *data) {LoadData(data);};
      virtual void LoadImageData(GRAY16 *data) {LoadData(data);};
      virtual void LoadImageData(RGB16 *data) {LoadData(data);};
      virtual void LoadImageData(std::complex<float> *data) 
  	   {
		  throw IOException("i3dlib: TARGA format does not support "
								  "handling complex data");
	   };
      virtual void LoadImageData(std::complex<double> *data) 
	   {
		  throw IOException("i3dlib: TARGA format does not support "
								  "handling complex data");
	   };
	
		// Load a histogram and its description. 
		//virtual void LoadHistogram(HistDesc& hd);

		~TGAReader();
	};

/** \ingroup io
 *
 * Class for writing TGA files */
class I3D_CORE_EXPORT TGAWriter:public ImageWriter
	{
	protected:
		FILE	*fd;
		int	abpp;
		TGAHeader	info_tga;
		
		unsigned short _tsize; 
		/* Length (in bytes) of a space at the end of the image file
		 * used for storing the image histogram and its description
		 * (FISH extension) */
		
		template <class T> void SaveData(const T *data);

	public:
		// A constructor which saves needed info about the written image
		// and format in which it should be written.
		// w is width, h is height, tsize is the length of the FISH-specific
		// histogram part at the end of the image (if tsize=0, no histogram is
		// written, even if the image has one), it is the voxel type of the image
		// etc.
		TGAWriter(const char *fname);

		virtual void SaveImageInfo();

		virtual void SaveImageData(const GRAY8 *data) {SaveData(data);};
		virtual void SaveImageData(const bool *data) {SaveData(data);};
		virtual void SaveImageData(const RGB *data) {SaveData(data);};
		virtual void SaveImageData(const GRAY16 *data) {SaveData(data);};
		virtual void SaveImageData(const RGB16 *data) {SaveData(data);};
      virtual void SaveImageData(const std::complex<float> *data) 
	   {
		  throw IOException("i3dlib: TARGA format does not support "
								  "handling complex data");
	   };
      virtual void SaveImageData(const std::complex<double> *data) 
	   {
		  throw IOException("i3dlib: TARGA format does not support "
								  "handling complex data");
	   };

		// Save a histogram and its description. 
		// _tsize must be equal to hd.iosize(), otherwise
		// the InternalException is thrown.
		//virtual void SaveHistogram(const HistDesc& hd);
					  
		~TGAWriter();
	};

}

#endif
