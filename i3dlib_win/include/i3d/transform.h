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


/** \mainpage CBIA 3D image algorithms library
 * \section introduction Introduction
 * This library provides a palette of image processing algorithms. The short name is \b
 * i3dalgo. It is developed entirely in the C++ programming language with extensive use of \e templates.
 * Technically, it is directly dependent on the CBIA 3D image representation library, i3dcore,
 * which provides I/O operations and image representation. The i3dcore's documentation can be
 * found at http://cbia.fi.muni.cz/user_dirs/i3dlib_doc/i3dcore/ .
 *
 * All algorithms are somewhat connected to biomedical image processing. Still, many of them may be
 * recognized as a part of say standard image processing suite. The selection for algorithms was
 * driven by a real needs of people in CBIA most of the time. However, some classes of algorithms
 * were implemented mostly for experimental reasons. Note that all functions work on a single image
 * in contrast to, for instance, computation of the optical flow where at least two images need to be supplied.
 *
 * The variety of algorithms in the i3dalgo ranges from simple global thresholding over morphology to more
 * complex ones like, for instance, segmentation based on level sets. One may also find here many specialized
 * and/or complex algorithms based on the literature from the image processing field. In such cases,
 * the source is properly cited in the documentation.
 *
 *
 * \section functionality List of available common functions
 * - position independed operations
 *   - global thresholding: i3d::Threshold
 *   - adaptive thresholding: i3d::LocalThreshold
 *   - color inversion: i3d::Negative
 * - filtering
 *   - gaussian smoothing: i3d::Gauss
 * - changing the image layout
 *   - resampling: i3d::Resample
 *   - image flipping: i3d::SwapHoriz, i3d::SwapVert
 * - edge detecion operators:
 *   - Sobel: i3d::Sobel2D, i3d::Sobel3D
 *   - Canny: i3d::Canny2D, i3d::Canny3D
 *   - ISEF: i3d::ShenCastan2D, i3d::ShenCastan3D
 * - histogram manipulation: 
 *   - i3d::IntensityHist 
 * - rasterization
 *   - seed line based fool fill: i3d::FloodFill
 *   - drawing the line using DDA algorithm: i3d::DrawLine 
 *   - drawing the line using Bresenham algorithm: i3d::DrawLineBres
 *   - drawing polygon: i3d::DrawLines
 * - labeling algorithms
 *   - region labeling (Rosenfeld-Pfaltz alg.): i3d::LabeledImage3d::CreateRegions
 *   - region labeling (flood fill based): i3d::LabeledImage3d::CreateRegionsFF
 * - mathematical morphology
 *   - dilation: i3d::Dilation
 *   - erosion: i3d::Erosion
 *   - waterhsed: i3d::Watershed
 *   - opening: i3d::Opening
 *   - closing: i3d::Closing
 * - etc. (see <a href="modules.html">module documentation</a> for more)
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
 *
 * \section otherprojects Where to go from here?
 * Appart to this library, there are other independent developement projects based on the i3dcore and i3dalgo
 * in the CBIA. These tend to provide some more functionality in visualizations, modified or enhanced algorithms
 * or simply new algorithms for some dedicated field of biomedical image processing and analysis, for example
 * for the field of microarray imaging. The list of projects can be found at CBIA's official web pages,
 * http://cbia.fi.muni.cz/software-development.html .
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
 * - affine.h & affine.c<br>
 *   author: Philippe Thévenaz<br>
 *   reference: P. Thévenaz, T. Blu, M. Unser, "Interpolation Revisited," IEEE
 *   Transactions on Medical Imaging, vol. 19, no. 7, pp. 739-758, July 2000.
 *
 * */

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





/*
 * FILE: transform.h
 *
 * Image transformations
 *
 * Pavel Matula (pam@fi.muni.cz) 2001
 * Petr Matula (pem@fi.muni.cz) - Added resampling and resizing functions
 */

#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#ifdef __GNUG__
#pragma interface
#endif

#include "image3d.h"
#include "regions.h"
#include <vector>
#include <algorithm>
#include <functional>

namespace i3d {

/** Copy 2D slice slc to 3D image img at level z. It is expected img 
and slc have the same x and y size. InternalException is raised if 
this is not satisfied*/
template <class T> I3D_ALGO_EXPORT
void CopySlice(const Image3d<T> &slc, Image3d<T> &img, size_t z);

/** RemapIntensities maps all voxels according to vector map_fun
   size of the vector must be higher than the max intensity in image */
template <class VOXEL> I3D_ALGO_EXPORT 
void RemapIntensities(Image3d<VOXEL>& img, std::vector<VOXEL>& map_fun);

/** Mirror image intensities of the input image in order to obtain zero central differences on the border. */
template <class VOXEL> I3D_ALGO_EXPORT void Mirror(const Image3d<VOXEL> &in, Image3d<VOXEL> &out);

enum SamplingMode 
{
    NEAREST_NEIGHBOUR,
    LINEAR,
	 LANCZOS
};

  /** src's image data is resapled so that it has size (new_x, new_y, new_z)
     or size and new image dest is returned (resolution of dest is recomputed,
     so that the both images have same size in microns)
     Only NEAREST_NIEGHBOUR is implemented
  */
template <class T> I3D_ALGO_EXPORT
void Resample(const Image3d<T> &src, 
		Image3d<T> &dest, 
		size_t new_x, 
		size_t new_y, 
		size_t new_z, 
		SamplingMode m=NEAREST_NEIGHBOUR);

template <class T> I3D_ALGO_EXPORT 
void Resample(const Image3d<T> &src, 
		Image3d<T> &dest, 
		const Vector3d<size_t> &size, 
		SamplingMode m=NEAREST_NEIGHBOUR);
  
  /** src's image data is resized so that it has size (new_x, new_y, new_z)
     or v and new image dest is returned. new size is in pixels (size_t
     variants) or in microns (float variants)
     Only NEAREST_NIEGHBOUR is implemented
  */
 template <class T> I3D_ALGO_EXPORT
void Resize(const Image3d<T> &src, 
		Image3d<T> &dest, 
		size_t new_x, 
		size_t new_y, 
		size_t new_z, 
		SamplingMode m=NEAREST_NEIGHBOUR);

template <class T> I3D_ALGO_EXPORT 
void Resize(const Image3d<T> &src, 
		Image3d<T> &dest, 
		const Vector3d<size_t> &size, 
		SamplingMode m=NEAREST_NEIGHBOUR);

template <class T> I3D_ALGO_EXPORT 
void ResizeInMicrons(const Image3d<T> &src, 
		Image3d<T> &dest, 
		float new_x, 
		float new_y, 
		float new_z, 
		SamplingMode m = NEAREST_NEIGHBOUR);

template <class T> I3D_ALGO_EXPORT 
void ResizeInMicrons(const Image3d<T> &src, 
		Image3d<T> &dest, 
		const Vector3d<float> &size, 
		SamplingMode m=NEAREST_NEIGHBOUR);

RGB max(const RGB &v1, const RGB &v2);

/** Compute xy maximum projection dest of image src. The function resizes
image dest to have the same xy size as src. Its depth (z-size) is set to 1. 
x and y offset and esolution are copied from src. z offset is set to 0. */
template <class VOXEL> I3D_ALGO_EXPORT 
void Get_AF_XY(const Image3d<VOXEL> &src, Image3d<VOXEL> &dest);

/** Compute xy projection dest of input labeled image src. The given list vis indicates
label visibilities. This list SHOULD have a size of max_label + 1 bool values. If vis is nullptr,
all non-zero labels are visible by default. The parameter only_boundary gives the mode of projection 
(if only_boundary is true then only boundary pixels of all visible component projections are saved into 
the output, if only_boundary is false then all visible component projections are saved 
into the output image). The function resizes image dest to have the same xy size as src. Its 
depth (z-size) is set to 1. x and y offset and resolution are copied from src. z offset
is set to 0. */
template <class LABEL, class VOXEL> I3D_ALGO_EXPORT 
void Get_Labeled_AF_XY(const LabeledImage3d<LABEL, VOXEL> &src, Image3d<LABEL> &dest, 
					   const bool vis[], bool only_boundary);
  
/** Compute xz maximum projection dest of image src. The function resizes
image dest to have the same xz size as src. Its height (y-size) is set to 1. 
Resolution and x and z offset are copied from src. y offset is set to 0.*/
template <class VOXEL> I3D_ALGO_EXPORT 
void Get_AF_XZ(const Image3d<VOXEL> &src, Image3d<VOXEL> &dest);

/** Compute xy projection dest of input labeled image src. The given list vis indicates
label visibilities. This list SHOULD have a size of max_label + 1 bool values. If vis is nullptr,
all non-zero labels are visible by default. The parameter only_boundary gives the mode of projection 
(if only_boundary is true then only boundary pixels of all visible component projections are saved into 
the output, if only_boundary is false then all visible component projections are saved 
into the output image). The function resizes image dest to have the same xz size as src. Its 
height (y-size) is set to 1. x and z offset and resolution are copied from src. y offset
is set to 0. */
template <class LABEL, class VOXEL> I3D_ALGO_EXPORT 
void Get_Labeled_AF_XZ(const LabeledImage3d<LABEL, VOXEL> &src, Image3d<LABEL> &dest, 
					   const bool vis[], bool only_boundary);
  
/** Compute yz maximum projection dest of image src. The function resizes
image dest to have the same yz size as src. Its width (x-size) is set to 1. 
Resolution and y and z offset are copied from src. x offset is set to 0 */
template <class VOXEL> I3D_ALGO_EXPORT 
void Get_AF_YZ(const Image3d<VOXEL> &src, Image3d<VOXEL> &dest);

/** Compute xy projection dest of input labeled image src. The given list vis indicates
label visibilities. This list SHOULD have a size of max_label + 1 bool values. If vis is nullptr,
all non-zero labels are visible by default. The parameter only_boundary gives the mode of projection 
(if only_boundary is true then only boundary pixels of all visible component projections are saved into 
the output image, if only_boundary is false then all visible component projections are saved 
into the output image). The function resizes image dest to have the same yz size as src. Its 
width (x-size) is set to 1. y and z offset and resolution are copied from src. x offset
is set to 0. */
template <class LABEL, class VOXEL> I3D_ALGO_EXPORT 
void Get_Labeled_AF_YZ(const LabeledImage3d<LABEL, VOXEL> &src, Image3d<LABEL> &dest, 
					   const bool vis[], bool only_boundary);

/** Copy content of image src to image dest. Both offset and resolution are
taken into account. Only voxels from src overlapping with image dest are copied.
Voxels in dest that don't overlap with src are untouched. Currently only nearest 
neighbour interpolation is implemented. */
template <class VOXEL>  I3D_ALGO_EXPORT 
void CopyToImage(const Image3d<VOXEL> &src, Image3d<VOXEL> &dest);

/** Create image dest from image src. Only voxels inside ivoi (in pixels)
are used as an input. The output image is resampled to have requested size
(in pixels). Nearest neighbour method is used. Offset and resolution is 
appropriately set. */
template <class VOXEL> I3D_ALGO_EXPORT
void GetResampledSubimage(const Image3d<VOXEL> &src, Image3d<VOXEL> &dest,
						  const VOI<PIXELS> &ivoi, const Vector3d<size_t> &size);

  /** Perform affine transformation of image img using the matrix matrix
  // origin is with respect to the first voxel of the image
  // degree is the interpolation degree (Note: in my tests only 0 and 1 worked well. PEM)
  // if use_resolution = true, the the resolution of the input image is taken into account
  // Implementation uses source code from Philippe Thevenaz (see affine.h)
  // It uses two float arrays with the size equal to the number of voxels of img =>
  // it's relatively memory consuming operation.*/
template <class VOXEL> I3D_ALGO_EXPORT 
void AffineTransform(
		Image3d<VOXEL> &img, 
		const double matrix[4][4], 
		const Vector3d<double> &origin, 
		int degree = 0, 
		VOXEL bgcol = 0, 
		bool use_resolution = false);

/** Added by Vladimir Ulman (xulman@fi.muni.cz), 3.12.2004 */
/** Colors the input image Imask, result is stored into RGB image Iout.
 *  Input parameters are images of the same dimensions Iselect and Imask.
 *  Voxel value of Iselect at some given position determines the color to
 *  be used, the color is picked from the input vector rgb_map. The intesity
 *  of chosen color is linearly influenced by the voxel value of image Imask
 *  at respective position.
 *
 *  Another description by Petr Matula <pem@fi.muni.cz>
 *  Function MapColor creates RGB image Iout voxel by voxel according to the 
 *  input images Iselect and Imask. It is expected that Iselect and Imask 
 *  have the same size and Iout is resized to have the same size as these 
 *  images. Voxel values in image Iselect are interpreted as indices to 
 *  rgb_map modulo rgb_map.size(). Voxel values in Imask are interpreted as 
 *  a value (or intensity) of the color from the map. Intensities equal to 
 *  numeric_limits<T2>::max() mean no color change. Intensities equal to 
 *  numeric_limits<T2>::min() mean black color. Intensities between these 
 *  limits are linearly interpolated.  If the input images differ in size an 
 *  InternalException is raised.
 *  
 *  In a typical case, Iselect is a labelled image of components (each 
 *  connected compoent in the image has a unique label), Imask is the 
 *  original grayscale image, which was later segmented and labelled, and 
 *  rgb_map specifies the desired colors of the connected components. Note 
 *  that if the first color in rgb_map is black, the background is set to 
 *  zero. If the first color is white, the background voxels are copied to 
 *  the output as gray values.
 */
template <class T1,class T2> I3D_ALGO_EXPORT 
void MapColor(
		const Image3d<T1> &Iselect,
		const Image3d<T2> &Imask,
		Image3d<RGB> &Iout, 
		const std::vector<RGB> &rgb_map);

/** Computes 2D image Iout from mostly 3D (possibly 2D) input image Iin.
 *  The input image is scanned line by line, lines are paralel to the input parameter
 *  direction. 2D image Iout is formed by shortening each line into single voxel.
 *  The value of resulting voxel is either input parameter color in case
 *  when all pixels from respective line fullfill the input predicate pred, either
 *  the value of first voxel in given direction from respective line which does not
 *  fullfill the input predicated pred. The predicate should be unary function
 *  from T2 into bool.
 */
#define MAP_DIRECTION_LEFT_RIGHT	0 //x-coordinate will increase
#define MAP_DIRECTION_RIGHT_LEFT	1 //x-coordinate will decrease
#define MAP_DIRECTION_FRONT_REAR	2 //y-coordinate will decrease
#define MAP_DIRECTION_REAR_FRONT	3 //y-coordinate will increase
#define MAP_DIRECTION_BOTTOM_TOP	4 //z-coordinate will increase
#define MAP_DIRECTION_TOP_BOTTOM	5 //z-coordinate will decrease

template <class T2> 
class I3D_ALGO_EXPORT is_background: public std::function<bool(T2)> 
{
  public:
	bool operator()(const T2 &v) const {return (v == 0); }
};

template <class T2,class PRED> I3D_ALGO_EXPORT
void MapCondColor(
		const Image3d<T2> &Iin,
		Image3d<T2> &Iout,
		PRED pred,
		T2 color,
		const int direction);


/* Resample input image with Lanczos windowed sinc reconstruction filter
   input  - input
	 output - output (function lanczos_resample allocates memory for output itself)
	 factor - vector of 3 factors for resize
	 n			- parameter for Lanczos window (standards are 2 and 3)
*/
template <class VOXEL> I3D_ALGO_EXPORT 
void lanczos_resample(
		const Image3d<VOXEL> *input,
		Image3d<VOXEL> *&output,
		const float factor[3],
		const int n);


template <class VOXEL> I3D_ALGO_EXPORT 
void lanczos_resample(
		const Image3d<VOXEL> *input,
		Image3d<VOXEL> *&output,
		const Vector3d<float> factor,
		const int n);

/** Resample the image to the resolution required by the user */

template <class VOXEL> I3D_ALGO_EXPORT 
void ResampleToDesiredResolution (i3d::Image3d<VOXEL> & image, float xRes, float yRes, float zRes, SamplingMode m = LANCZOS);

template <class VOXEL> I3D_ALGO_EXPORT 
void ResampleToDesiredResolution (i3d::Image3d<VOXEL> & image, const i3d::Resolution &res, SamplingMode m = LANCZOS);

}

#endif
