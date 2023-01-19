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

/** \file imgfiles.h
	\brief Structures and functions for reading/writing image files - header.
 
	This file is intended for all the stuff common to reading and writting 
	various image formats. 

	\author Petr Mejzl�k (mejzlik@fi.muni.cz) 2000
	\author Petr Matula (pem@fi.muni.cz) 2001
	\author David Svoboda <svoboda@fi.muni.cz> 2001
	\modified by Maros Gonda (mano@mail.muni.cz) 2011
 */


#ifndef __IMGFILES_H__
#define __IMGFILES_H__

#ifdef __GNUG__
#	pragma interface
#endif

#include <string>
#include <vector>
#include <map>

#include "basic.h"
#include "vector3d.h"
#include "voi.h"
#include "resolution.h"

namespace i3d {

	/** \defgroup io Image input/output methods 
	\todo Describe how to add support fot a new file format
	*/
	///@{
	/***************************************************************************\
	*
	*                               Typedefs
	*
	\***************************************************************************/
	//--------------------------------------------------------------------------
	// FileList
	//--------------------------------------------------------------------------
	typedef std::vector<std::string> FileList;

	/***************************************************************************\
	*
	*                               Enumerations
	*
	\***************************************************************************/
	//--------------------------------------------------------------------------
	// File formats
	//--------------------------------------------------------------------------
	//--------------------------------------------------------------------------
	// modified Maros Gonda (mano@mail.muni.cz) 2011
	/** Supported image file formats */
	enum FileFormat {
		IMG_UNKNOWN, ///< unknown (unrecognized) image type
		IMG_TARGA, ///< Targa image file format
		IMG_I3D, ///< I3D image file - internal format of i3dlib
		IMG_JPEG, ///< Image JPEG format
		IMG_PNG, ///< PNG image format
		IMG_TIFF, ///< TIFF Image file format
		IMG_METAIO, ///< MetaIO image file format
		IMG_ICSv1, ///< Image Cytometry Standard format (version 1)
		IMG_ICSv2, ///< Image Cytometry Standard format (version 2)
		IMG_HDF5, ///< HDF5 file format
		IMG_DCM ///< DICOM images
	};

	//--------------------------------------------------------------------------
	// Voxel types
	//--------------------------------------------------------------------------
	/** Known voxel types. */
	enum ImgVoxelType {      
		UnknownVoxel, ///< Voxel type is unknown
		BinaryVoxel, ///< BINARY voxel
		Gray8Voxel, ///< 8-bit unsigned voxel - GRAY8
		Gray16Voxel, ///< 16-bit unsigned voxel - GRAY16
		IntegerVoxel, ///< signed integer voxel 
		RGBVoxel,  ///< RGB voxel with GRAY8 components
		RGB16Voxel, ///< RGB16 voxel with GRAY16 components
		FloatVoxel, ///< float voxel with single precision
		DoubleVoxel, ///< float voxel with double precision
		Complex32Voxel, ///< 32-bit complex type (complex<float>)
		Complex64Voxel, ///< 64-bit complex type (complex<double>)
		VectFloatVoxel, ///< \todo zjistit, co je toto a k cemu (od Zdendy/Vlada)
		VectDoubleVoxel ///< \todo zjistit, co je toto a k cemu (od Zdendy/Vlada)
	};


	/***************************************************************************\
	*
	*                               Structures
	*
	\***************************************************************************/
	//--------------------------------------------------------------------------
	// Image File Header
	//--------------------------------------------------------------------------
	/// modified by Maros Gonda (mano@mail.muni.cz) 2011
	/** General image file header structure description

	Compression types for different image files formats.
	It depends on the image format:
	- Targa ... RLE
	- JPG ... JPEG
	- PNG ... zlib
	- HDF5 ... zlib
	- TIFF (8bpp, 24bpp) ... LZW
	- TIFF (1bpp) ... CCITT Group 4
	- MetaIO ... raw data - no compression
	- ICS ... gzipped raw data 
	*/
	struct I3D_CORE_EXPORT ImageFileHeader
	{
		/// constructor
		ImageFileHeader(const char *s = "", 
			Vector3d<size_t> sz = Vector3d<size_t>(1,1,1),
			ImgVoxelType it = UnknownVoxel,
			bool comp = true,
			bool top = true, bool left = true):
		name(s), size(sz), itype(it), compression(comp), 
			zero_at_the_top(top), zero_on_the_left(left), 
			bpp(), color_inversion(false), offset(), 
			resolution(NULL) {};

		/** file name */	
		std::string	name;

		/** size of the image */
		Vector3d<size_t> size;

		/** type of voxel (Gray8, Binary, RGB, ...) */
		ImgVoxelType			itype;

		/** compression scheme of image data */
		bool		compression;

		/** orientation of the image */
		bool		zero_at_the_top,
			zero_on_the_left;

		/** bits per pixel (1b, 8b, 16b, 24b, 48b) */
		int		bpp; 

		/** BLACK may be '0' or '1'. Default is '0'.
		*                   color_inversion == false <=> BLACK is '0' */
		bool		color_inversion;

		/** Image offset - in microns */
		Offset 	offset;

		/** Image resolution */
		Vector3d<float> *resolution;
		
		///modified by Maros Gonda (mano@mail.muni.cz) 2011
		/** Image description */
		std::map<std::string, std::string> description;
		
		
	}; // ImageFileHeader

	struct I3D_CORE_EXPORT ImageHeader
	{
		/** image size */
		Vector3d<size_t> size;

		/** voxel type */
		ImgVoxelType type;

		/** image offset */
		Offset offset;

		/** image resolution */
		Resolution resolution;

		/** Constructor. */
		ImageHeader(const Vector3d<size_t> &s = Vector3d<size_t>(1,1,1), 
			        ImgVoxelType t = UnknownVoxel, 
					const Offset &o = Offset(), 
					const Vector3d<float> *r = NULL)
			: size(s), type(t), offset(o), resolution() 
		{
			if (r)
			{
				resolution = Resolution(*r);
			}
		}
	};

	//--------------------------------------------------------------------------
	// Datatype of table of implemented file formats
	//--------------------------------------------------------------------------
	/** Table of implemented image file format.
	Note that "Unknown" is the last in the table */
	typedef struct
	{
		/// filename
		const char *name;
		/// file extension
		const char *ext;
		/// type of the image file
		FileFormat type;
		/// maximum dimension supported by the image format
		size_t max_dim;
	} ImgFormatsTable;


	/***************************************************************************\
	*
	*                                 Constants
	*
	\***************************************************************************/
	//--------------------------------------------------------------------------
	// Table of implemented image formats
	//--------------------------------------------------------------------------
	/// supported image formats
	const ImgFormatsTable ImgFormat[]=
	{
		{"I3D", "i3d", IMG_I3D, 3},
		{"TARGA", "tga", IMG_TARGA, 2},
		{"JPEG", "jpg", IMG_JPEG, 2},
		{"PNG", "png", IMG_PNG, 2},
		{"TIFF", "tif", IMG_TIFF, 3},
		{"RAW", "mha", IMG_METAIO, 3},
		{"RAW", "mhd", IMG_METAIO, 3},
		{"ICS", "ics", IMG_ICSv2, 5},
		{"ICS", "ics", IMG_ICSv1, 5},
		{"HDF5", "h5", IMG_HDF5, 4},
		{"DCM", "dcm", IMG_DCM, 3}
	};


	/***************************************************************************\
	*
	*                                 Classes
	*
	\***************************************************************************/
	//--------------------------------------------------------------------------
	// Image reader
	//--------------------------------------------------------------------------
	/** General (abstract) object for reading image file formats */
	class I3D_CORE_EXPORT ImageReader
	{
	protected:
		/// image file header structure instantiation
		ImageFileHeader header;

		int channel;

		/** Request to read only specific part of the image. In general,
		* this is not supported in all image formats. Here, it will be
		* defined in selected formats only. */
		const VOI<PIXELS> *crop;

		/// load image data - abstract template method
		//template <class T> void LoadData(T *data) {}

	public:
		/// constructor
		ImageReader() :channel(-1), crop(0)  {};

		/// constructor
		ImageReader(const char *fname, const VOI<PIXELS> *voi = NULL) :
		header(fname), channel(-1), crop(voi) {};

		/// destructor
		virtual ~ImageReader();

		/// get the image files name associated to this image
		virtual size_t GetFileNames(FileList &fl);

		/// get image voxel type	
		ImgVoxelType GetVoxelType() { return header.itype; };

		/// get the image dimension	
		Vector3d<size_t> GetDim();

		/// get offet of the image
		Offset GetOffset() { return header.offset; };
		
		
		/// get the number of channels
		/// Important: returns 0 if the number of channels is unknown.
		virtual size_t GetNumChannels();

		/// choose the channel for reading
		virtual void ChooseChannel(int chan);

		/// get the image resolution
		Vector3d<float>* GetResolution() { return header.resolution; };
		
		/// get image description from header
		std::map<std::string, std::string>& GetDescription() { return header.description; };
		
		/// load image header
		virtual void LoadImageInfo() = 0;

		/// load gray8 image data
		virtual void LoadImageData(GRAY8 *data) = 0;
		/// load binary image data
		virtual void LoadImageData(bool *data) = 0;
		/// load rgb image data
		virtual void LoadImageData(RGB *data) = 0;
		/// load gray16 image data
		virtual void LoadImageData(GRAY16 *data) = 0;
		/// load rgb16 image data
		virtual void LoadImageData(RGB16 *data) = 0;
		/// load float data - empty function
		virtual void LoadImageData(float *data) {};
		/// load float data - empty function
		virtual void LoadImageData(double *data) {};
		/// load int data - empty function
		virtual void LoadImageData(int *data) {};
		/// load size_t data - empty function
		virtual void LoadImageData(size_t *data) {};
		/// load Vector3d<float> data - empty function
		virtual void LoadImageData(Vector3d<float> *data) {};
		/// load Vector3d<double> data - empty function
		virtual void LoadImageData(Vector3d<double> *data) {};
		/// load single complex data - empty function
		virtual void LoadImageData(std::complex<float> *data) {};
		/// load double complex data - empty function
		virtual void LoadImageData(std::complex<double> *data) {};
		

	};


	//--------------------------------------------------------------------------
	// Image Writer
	//--------------------------------------------------------------------------
	/** General object for writting image file formats */
	class I3D_CORE_EXPORT ImageWriter
	{
	protected:
		/// image file header structure instantiation
		ImageFileHeader	header;		
		
		/** Request to save only specific part of the image. In general,
		* this is not supported in all image formats. Here, it will be
		* defined in selected formats only. */
		const VOI<PIXELS> *crop;
		
		/// save image data - abstract template method		
		//		template <class T> void SaveData(const T *data) {};

	public:
		/// constructor
		ImageWriter(const char *fname, const VOI<PIXELS> *voi = NULL):
			header(fname), crop(voi) {};

		/// destructor
		virtual ~ImageWriter();

		/// set the image dimension	
		void SetDim(size_t w, size_t h, size_t d) 
		{
			header.size = Vector3d<size_t>(w,h,d);
		};

		/// set the image dimension	
		void SetDim(Vector3d<size_t> sz) 
		{
			header.size = sz;
		};

		/// set image voxel type	
		void SetVoxelType(ImgVoxelType vt) {header.itype = vt;};

		/** Set the type of compression used when saving the appropriate image
		* file. If 'comp' is false, no compression is used (if possible).
		* If 'comp' is treu, the default compression is applied. For TIFF 
		* image file format it is LZW compression, for TARGA format RLE scheme
		* is used, etc. */
		void SetCompression(bool comp) {header.compression = comp;};
		
		/// set image resolution
		void SetResolution(Vector3d<float> v);
		
		/// set image description
		void SetDescription(const std::map<std::string, std::string> &description) { 
				header.description = description;
		};
		
		/// save image header
		virtual void SaveImageInfo() {};
		
		/// set offet of the image
		void SetOffset(Offset _off) {header.offset = _off;};
		
		/// save gray8 image data	
		virtual void SaveImageData(const GRAY8 *data) = 0;
		/// save binary image data	
		virtual void SaveImageData(const bool *data) = 0;
		/// save rgb image data	
		virtual void SaveImageData(const RGB *data) = 0;
		/// save gray16 image data	
		virtual void SaveImageData(const GRAY16 *data) = 0;
		/// save rgb16 image data	
		virtual void SaveImageData(const RGB16 *data) = 0;
		/// save float image data
		virtual void SaveImageData(const float *data) {};
		/// save double image data
		virtual void SaveImageData(const double *data) {};
		/// save int image data
		virtual void SaveImageData(const int *data) {};
		/// save size_t image data
		virtual void SaveImageData(const size_t *data) {};
		/// save Vector3d<float> data - empty function
		virtual void SaveImageData(const Vector3d<float> *data) {};
		/// save Vector3d<double> data - empty function
		virtual void SaveImageData(const Vector3d<double> *data) {};
		/// save single complex image data
		virtual void SaveImageData(const std::complex<float> *data) {};
		/// save double complex image data
		virtual void SaveImageData(const std::complex<double> *data) {};
	};

	//--------------------------------------------------------------------------
	// Sequence reader
	//--------------------------------------------------------------------------
	/** The basic class for reading the image sequences. You can make filelist
	of TIF of TGA files to build one 3D image. Note, that reading/saving 
	resolution along z-axis is not possible in this case. For this purpose 
	some other image formats supporting 3D data representation are offered.
	
	This class is the ancestor of more specialized class I3DReader */
	class I3D_CORE_EXPORT SequenceReader:public ImageReader
	{
	protected:
		template <class T> void LoadData(T *data);
		FileList nlist;
		std::vector<ImageReader*> ireaders;

	public:
		SequenceReader() {};
		SequenceReader(const char *fnames, const VOI<PIXELS> *voi = NULL);
		SequenceReader(const FileList &namelist, const VOI<PIXELS> *voi);

		virtual void ChooseChannel(int chan);

		~SequenceReader();

		virtual size_t GetFileNames(FileList &fl);

		virtual void LoadImageInfo();

		virtual void LoadImageData(GRAY8 *data) {LoadData(data);};
		virtual void LoadImageData(bool *data) {LoadData(data);};
		virtual void LoadImageData(RGB *data) {LoadData(data);};
		virtual void LoadImageData(GRAY16 *data) {LoadData(data);};
		virtual void LoadImageData(RGB16 *data) {LoadData(data);};
		virtual void LoadImageData(Vector3d<float> *data) {LoadData(data);};
		virtual void LoadImageData(Vector3d<double> *data) {LoadData(data);};
	};

	//--------------------------------------------------------------------------
	// Sequence writer
	//--------------------------------------------------------------------------
	/** The basic class for writing the image sequences. You can use this
	class to store 3D image data in file formats that do not support the
	third dimension (TIF, TGA, JPG, PNG).
	This class is the ancestor of specialized class I3DWriter. */
	class I3D_CORE_EXPORT SequenceWriter:public ImageWriter
	{
	protected:
		template <class T> void SaveData(const T *data);
		std::vector<ImageWriter*> iwriters;
		std::string path, name, ext;
		FileFormat ft;

	public:
		SequenceWriter(const char *name_list, FileFormat ft = IMG_UNKNOWN);

		~SequenceWriter();

		virtual void SaveImageInfo();

		virtual void SaveImageData(const GRAY8 *data) {SaveData(data);};
		virtual void SaveImageData(const bool *data) {SaveData(data);};
		virtual void SaveImageData(const RGB *data) {SaveData(data);};
		virtual void SaveImageData(const GRAY16 *data) {SaveData(data);};
		virtual void SaveImageData(const RGB16 *data) {SaveData(data);};
		virtual void SaveImageData(const Vector3d<float> *data) {SaveData(data);};
		virtual void SaveImageData(const Vector3d<double> *data) {SaveData(data);};
	};

	/***************************************************************************\
	*
	*                               Functions
	*
	\***************************************************************************/
	//--------------------------------------------------------------------------
	// Conversions
	//--------------------------------------------------------------------------
	/** Convert string to voxel type. Supported strings are "BINARY", "GRAY8", 
	"GRAY16", "RGB", "RGB16", and "float". UnknownVoxel is returned 
	for other strings. String representation of voxel types is needed in 
	%i3d description file format. */
	I3D_CORE_EXPORT ImgVoxelType StringToVoxelType(const std::string &s);

	/** Convert voxel type to a suitable string. String representation of voxel 
	types is needed in %i3d description file format. */
	I3D_CORE_EXPORT std::string VoxelTypeToString(const ImgVoxelType vt);


	/** Conversion from string to file format */
	I3D_CORE_EXPORT FileFormat StringToFileFormat(const std::string &s);

	/** Conversion from file format to string */
	I3D_CORE_EXPORT std::string FileFormatToString(const FileFormat ff);


	/** Conversion from file extension to file format 
	note: extensions are without dot, e.g. "tga" for IMG_TARGA */
	I3D_CORE_EXPORT FileFormat ExtensionToFileFormat(const std::string &s);

	/** Conversion from file format to file extension */
	I3D_CORE_EXPORT std::string FileFormatToExtension(const FileFormat ff);


	//--------------------------------------------------------------------------
	// Guessing and info functions
	//--------------------------------------------------------------------------
	/** Tries to recognize image file format from the filename (extension). */
	I3D_CORE_EXPORT FileFormat GuessFileFormat(const char *fname);

	/** Returns the pixel type of a 2D image stored in fname or a voxel
	type of a 3D image referenced by fname.
	File format is guessed from extension of fname if ft == IMG_UNKNOWN */
	I3D_CORE_EXPORT ImgVoxelType ReadImageType(const char *fname, FileFormat ft = IMG_UNKNOWN);

	/** Returns information about an image size, type, offset, and resolution.
	  * File format is guessed from extension of fname if ft == IMG_UNKNOWN */
	I3D_CORE_EXPORT ImageHeader ReadImageHeader(const char *fname, FileFormat ft = IMG_UNKNOWN);

	/** Get the maximum dimensionality supported by the image format. \returns 
	Dimensionality of file format \p ff in ImgFormatsTable, \returns 2 if file 
	format is not found in the table. */
	I3D_CORE_EXPORT size_t GetMaxDimensionality(const FileFormat ff);

	///@} end of io group
}

#endif
