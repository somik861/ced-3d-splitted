/*
 * i3dlib - image manipulation library
 *
 * Copyright (C) 2000-2012   Centre for Biomedical Image Analysis (CBIA)
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
 * FILE: imgHDF5.h
 *
 * Structures and functions for reading/writing HDF5image files.
 *
 * author: Maros Gonda (no contact e-mail) 2011 
 * modified by: David Svoboda <svoboda@fi.muni.cz> 2012
 *
 */

#ifndef _HDF5_TOOLS_
#define _HDF5_TOOLS_

#include <map>
#include "imgfiles.h"
#include "hdf5.h"

/// function to enable comparing of H5O_token_t
inline bool operator<(const H5O_token_t& lhs, const H5O_token_t& rhs)
{
	for (int i = 0; i < H5O_MAX_TOKEN_SIZE; ++i)
		if (lhs.__data[i] < rhs.__data[i])
			return true;

	return false;
}

namespace i3d {

/** \ingroup io
 *
 * Class for reading HDF5 files */
class I3D_CORE_EXPORT HDF5Reader:public ImageReader
	{
	protected:
		/// descriptor of main file structure and root group
		hid_t fd;
		
		/// descriptor of parent group of image dataset
		hid_t parentGroup;
				
		/// descriptor of image dataset
		hid_t dataSetID;

		/// descriptor of image dataset's dataspace
		hid_t dataSpaceID;

		/// descriptor of image data type
		hid_t dataType;
		
		/// image dataset's type class for correct recognition
		H5T_class_t dataImageType;
		
		/// desciptor of dataspace in file memory
		hid_t fileSpaceID;
		
		/// virtual memory dataspace's desciptor
		hid_t memorySpaceID;
		
		/// array of sizes of dimensions of image dataset
		hsize_t *dims;
		
		/// image dataset dimensions count
		int dimensions;
		
		/// array of positions of image coordinates in order X,Y,Z,C
		int dimsPosition[4];
		
		/// map consists of group address in file and its descriptor,
		/// used for storing information of groups to be scanned
		std::map<H5O_token_t, hid_t> searchGroups;
		
		/// map consists of group address in file and its descriptor,
		/// used for storing information of groups already scanned
		std::map<H5O_token_t, hid_t> checkedGroups;
				
		/** 
		 * Loads attribute data of specified type and optionally gives
		 * size of data stored by attribute (multiplication of dimensions' 
		 * sizes), respectivelly size of attribute datatype (e.g. string
		 * length) and returns given pointer to alocated data or NULL 
		 * in case of error.
		 */
		template <class A> A* GetAttribute(hid_t dataSet, const char* attributeName, H5T_class_t checkTypeClass, A* attributeData, hsize_t* attributeSize = NULL, hsize_t* storageSize=NULL);
		
		/// Checks whether given dataset is image or not
		bool IsImage(hid_t dataset);
		
		/// Loads single float value of selected dataset 
		float LoadObjectData(hid_t arg1);
		
		/// Checks if the data can be decoded (if the decompression algorithms are available)
		bool CheckCompressionAlgorithms();
		
		/// static function passed to iteration data objects calling correct handler
		static herr_t ObjCheck(hid_t loc_id, const char *name, const H5L_info_t *info, void *object);
		
		/// static function passed to iteration of dimension scales calling correct handler
		static herr_t DimensionScaleIterate(hid_t did, unsigned dimension, hid_t dsid, void *object);
		
		/// static function passed to iteration of additional text datasets and calling correct handler
		static herr_t ImageDescriptionIterate(hid_t loc_id, const char *name, const H5L_info_t *info, void *object);
		
		/// Loads RGB image data
		template <class R> void LoadRGBData(RGB_generic<R> *data);
		
		/// Loads image data from file
		template <class T> void LoadData(T *data);
		
	public:	
		/// Constructor
		HDF5Reader(const char *fname, const VOI<PIXELS> *voi=NULL);		
		
		/// Handles iteration of data objects during file scanning
		herr_t ObjectCheck(hid_t loc_id, const char* name);
		
		/// Handles iteration of datasets given as dimension scales
		herr_t DimensionScaleCheck(hid_t mainDataSet, int dimension, hid_t dataset);
		
		/// Handles iteration of datasets storing additional image text description
		herr_t ImageDescriptionCheck(hid_t loc_id, const char *name);
				
		/// Loads all additional image description
		virtual void LoadDescription();
		
		/// Loads main information about image
		virtual void LoadImageInfo();
		
		/// Loads image data
		virtual void LoadImageData(bool *data) {LoadData(data);};
		virtual void LoadImageData(GRAY8 *data) {LoadData(data);};
		virtual void LoadImageData(GRAY16 *data) {LoadData(data);};
		virtual void LoadImageData(int *data) {LoadData(data);};
		virtual void LoadImageData(RGB *data) {LoadRGBData(data);};
		virtual void LoadImageData(RGB16 *data) {LoadRGBData(data);};
		virtual void LoadImageData(float *data) {LoadData(data);};
		virtual void LoadImageData(double *data) {LoadData(data);};
		virtual void LoadImageData(Vector3d<float> *data) {LoadData(data);};
		virtual void LoadImageData(Vector3d<double> *data) {LoadData(data);};
		virtual void LoadImageData(std::complex<float> *data) {LoadData(data);};
		virtual void LoadImageData(std::complex<double> *data) {LoadData(data);};
		
		~HDF5Reader();    
	};

/** \ingroup io
 *
 * Class for writing HDF5 files */
class I3D_CORE_EXPORT HDF5Writer:public ImageWriter
	{
	protected:
		
		/// name of main image dataset
		const char* DATASET_NAME;
		
		/// flag specifying wheter to create a new file 
		///  or insert data in already existing file
		bool newFile;
		
		/// flag specifying whether to find image data minimal and maximal value
		bool checkMinMax;
		
		/// descriptor of main file structure and root group
		hid_t fd;
		
		/// descriptor of parent group of image dataset
		hid_t parentGroup;
		
		/// descriptor of image dataset
		hid_t dataSetID;
		
		/// descriptor of image dataset's dataspace
		hid_t dataSpaceID;
		
		/// descriptor of image data type
		hid_t dataImageType;
		
		/// image dataset dimensions count
		int dimensions;
		
		/// array of positions of image coordinates in order X,Y,Z
		unsigned char dimsPosition[3];
			
		/// creates compound data types with specified number, type and 
		/// names of fields used for storing complex numbers and vectors
		template<class A> hid_t CreateCompoundType(const char* name[], size_t size, hid_t H5Tid);
		
		/// Saves Additional data into its own dataset of specified type
		hid_t SaveAdditionalInfo(hid_t parentGroup, const char* datasetName, hid_t dataType, const void* data, int dimensions = 1, hsize_t *dims = NULL);
		
		// shorter way how to find values of maximum/minimum ...
		template<class T> T minValue(const T arg1, const T arg2) { return (arg1<arg2 ? arg1 : arg2); }
		template<class T> T maxValue(const T arg1, const T arg2) { return (arg1<arg2 ? arg2 : arg1); }
		// ... and avoid compiler yelling because of inability of complex numbers to be compared
		// these complex numbers handler functions are never been really used!
		template<class R> std::complex<R> minValue(const std::complex<R> arg1, const std::complex<R> arg2) { return std::complex<R>(arg1.real(),arg2.imag());}
		template<class R> std::complex<R> maxValue(const std::complex<R> arg1, const std::complex<R> arg2) { return std::complex<R>(arg2.real(),arg1.imag());}
		
		/// Saves RGB image data into file
		template <class R> void SaveRGBData(const RGB_generic<R> *data);
		
		/// Saves image data into file
		template <class T> void SaveData(const T *data);
		
	public:
		/// Constructor
		HDF5Writer(const char *fname, const VOI<PIXELS> *voi = NULL);
		
		/// Saves image information
		virtual void SaveImageInfo();
		
		/// Saves image description
		virtual int SaveDescription();
		
		/// Saves image data
		virtual void SaveImageData(const bool *data) {SaveData(data);};
		virtual void SaveImageData(const GRAY8 *data) {SaveData(data);};
		virtual void SaveImageData(const GRAY16 *data) {SaveData(data);};
		virtual void SaveImageData(const int *data) {SaveData(data);};
		virtual void SaveImageData(const RGB *data) {SaveRGBData(data);};
		virtual void SaveImageData(const RGB16 *data) {SaveRGBData(data);};
		virtual void SaveImageData(const float *data) {SaveData(data);};
		virtual void SaveImageData(const double *data) {SaveData(data);};
		virtual void SaveImageData(const Vector3d<float> *data) {SaveData(data);};
		virtual void SaveImageData(const Vector3d<double> *data) {SaveData(data);};
		virtual void SaveImageData(const std::complex<float> *data) {SaveData(data);};
		virtual void SaveImageData(const std::complex<double> *data) {SaveData(data);};
		
		~HDF5Writer();
	};
}

#endif
