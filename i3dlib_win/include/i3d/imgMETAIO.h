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
 * FILE: imgMETAIO.h
 *
 * Structures and functions for reading/writing METAIO image files.
 *
 * Honza Hubený (xhubeny@fi.muni.cz) 2004
 * David Svoboda <svoboda@fi.muni.cz> 2005
 *
 */

#ifndef _METAIO_TOOLS_
#define _METAIO_TOOLS_

#include "imgfiles.h"
#include <string>
#include <iostream>
#include <fstream>

namespace i3d {

////////////////////////////////////////////////////////////////////////////
/** struct with parameters of the image read from the header of the text *.mhd or *.mha file*/
typedef struct {
	/** Size of the image header. If set to -1, the length is counted
	 * during the reading process and the data block is stored just after
	 * the header footnote */
    int HeaderSize; 

	 /// number of dimensions in the image 
    int NDims;

	 /// byte ordering scheme
    bool ElementByteOrderMSB;

	 /** Distance between to voxels. It is reciprocal value to resolution */
    float ElementSpacing[3];

	 /** Phsysical size of each voxel */
    float ElementSize[3];

	 /** Postion of the image in the real world */
	 float Position[3];

	 /** minimum value in the data */
    float ElementMin;

	 /** maximum value in the data */
    float ElementMax;

	 /** number of channels per voxel */
    int ElementNumberOfChannels;

	 /** localization of raw image data */
    std::string ElementDataFile;

    int FileNameMin;
    int FileNameMax;
    int FileNameStep;
} METAIOHeader;

////////////////////////////////////////////////////////////////////////////
/** \ingroup io
 *
 * Class for reading MetaIO files */
////////////////////////////////////////////////////////////////////////////
class I3D_CORE_EXPORT METAIOReader:public ImageReader
	{
	protected:
		METAIOHeader meta_tags;
		std::ifstream f;

		template <class T> size_t ReadRawData(std::ifstream &ff, T *data);
		template <class T> void LoadData(T *data);

	public:
    METAIOReader(const char *fname);

    virtual void LoadImageInfo();

	 virtual size_t GetFileNames(FileList &fl);
		
    virtual void LoadImageData(GRAY8 *data) {LoadData(data);};
    virtual void LoadImageData(bool *data) {LoadData(data);};
    virtual void LoadImageData(RGB *data) {LoadData(data);};
    virtual void LoadImageData(GRAY16 *data) {LoadData(data);};
    virtual void LoadImageData(RGB16 *data) {LoadData(data);};
    virtual void LoadImageData(float *data) {LoadData(data);};
    virtual void LoadImageData(Vector3d<float> *data) {LoadData(data);};
    virtual void LoadImageData(Vector3d<double> *data) {LoadData(data);};
    virtual void LoadImageData(std::complex<float> *data) 
	 {
		  throw IOException("i3dlib: METAIO format does not support "
								  "handling complex data");
	 };
    virtual void LoadImageData(std::complex<double> *data) 
	 {
		  throw IOException("i3dlib: METAIO format does not support "
								  "handling complex data");
	 };
					
    ~METAIOReader();
		
	};

////////////////////////////////////////////////////////////////////////////
/** \ingroup io
 *
 * Class for writing the MetaIO files */
////////////////////////////////////////////////////////////////////////////
class I3D_CORE_EXPORT METAIOWriter:public ImageWriter
  {
  protected:
		METAIOHeader meta_tags;
	   std::ofstream f;

		template <class T> size_t WriteRawData(std::ofstream &ff, const T *data);
		template <class T> void SaveData(T *data);
		
  public:	
    METAIOWriter(const char *fname);

    virtual void SaveImageInfo();
		
    virtual void SaveImageData(const GRAY8 *data) {SaveData(data);};
    virtual void SaveImageData(const bool *data) {SaveData(data);};
    virtual void SaveImageData(const RGB *data) {SaveData(data);};
    virtual void SaveImageData(const GRAY16 *data) {SaveData(data);};
    virtual void SaveImageData(const RGB16 *data) {SaveData(data);};
    virtual void SaveImageData(const float *data) {SaveData(data);};
    virtual void SaveImageData(const Vector3d<float> *data) {SaveData(data);};
	 virtual void SaveImageData(const Vector3d<double> *data) {SaveData(data);};
    virtual void SaveImageData(const std::complex<float> *data) 
	 {
		  throw IOException("i3dlib: METAIO format does not support "
								  "handling complex data");
	 };
    virtual void SaveImageData(const std::complex<double> *data) 
	 {
		  throw IOException("i3dlib: METAIO format does not support "
								  "handling complex data");
	 };
	
    ~METAIOWriter();
  };

////////////////////////////////////////////////////////////////////////////

}
#endif
