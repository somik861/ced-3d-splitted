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
 * FILE: imgTIFF.h
 *
 * Structures and functions for reading/writing TIFF image files.
 *
 * David Svoboda <svoboda@fi.muni.cz> 2002 
 *
 */
#ifndef _TIFF_TOOLS_
#define _TIFF_TOOLS_

#include "imgfiles.h"
#include "basic.h"

/* New TIFF tags numbers */
#define I3DTAG_ZPOSITION 65000
#define I3DTAG_ZRESOLUTION 65001

typedef struct tiff TIFF;

namespace i3d {

  /** \ingroup io
   *
   * Class for reading the TIFF files */    
  class I3D_CORE_EXPORT TIFFReader:public ImageReader 
  {
  protected:
    //-------------------------------------------------------------------------
    // Member variables
    //-------------------------------------------------------------------------
    /// TIFF file representation
    TIFF *tif;
    /// Volume of interest
    VOI<PIXELS> tifVOI;
    
    //-------------------------------------------------------------------------
    // Member functions
    //-------------------------------------------------------------------------
    /// Loads image data of voxel types GRAY8, GRAY16 and RGB.			  
    template <class T> void LoadData(T *data);
    /// Loads image data of voxel type RGB16 or from palette color images.
    template <class T> void LoadRGB16Data(T *data);
    /// Loads image data of voxel type BINARY.
    void LoadBinData(bool *data);

  public:	
    //-------------------------------------------------------------------------
    // Constructor
    //-------------------------------------------------------------------------
    /** Constructor. It is used for reading TIFF files. Initialize Libtif for 
      using new tags. Open specified file for reading and setup member VOI. 
      If we dont specify any VOI then it will be later set to full volume of 
      image.

      \param fname image filename
      \param voi volume of interest to read from the file
    */
    TIFFReader(const char *fname, const VOI<PIXELS> *voi);

    //-------------------------------------------------------------------------
    // LoadImageInfo
    //-------------------------------------------------------------------------
    /* Check if the header parameters are consistent in whole image. If no VOI
       is set then it will be whole image volume by default. Choose voxel type
       of the image.
    */
    virtual void LoadImageInfo();	
    
    //-------------------------------------------------------------------------
    // Image data loaders
    //-------------------------------------------------------------------------
    virtual void LoadImageData(GRAY8 *data) {LoadData(data);};
    virtual void LoadImageData(bool *data) {LoadBinData(data);};
    virtual void LoadImageData(RGB *data) {LoadData(data);};
    virtual void LoadImageData(GRAY16 *data) {LoadData(data);};
    virtual void LoadImageData(float *data) {LoadData(data);};
    virtual void LoadImageData(RGB16 *data) {LoadRGB16Data(data);};
    virtual void LoadImageData(std::complex<float> *data) 
	 {
		  throw IOException("i3dlib: TIFF format does not support "
								  "handling complex data");
	 };
    virtual void LoadImageData(std::complex<double> *data) 
	 {
		  throw IOException("i3dlib: TIFF format does not support "
								  "handling complex data");
	 };
					
    /** Destructor. Destructor of TIFF reader class. */
    ~TIFFReader();
  };


  /** \ingroup io
	*
	* Class for writing the TIFF files */
  class I3D_CORE_EXPORT TIFFWriter:public ImageWriter
  {
  protected:
    //-------------------------------------------------------------------------
    // Member variable
    //-------------------------------------------------------------------------
    /// TIFF file representation
    TIFF *tif;

	// local variable for handling mulitpage images
	size_t active_directory;
		
    //-------------------------------------------------------------------------
    // Member functions
    //-------------------------------------------------------------------------
    /// Saves image data of voxel types GRAY8, GRAY16, RGB and RGB16
    template <class T> void SaveData(const T *data);
    /// Saves image data of voxel type BINARY
    void SaveBinData(const bool *data);
		
  public:	
    //-------------------------------------------------------------------------
    // Constructor
    //-------------------------------------------------------------------------
    /** Constructor. It is used for writing TIFF files. Initialize Libtif for
      using new tags and open specified file for writing.

      \param fname image filename
    */
    TIFFWriter(const char *fname);

    //-------------------------------------------------------------------------
    // SaveImageInfo
    //-------------------------------------------------------------------------
    /// Saves image header
    virtual void SaveImageInfo();
	
    //-------------------------------------------------------------------------
    // Functions for saving image data
    //-------------------------------------------------------------------------	
    virtual void SaveImageData(const GRAY8 *data) {SaveData(data);};
    virtual void SaveImageData(const bool *data) {SaveBinData(data);};
    virtual void SaveImageData(const RGB *data) {SaveData(data);};
    virtual void SaveImageData(const GRAY16 *data) {SaveData(data);};
    virtual void SaveImageData(const RGB16 *data) {SaveData(data);};
    virtual void SaveImageData(const float *data) {SaveData(data);};
    virtual void SaveImageData(const std::complex<float> *data) 
	 {
		  throw IOException("i3dlib: TIFF format does not support "
								  "handling complex data");
	 };
    virtual void SaveImageData(const std::complex<double> *data) 
	 {
		  throw IOException("i3dlib: TIFF format does not support "
								  "handling complex data");
	 };

    /** Destructor. Destructor of TIFF writer class. */	
    ~TIFFWriter();
  };
}

#endif
