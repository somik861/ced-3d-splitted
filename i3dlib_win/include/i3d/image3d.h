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


/** \file image3d.h
  \brief 3D image class and manipulation routines - header.

  This file contains the main Image3d template and closely related
  functions. 
 
  \author Petr Matula (pem@fi.muni.cz) 2000
  \author Petr Mejzlík (mejzlik@fi.muni.cz) 2000
  \author Pavel Matula (pam@fi.muni.cz) 2001
 
*/
#ifndef __IMAGE3D_H__
#define __IMAGE3D_H__

#ifdef __GNUG__
#pragma interface
#endif

#include <cstdio>
#include <iostream>
#include <valarray>
#include <string.h>

#include "basic.h"
#include "resolution.h"
#include "voi.h"
#include "imgfiles.h"
#include "vector3d.h"

/** \mainpage CBIA 3D image representation library
 * \section introduction Introduction
 * This library provides a \e representation of 1D, 2D and 3D \e images. The short name is \b
 * i3dcore. It is developed entirely in the C++ programming language with extensive use of \e templates.
 *
 * Every image is internally always represented as a 3D image. The dimensionality of the
 * image is understood as the result of 3 minus the number of fixed coordinates. This results
 * in the following means of representation:
 *
 * \arg 1D image is a line given by (x,0,0),
 * \arg 2D image is a plane given by (x,y,0),
 * \arg 3D image is a stack of same-sized planes given by (x,y,z).
 *
 * Images are composed from \e voxels (volume picture element) arranged in the \e regular \e orthogonal \e voxel \e grid.
 * The voxel is the carrier of the visual information which, in turn, is represented by a \e voxel \e type.
 * We support \e binary, \e grayscale, \e float and \e RGB voxel types. Note that the RGB voxel type, in
 * fact, increases the dimensionality by adding a colour component.
 *
 * The representation is governed by the template class i3d::Image3d \<VOXEL\> where the template
 * parameter defines voxel type. The class predominantely provides the load and save image methods as well as
 * many data accessing methods such as:
 *
 * \arg allocate memory for a new image
 * \arg copy a certain VOI out of the image
 * \arg get some image parameters: size, resolutions, etc.
 * \arg get pointers directly to image data
 *
 * The class can also store, besides the image array, information
 * about the resolution and offset of the image. However, not every supported image format
 * allows for storing and retrieving of such metadata.
 *
 * One may also be interested in the CBIA 3D image algorithms library, i3dalgo,
 * which provides various image processing routines.
 * See its documentation at http://cbia.fi.muni.cz/user_dirs/i3dlib_doc/i3dalgo/ .
 *
 *
 * \section guide Quick start with i3dcore
 * \subsection io Input/Output
 * The basic image class is i3d::Image3d. It is a common ground for all image
 * manipulating, processing and analysis functions.
 *
 * The simple instantiation is done by calling its constructor with the name of the image to be openned:
 * <tt> i3d::Image3d<i3d::GRAY8> my_image("lena.tif"); </tt> // open 8b grasyscale image
 *
 * Consequently, do some image processing.
 *
 * Saving the results is straightforward: 
 *
 * <tt>my_image.SaveImage("new_name.jpg");</tt> // save the image
 * 
 *
 * \subsection storage Data storage
 * 
 * The library supports various image formats: 
 * - I3D (internal)
 * - TIFF (requires <a href="http://www.libtiff.org/">libtiff</a>)
 * - JPEG (requires <a href="http://www.ijg.org/">libjpeg</a>)
 * - TARGA (internal)
 * - MetaIO (internal)
 * - ICS (requires <a href="http://libics.sourceforge.net/">libics</a>)  
 *  
 * When using any of them, default compression algorithm is used: 
 * - TIFF ... LZW (Lempel-Ziv-Welch)
 * - JPEG ... discrete cosine transform
 * - TARGA ... RLE (Run-length encoding)
 * - MetaIO ... None
 * - ICS ... Gzip (LZ77, Huffman or LZW)
 *
 * \subsection data Data representation
 * The I3D is capable of manipulation with 1b, 8b, 16b, 24b, 48b raster image data (TIFF and TARGA support 48b TrueColor images).
 * For this purpose, special data types have been defined:
 * - binary data: bool
 * - 8bit and 16bit grayscale: i3d::GRAY8 and i3d::GRAY16
 * - 24bit and 48bit three-channel: i3d::RGB and i3d::RGB16
 * - 32bit float
 *
 * The layout of image data in the memory is as follows. The whole image is stored using
 * std::valarray in a scalable one-dimensional array with row by row and plane by plane
 * voxel arrangement. Hence, the voxel at (x,y,z) is in the
 * i3d::Image3d::data [z * i3d::Image3d::GetSliceSize() + y * i3d::Image3d::GetWidth() + x].
 *
 * \section licensenote License
 * The library is licensed under the GNU GPL license. Its text is included in the library
 * and is also accessible from the documentation, see \ref gnulicense .
 *
 * \section support Supported Platforms 
 *
 *	Our goal is to develop the library according to the C++ standard. In principle, 
 *	it should work on any platform with a good C++ compiler. However, we have succesfully
 *	compiled and tested this library only on the following x86-based architectures:
 *
 *	\arg Microsoft Windows XP and Server 2003 with Microsoft Visual C++ 2005
 * 	\arg Linux 2.4 and Linux 2.6 with GNU C++ compiler 4.x.x
 *	\arg Mac OS X 10.5 Leopard - GNU C++ compiler 4.x.x
 *
 *	The installation guide can be found at http://cbia.fi.muni.cz/user_dirs/i3dlib_doc/install.html .
 *
 *
 * \section download Download
 * The sources of the CBIA's i3dalgo are freely available at
 * http://cbia.fi.muni.cz/projects/the-cbia-i3dcore-and-i3dalgo-libraries.html .
 * You may need to register before downloading.
 *
 * \section examples Examples
 * A collection of sample programs is present in the original source package of both
 * libraries. This collection is also available at 
 * http://cbia.fi.muni.cz/user_dirs/i3dlib_doc/i3d_examples.zip (20kB) for reference.
 *
 *   
 * \section authors Authors 
 *
 * It is a common work of members of <a href="http://cbia.fi.muni.cz/">CBIA</a> as well as students
 * from <a href="http://www.fi.muni.cz/">Faculty of informatics, Masaryk University</a>.
 * Nevertheless, the major contributors were:
 * Petr Mejzlík, Petr Matula <pem@fi.muni.cz>,
 * Pavel Matula <pam@fi.muni.cz> and David Svoboda <svoboda@fi.muni.cz>.
 *
 * <hr>
 * \section dis Disclaimer
 *
 * There are some header and source code files which are part of this
 * library but weren't created by the <a href="http://cbia.fi.muni.cz/">CBIA</a>.
 * We redistribute these files as a part of our library but do not
 * provide any warranty if using these codes.
 * 
 * This files are:
 * - msdir.h & msdir.c<br>
 *   author: Toni Ronkko
 */

/**	\page cstyle Coding Style
	Coding style will be discussed in our laboratory and the results of our
	discussion will be summarized here. 

	However, each public symbol (class, type, function, ...) should be commented. Commenting private symbols is 
	desirable since the documentation is ment also for the library developers. The documentation is writen in English.
*/
/*
	Prefere this commenting style:
	\verbinclude comments_good.txt

	Never use stars before documentation blocks such as
	\verbinclude comments_bad.txt
	It goes against ease of maintenance.
*/

/** Namespace of <b> i3d library </b>. This namespace contains all symbols 
declared and/or defined in i3dlib. 
 */
namespace i3d {

	/*****************************************************************************\
	*
	*                            Indexing functions
	*
	\******************************************************************************/
	inline size_t GetIndex(size_t x, size_t y, size_t z, 
		const Vector3d<size_t> &imgsize)
	{ return (z * imgsize.y + y) * imgsize.x + x; }

	inline size_t GetIndex(const Vector3d<size_t> &coord,
		const Vector3d<size_t> &imgsize)
	{return GetIndex(coord.x, coord.y, coord.z, imgsize); }


	/*****************************************************************************\
	*
	*                                 3D image       
	*
	\******************************************************************************/
	/**
	\brief The main template class which stores and manipulates the image data 

	\todo Go through the documentation and make it more consistent and accurate

	\note Functions GetVoxel, GetVoxelAddr, GetFirstVoxelAddr and OnBorder
	don't check whether the required voxel is available or whether the image 
	is not empty.
	*/
	template <class VOXEL> class I3D_CORE_EXPORT Image3d {
	public: 
		//--------------------------------------------------------------------------
		// Constructors and destructor
		//--------------------------------------------------------------------------
		/** Default constructor. It creates an empty image. */ 
		explicit Image3d(
			const Offset* off_ = 0, 
			const Resolution* res_ = 0) 
			: offset(), size(), resolution(), data()
		{ 
			if (off_) offset = *off_; 
			if (res_) resolution = *res_; 
		} 

		/** Constructor. Read image from a specified file and constructs the 
		Image3d object

		parameters:
		\param fname image filename or a regular expression 
		\param voi volume of interest to read from the file
		\param is_regex specifies whether the \p fname is regular filename 
		or a mask for regular expansion.
		\param channel which channel to read from the file.	Default value (-1) 
		means all channels. Currently, only ICS format supports this parameter.
		\param offset image offset (in microns)
		\param resolution image resolution (in pixels per microns)
		\p offset and \p resolution are optional parameters. If they are set to
		0 the values stored in the image data file are used (implicitly), otherwise 
		the argument values are used (explicitly).
		*/
		Image3d(const char * fname,
			const VOI<PIXELS> *voi = 0,
			bool is_regex = false,
			int channel = -1,
			const Offset* offset = 0,  
			const Resolution* resolution = 0); 

		/** Copy constructor. copy of VOI, if VOI == 0, whole image is copied
		VOI is in pixels and is relative to origin of image
		offset is recomputed apropriately, if resolution is not defined
		offset is simply added (i.e. it's supposed 1 pixel = 1 micron)
		*/
		Image3d (const Image3d&, const VOI<PIXELS> *voi = 0);

		/** Copy constructor. VOI is in microns, Image in intersection of
		VOI and src image is returned */
		Image3d (const Image3d&, const VOI<MICRONS> &voi); 

		/** Destructor: */ 
		virtual ~Image3d() 
		{}

		//--------------------------------------------------------------------------
		// Operators
		//--------------------------------------------------------------------------
		/** Assignment operator */ 
		Image3d& operator= (const Image3d&); 

		//--------------------------------------------------------------------------
		// Copy methods
		//--------------------------------------------------------------------------
		/** A function that copies the selected VOI from another image.
		Copies the contents of a VOI from the src image to the current image, allocating enough room to fit the copied data. The source and destination must not be the same image.
		 * \param src another (input) image
		 * \param voi the area you are interested in within the input image
		 * \param overrun whether the given VOI may overrun the input image domain
		 * \param padding_value if the VOI overruns the input image the area that corresponds to the area beyond the input image domain must be padded with some value.
		 */
		void CopyFromVOI(const Image3d<VOXEL> &src, 
							  const VOI<PIXELS> &voi,
							  bool overrun = false,
							  VOXEL padding_value = VOXEL(0));

		/** Copy a selected slice to a given output image. If the slice position is out of the image bounds, an InternalException is thrown.
		  * The output image is always 2D (i.e., its size in the z-axis is equal to 1 irrespective of the selected copying direction).
		  * The ordering of voxels in the output image follows the ordering in the input image. */
		void GetSliceX(Image3d<VOXEL> &img, size_t x) const;
		void GetSliceY(Image3d<VOXEL> &img, size_t y) const;
		void GetSliceZ(Image3d<VOXEL> &img, size_t z) const;

		/** Copy a 2D image to a given slice. If the slice position is out of the image bounds or the size of the given 2D image is not equal to 
		  * the size of the selected slice, an InternalException is thrown. */
		void SetSliceX(const Image3d<VOXEL> &img, size_t x);
		void SetSliceY(const Image3d<VOXEL> &img, size_t y);
		void SetSliceZ(const Image3d<VOXEL> &img, size_t z);

		/** Converts contents of another image (of possibly different type) into this one using supplied CONVERTER
		 * \param src source image to copy data from
		 */
		template <typename CONVERTER, typename VOXELIN>
		Image3d& ConvertFrom(const Image3d<VOXELIN> &src)
		{
			this->CopyMetaData(src);
			size_t srcSize = src.GetImageSize();
			for (size_t i = 0; i < srcSize; ++i)
				this->SetVoxel(i, CONVERTER(src.GetVoxel(i)));
			return *this;
		}

		/** Converts contents of another image (of possibly different type) into this one without any advanced logic (simple constructor of VOXEL type is used).
		 * \param src source image to copy data from
		 */
		template <typename VOXELIN>
		Image3d& ConvertFrom(const Image3d<VOXELIN> &src) { return ConvertFrom<VOXEL>(src); }

		//--------------------------------------------------------------------------
		// Input/Output functions
		//--------------------------------------------------------------------------
		/** Read 3D image from file. \returns true on success. 
		Parameters:
		\param fname image filename or a regular expression 
		\param voi volume of interest to read from the file
		\param is_regex specifies whether the \p fname is regular filename 
		or a mask for regular expansion.
		\param channel which channel to read from the file.	Default value (-1) 
		means all channels. Currently, only ICS format supports this parameter.
		\param offset image offset (in microns)
		\param resolution image resolution (in pixels per microns)
		\p offset and \p resolution are optional parameters. If they are set to
		0 the values stored in the image data file are used (implicitly), otherwise 
		the argument values are used (explicitly).
		*/
		void ReadImage(
			const char *fname,
			const VOI<PIXELS> *voi = 0,
			bool is_regex = false,
			int channel = -1,
			const Offset *offset = 0, 
			const Resolution *resolution = 0);

		/** SaveImage: Saves the image into a file(s) in specified format
		File format is guessed from extension of fname if ft == IMG_UNKNOWN

		IOException is thrown
		- if format for saving is not recognized or not supported
		- if some disk problems occurred
		*/
		void SaveImage(
			const char * fname, 
			FileFormat ft = IMG_UNKNOWN,
			bool comp = true,
			const VOI<PIXELS> *voi = NULL) const;

		//--------------------------------------------------------------------------
		// Get image properties
		//--------------------------------------------------------------------------
		/** Is the image empty? */
		bool IsEmpty() const 
		{ 
			return GetImageSize() == 0; 
		}

		/** Get the number of voxels in image. */
		size_t GetImageSize(void) const 
		{
			return size.x * size.y * size.z; 
		}

		/// Get the number of voxels per one slice.
		size_t GetSliceSize(void) const {return size.x * size.y; }

		/// Get the width (horizontal axis) of the image.
		size_t GetWidth(void) const     {return size.x; }

		/// Get the height (vertical axis) of the image.
		size_t GetHeight(void) const    {return size.y; } 

		/// Get number of slices per image.
		size_t GetNumSlices(void) const {return size.z; }

		/// Get the width (horizontal axis) of the image.
		size_t GetSizeX(void) const     {return size.x; }

		/// Get the height (vertical axis) of the image.
		size_t GetSizeY(void) const     {return size.y; } 

		/// Get number of slices per image.
		size_t GetSizeZ(void) const     {return size.z; }

		/** Returns minimal and maximal value in the Image. Returns minimum and maximum 
		in red green and blue, if the image is RGB or RGB16 */
		void GetRange (VOXEL & min, VOXEL & max) const;

		/** Returns minimal value in the Image and index of its occurence (the last one). 
		The function is not implemented for composed types like RGB, RGB16 etc. */
		VOXEL GetMinValue (size_t &index) const;
		VOXEL GetMinValue () const;

		/** Returns maximal value in the Image and index of its occurence (the last one). 
		The function is not implemented for composed types like RGB, RGB16 etc. */
		VOXEL GetMaxValue (size_t &index) const;
		VOXEL GetMaxValue () const;

		/** Returns k-percentile value in the Image. 
		The function is not implemented for composed types like RGB, RGB16 etc. */
		VOXEL GetKPercentileValue(float k) const;

		/// Get the offset of this image.
		const Offset& GetOffset() const {return offset;} 

		/// Get the resolution of this image.
		const Resolution& GetResolution() const {return resolution;} 
		
		/// Get the description of this image.
		const std::map<std::string, std::string>& GetDescription() const {return description;} 
		
		/// Get the dimensions of the image.
		const Vector3d<size_t>& GetSize() const {return size;}

		//--------------------------------------------------------------------------
		// Set image properties
		//--------------------------------------------------------------------------
		/// Set the offset for this image.
		void SetOffset(const Offset& off_) {offset = off_;} 

		/// Set the resolution for this image.
		void SetResolution(const Resolution& res_) {resolution = res_;} 
		
		/// Set description for this image.
		void SetDescription(const std::map<std::string, std::string> &description_) {description = description_;}
		
		/// Copy resolution, offset, size and allocate the memory
		template <class T> void CopyMetaData(const Image3d<T>& img)
		{
			 this->SetResolution(img.GetResolution());
			 this->SetOffset(img.GetOffset());
			 this->SetDescription(img.GetDescription());
			 this->MakeRoom(img.GetSize());
		}

        /** Change the number of slices. The content of the first <tt>min(sliceCount, GetSizeZ())</tt> 
            slices is preserved.
            
            @param[in] sliceCount The new number of slices.
        */
        void ChangeNumberOfSlices(size_t sliceCount);

		//--------------------------------------------------------------------------
		// Indexing
		//--------------------------------------------------------------------------
		/// Get the x-coordinate of the i-th voxel in the image data block.
		size_t GetX(size_t i) const     {return i % size.x; }

		/// Get the y-coordinate of the i-th voxel in the image data block.
		size_t GetY(size_t i) const     {return (i / size.x) % size.y; } 

		/// Get the z-coordinate of the i-th voxel in the image data block.
		size_t GetZ(size_t i) const     {return (i / size.x) / size.y; }

		/** Get the position of the voxel in the image data block (first
		position is O. */
		size_t GetIndex(size_t x, size_t y, size_t z) const
		{ return i3d::GetIndex(x,y,z,size); }

		size_t GetIndex(Vector3d<size_t> v) const
		{ return i3d::GetIndex(v.x, v.y, v.z, size); }

		/** get the coords from the position in the image buffer vector
		coords is Vector3d<int> type - for relative positions */
		/*Coords GetCoords(size_t i) const
		{ return Coords(GetX(i), GetY(i), GetZ(i)); }*/

		Vector3d<size_t> GetPos(size_t i) const
		{ return Vector3d<size_t>(GetX(i), GetY(i), GetZ(i)); }

		//--------------------------------------------------------------------------
		// Voxel & data access
		//--------------------------------------------------------------------------
		/** Get a voxel value (voxels are numbered from 0): */
		VOXEL GetVoxel(size_t x, size_t y, size_t z) const
		{ return data[i3d::GetIndex(x,y,z,size)]; }

		/** Get a voxel value (voxels are numbered from 0) */
		VOXEL GetVoxel(const Vector3d<size_t>& v) const
		{ return data[i3d::GetIndex(v.x, v.y, v.z, size)]; }

		/** Get a voxel value (voxels are numbered from 0) */
		VOXEL GetVoxel(size_t i) const
		{ return data[i]; }

		/** Get a voxel address (voxels are numbered from 0) */
		VOXEL* GetVoxelAddr(size_t x, size_t y, size_t z)
		{ return &data[i3d::GetIndex(x,y,z,size)]; }

		/** Get a voxel address (voxels are numbered from 0) */
		const VOXEL* GetVoxelAddr(size_t x, size_t y, size_t z) const
		{ std::valarray<VOXEL>& d = const_cast<std::valarray<VOXEL>&> (data);
		return &d[i3d::GetIndex(x,y,z,size)];
		}
		/** Get a voxel address (voxels are numbered from 0) */
		VOXEL* GetVoxelAddr(size_t i) 
		{ return &data[i]; }

		/** Get a voxel address (voxels are numbered from 0) */
		const VOXEL* GetVoxelAddr(size_t i) const
		{ std::valarray<VOXEL>& d = const_cast<std::valarray<VOXEL>&> (data);
		return &d[i];
		}

		/** Get the first voxel address (voxels are numbered from 0) */
		const VOXEL* GetFirstVoxelAddr() const
		{ std::valarray<VOXEL>& d = const_cast<std::valarray<VOXEL>&> (data);
		return &d[0];
		}

		/** Get the first voxel address (voxels are numbered from 0) */
		VOXEL* GetFirstVoxelAddr()
		{ return &data[0]; }

		/** Set a voxel to value (voxels are numbered from 0) */
		void SetVoxel(size_t i, VOXEL voxel)
		{ data[i] = voxel; }

		/** Set a voxel to value (voxels are numbered from 0) */
		void SetVoxel(size_t x, size_t y, size_t z, VOXEL voxel)
		{ data[i3d::GetIndex(x,y,z,size)] = voxel; }

		/** Set a voxel to value (voxels are numbered from 0) */
		void SetVoxel(const Vector3d<size_t>& v, VOXEL voxel)
		{ data[i3d::GetIndex(v.x, v.y, v.z, size)] = voxel; }

		/** Set all voxels to given value */
		void SetAllVoxels(VOXEL voxel)
		{ for (size_t i = 0; i < data.size(); i++) data[i] = voxel; }


		/** Set border voxels to a given value. It is for example useful if an algorithm needs 
		a special value at all border pixels. 
		For 2D images it works as one would expected :-).
		*/
		void SetBorderVoxels(VOXEL voxel);

		/** Synonym for GetFirstVoxelAddr() */
		VOXEL* begin()
		{ return GetFirstVoxelAddr(); }

		/** Pointer beyond the last image element */
		VOXEL* end()
		{ return GetFirstVoxelAddr() + GetImageSize(); }

		/** Synonym for const GetFirstVoxelAddr() */
		const VOXEL* begin() const
		{ return GetFirstVoxelAddr(); }

		/** Const pointer beyond the last image element */
		const VOXEL* end() const
		{ return GetFirstVoxelAddr() + GetImageSize(); }

		/** Returns the reference the the object 'data', which 
		is of the \c std::valarray data type */
		std::valarray<VOXEL> & GetVoxelData() 
		{ return data; }

		const std::valarray<VOXEL> & GetVoxelData() const
		{ return data; }


		void Clear()
		{
			memset(GetFirstVoxelAddr(), 0, size.x*size.y*size.z*sizeof(VOXEL));
		}

		/** 
			Pad image with the given value from each side. 
			The size of the image will increase by 2 * sz (sz at each side)

			Warning: voxel buffer will be reallocated!
		*/
		void PadImage(i3d::Vector3d<size_t> sz, VOXEL value = VOXEL(0));

		/** 
			Remove padding (it is the inverse to PadImage function). 
			The size of the image will decrease by 2 * sz (sz at each side)

			Warning: voxel buffer will be reallocated!
		*/
		void RemovePadding(i3d::Vector3d<size_t> sz);

        /** Cycle slices. Cycle the content of the slices in the interval
            <tt>[idxBegin, idxEnd)</tt> such that the slice at index
            <tt>idxFirst</tt> is shifted to index <tt>idxBegin</tt>.
        */
        void CycleSlices(size_t idxBegin, size_t idxEnd, size_t idxFirst);

		//--------------------------------------------------------------------------
		// Bounding box testing functions
		//--------------------------------------------------------------------------
		/// Is index i on the border of the image?
		bool OnBorder(const size_t i) const
		{
			return OnBorder(GetX(i), GetY(i), GetZ(i));
		}
		
		/// Is v on the border of the image?
		bool OnBorder(const Vector3d<size_t> v) const
		{
			return OnBorder(v.x, v.y, v.z);
		}

		/// Is (x,y,z) on the border of the image?
		bool OnBorder(const size_t x, const size_t y, const size_t z) const
		{	
			return (size.x != 1 && (x==0 || x==size.x-1)) 
				|| (size.y != 1 && (y==0 || y==size.y-1))
				|| (size.z != 1 && (z==0 || z==size.z-1)); 
		}

		/// Is index i on the width wide border of the image?
		bool OnWideBorder(const size_t i, const size_t width) const
		{
			return OnWideBorder(GetX(i), GetY(i), GetZ(i), width);
		}

		/// Is (x,y,z) on the width wide border of the image?
		bool OnWideBorder(const size_t x, const size_t y, const size_t z, const size_t width) const
		{	
			return (size.x > width && (x < width || (x >= size.x - width && x < size.x))) 
				|| (size.y > width && (y < width || (y >= size.y - width && y < size.y)))
				|| (size.z > width && (z < width || (z >= size.z - width && z < size.z))); 
		}

		/// Is the voxel [x,y,z] in this image?
		bool Include(int x, int y, int z) const
		{ return (x >= 0) && (y >=0) && (z >= 0) &&
		(x <= (int)size.x-1) && (y <= (int)size.y-1) && (z <= (int)size.z-1);
		}

		/// Flip the image along any axis
	   void Flip(bool xaxis, bool yaxis, bool zaxis);

		/// Is the voxel 'v' in this image?
		bool Include(const Vector3d<int> &v) const
		{ return Include(v.x, v.y, v.z); }

		/// Get this image 'voi'.
		VOI<MICRONS> GetVOI(void) const {
			return VOI<MICRONS>(offset,PixelsToMicrons(size,resolution)); }

		//--------------------------------------------------------------------------
		// Low level functions
		//--------------------------------------------------------------------------
		/** Free memory occupied by data and set size to (0,0,0) */
		void DisposeData()
		{
			size.x = size.y = size.z = 0;
			data.resize(0);
		}

		/** Allocate/reallocate voxel memory and set the image size.
		* The input are three dimensions. */
		void MakeRoom(size_t width, size_t height, size_t slices); 

		/** Allocate/reallocate voxel memory and set the image size.
		* The input is the dimension vector. */
		void MakeRoom(const Vector3d<size_t> &sz)
		{
			MakeRoom(sz.x, sz.y, sz.z);
		}

		/** Test, whether Image3d<T> can, in principle, be created from a file 
		of type itype: */ 
		bool TestConsistency(ImgVoxelType itype) const; 

		/** Return a file type consistent with the voxel type T: */ 
		ImgVoxelType ConsistentVoxelType () const; 


	protected: 
		//--------------------------------------------------------------------------
		// Non-public members
		//--------------------------------------------------------------------------
		/// position of the image in absolute coordinates in micrometers
		Offset offset;  

		/// size of the image (width x height x slices) in pixels 
		Vector3d<size_t> size; 

		/// image resolution in pixels per micrometer
		Resolution resolution; 

		/// image data buffer
		std::valarray<VOXEL> data;  
		
		/// image description
		std::map<std::string, std::string> description;
		
	}; // 3D image


	/***************************************************************************\
	*
	*                         Conversion functions
	*
	\***************************************************************************/
	/**
		works for GRAY8, GRAY16, float, and double
	*/
	template <class VOXEL> I3D_CORE_EXPORT void BinaryToScalar(const Image3d<bool> &bimg, Image3d<VOXEL> &simg);

	/**
		works for GRAY8 and GRAY16
	*/
	template <class VOXEL> I3D_CORE_EXPORT void GrayToBinary(const Image3d<VOXEL> &gimg, Image3d<bool> &bimg);

	template <class VOXELIN, class VOXELOUT> I3D_CORE_EXPORT void FloatToGray (const Image3d<VOXELIN> &fimg, Image3d<VOXELOUT> &gimg);
	template <class VOXELIN, class VOXELOUT> I3D_CORE_EXPORT void FloatToGrayNoWeight (const Image3d<VOXELIN> &fimg, Image3d<VOXELOUT> &gimg);
	template <class VOXELIN, class VOXELOUT> I3D_CORE_EXPORT void GrayToFloat(const Image3d<VOXELIN> &gimg, Image3d<VOXELOUT> &fimg);
	template <class VOXELIN, class VOXELOUT> I3D_CORE_EXPORT void GrayToFloatNormalized(const Image3d <VOXELIN> &gimg, Image3d <VOXELOUT> &fimg);


	/** Convert a RGB image into a tripple of grayscale images: */
	template <class FULL_COLOR, class COLOR_CHANNEL>
		I3D_CORE_EXPORT void RGBtoGray(const Image3d<FULL_COLOR>&, Image3d<COLOR_CHANNEL>& red, 
		Image3d<COLOR_CHANNEL>& green, Image3d<COLOR_CHANNEL>& blue);

	/** Copy channel (red... 0, green...1, blue...2) from RGB image into 
	grayscale images
	return false if channel is not 0, 1, or 2
	*/ 
	template < class FULL_COLOR, class GRAY_CHANNEL > I3D_CORE_EXPORT bool CopyChannel (
		const Image3d < FULL_COLOR > &rgb,
		Image3d < GRAY_CHANNEL > &gray, 
		int channel);

	template < class GRAY_CHANNEL, class FULL_COLOR > I3D_CORE_EXPORT bool CopyChannelBack ( 
		const Image3d < GRAY_CHANNEL > &gray,
		Image3d < FULL_COLOR > &rgb,
		int channel);

	/** Convert a tripple of grayscale images into a RGB image : */
	template <class COLOR_CHANNEL, class FULL_COLOR> I3D_CORE_EXPORT void GrayToRGB(
		const Image3d<COLOR_CHANNEL> &red,
		const Image3d<COLOR_CHANNEL> &green,
		const Image3d<COLOR_CHANNEL> &blue, 
		Image3d<FULL_COLOR> &rgb );

	/** Convert vector in microns to vector in pixels in given image space. Returns
        false if the vector is outside the image VOI */
	template <class T> inline bool MicronsToImagePixels(
		const Vector3d<float> &v_mic,
		const Image3d<T> &img,
        Vector3d<size_t> &v_pix) 
	{
        Vector3d<float> tmp = (v_mic - img.GetOffset()) * img.GetResolution().GetRes();
		if (tmp.x < 0 || tmp.y < 0 || tmp.z < 0 || tmp.x >= img.GetSizeX() || 
            tmp.y >= img.GetSizeY() || tmp.z >= img.GetSizeZ())
            return false;
        v_pix.x = (size_t)tmp.x;
        v_pix.y = (size_t)tmp.y;
        v_pix.z = (size_t)tmp.z;
        return true;
    }

	/***************************************************************************\
	*
	*                               Other functions
	*
	\***************************************************************************/
	/** Add a boundary to the image. The width of the boundary (in each axis) is
	defined by the parameter \p width */
	template <class VOXEL> I3D_CORE_EXPORT void GenerateDummyVoxels (
		const Image3d<VOXEL> & ImgIn, 
		Image3d<VOXEL> & ImgOut, 
		VOXEL Value, 
		const Vector3d<size_t> &width);


	/***************************************************************************\
	*
	*                               Vector field 3D
	*
	\***************************************************************************/
	/** Vector field is specialized 3d image, where each voxel has three 
	componenets wrapped	in Vector3d structure. Supposed TYPE may be float 
	or double. 
	\todo Move to a separate file and improve documentation and layout
	*/
	template < class TYPE> class I3D_CORE_EXPORT VectField3d
		: public Image3d<Vector3d<TYPE> > 
	{  
	public:
		//constructors
		/** Read vector field from a specified file and constructs the VectField3d object.
		*   (So far only MetaIO format is supported)
		*
		* parameters:
		* 
		* - 'is_regex' says, whether the input 'fname' is regular filename 
		*   or can be expected as a mask for regular expansion.
		*   (in metaOI format is this parameter irrelevant)
		* - 'channel' chooses the channel order which is going to be read.
		*   If default value (-1) is chosen, all the channels are read.
		*   For the time being, only ICS format supports this parameter.
		* - offset and resolution set the image layout in the real scene.
		*   Both of them are optional: if not set, the values stored in the
		*   image data file is used (implicitly), otherwise the argument
		*   values are used (explicitly).
		* 
		* */
		VectField3d(const char * fname,
			const VOI<PIXELS> *voi = 0,
			bool is_regex = false ,
			int channel = -1,
			const Offset* off_ = 0,  
			const Resolution* res_ = 0): 
				  Image3d<Vector3d<TYPE> >(fname, voi, is_regex, 
													channel, off_, res_)
		{}

		explicit VectField3d(const Offset* off_ = 0, 
			const Resolution* res_ = 0): Image3d<Vector3d<TYPE> >(off_, res_)
		{}


		/** Copy constructor: copy of VOI, if VOI == 0, whole image is copied
		VOI is in pixels and is relative to origin of image
		offset is recomputed apropriately, if resolution is not defined
		offset is simply added (i.e. it's supposed 1 pixel = 1 micron)
		*/
		VectField3d (const VectField3d& vf, 
						 const VOI<PIXELS> *voi = 0):
				  Image3d<Vector3d<TYPE> >(vf, voi){}

		/** Copy constructor, VOI is in microns, Image in intersection of
		VOI and src image is returned */
		VectField3d (const VectField3d& vf, const VOI<MICRONS> &voi):Image3d<Vector3d<TYPE> >(vf, voi){}

		/** Destructor: */ 
		~VectField3d() {} 
	};

} // i3d namespace

#endif
