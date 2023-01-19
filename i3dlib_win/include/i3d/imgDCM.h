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
 * FILE: imgDCM.h
 *
 * Structures and functions for reading/writing DICOM image files.
 *
 * David Svoboda <svoboda@fi.muni.cz> 2008
 * Jakub Grochol <139693@mail.muni.cz> 2008,2009
 *
 */

#ifndef _DICOM_TOOLS_
#define _DICOM_TOOLS_

typedef class DcmFileFormat DcmFF;

#include "imgfiles.h"
#include "basic.h"

namespace i3d {

  /** \ingroup io
   *
   * Class for reading the DCM files */    
  class I3D_CORE_EXPORT DCMReader:public ImageReader 
  {
  protected:
	//-------------------------------------------------------------------------
    // Member variable
    //-------------------------------------------------------------------------
	DcmFF *dcmHeader;

    //-------------------------------------------------------------------------
    // Member functions
    //-------------------------------------------------------------------------
    /// Loads image data of voxel types GRAY8, GRAY16 and RGB.		  
    template <class T> void LoadData(T *data);

  public:	
    //-------------------------------------------------------------------------
    // Constructor
    //-------------------------------------------------------------------------
    /** Constructor.

      \param fname image filename
    */
    DCMReader(const char *fname);

    //-------------------------------------------------------------------------
    // LoadImageInfo
    //-------------------------------------------------------------------------
    /// Load image header information
    virtual void LoadImageInfo();	
    
    //-------------------------------------------------------------------------
    // Image data loaders
    //-------------------------------------------------------------------------
    virtual void LoadImageData(GRAY8 *data) {LoadData(data);};
    virtual void LoadImageData(RGB *data) {LoadData(data);};
    virtual void LoadImageData(GRAY16 *data) {LoadData(data);};
    virtual void LoadImageData(RGB16 *data) {LoadData(data);};
    virtual void LoadImageData(bool *data) 
	 {
		  throw IOException("i3dlib: DICOM format does not support "
								  "handling binary data");
	 };
    virtual void LoadImageData(float *data) 
	 {
		  throw IOException("i3dlib: DICOM format does not support "
								  "handling float data");
	 };
    virtual void LoadImageData(std::complex<float> *data) 
	 {
		  throw IOException("i3dlib: DICOM format does not support "
								  "handling complex data");
	 };
    virtual void LoadImageData(std::complex<double> *data) 
	 {
		  throw IOException("i3dlib: DICOM format does not support "
								  "handling complex data");
	 };
					
    /** Destructor. Destructor of DCM reader class. */
    ~DCMReader();
  };


  /** \ingroup io
	*
	* Class for writing the DCM files */
  class I3D_CORE_EXPORT DCMWriter:public ImageWriter
  {
  protected:
    //-------------------------------------------------------------------------
    // Member variable
    //-------------------------------------------------------------------------
	DcmFF *dcmHeader;

    //-------------------------------------------------------------------------
    // Member functions
    //-------------------------------------------------------------------------
    /// Saves image data
    template <class T> void SaveData(const T *data);
		
  public:	
    //-------------------------------------------------------------------------
    // Constructor
    //-------------------------------------------------------------------------
    /** Constructor.

      \param fname image filename
    */
    DCMWriter(const char *fname);

    //-------------------------------------------------------------------------
    // SaveImageInfo
    //-------------------------------------------------------------------------
    /// Save necessary header information
    virtual void SaveImageInfo();
	
    //-------------------------------------------------------------------------
    // Functions for saving image data
    //-------------------------------------------------------------------------	
    virtual void SaveImageData(const GRAY8 *data) {SaveData(data);};
    virtual void SaveImageData(const RGB *data) {SaveData(data);};
    virtual void SaveImageData(const GRAY16 *data) {SaveData(data);};
    virtual void SaveImageData(const RGB16 *data) {SaveData(data);};
    virtual void SaveImageData(const bool *data)
	 {
		  throw IOException("i3dlib: DICOM format does not support "
								  "handling binary data");
	 };
    virtual void SaveImageData(const float *data) 
	 {
		  throw IOException("i3dlib: DICOM format does not support "
								  "handling complex data");
	 };
    virtual void SaveImageData(const std::complex<float> *data) 
	 {
		  throw IOException("i3dlib: DICOM format does not support "
								  "handling complex data");
	 };
    virtual void SaveImageData(const std::complex<double> *data) 
	 {
		  throw IOException("i3dlib: DICOM format does not support "
								  "handling complex data");
	 };

    /** Destructor. Destructor of DCM writer class. */	
    ~DCMWriter();
  };
}

#endif