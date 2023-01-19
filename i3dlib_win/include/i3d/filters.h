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
 * FILE: filters.h
 *
 * Image filtering
 *
 * Petr Mejzlík (mejzlik@fi.muni.cz) 2000
 */

/** \file 
 * Image filtering functions.
 *
 * \author Petr Mejzlík (mejzlik@fi.muni.cz)
 * \date 2000
 */

#ifndef __FILTERS_H__
#define __FILTERS_H__

#ifdef __GNUG__
#pragma interface
#endif

#ifndef _MSC_VER
#include <cmath>
#endif
#include <valarray>
#include <stdexcept>
#include <iostream>
#include "basic.h"
#include "image3d.h"
#include "neighbours.h" 

namespace i3d {

	/** A memory buffer (the main reason for defining this class is its
   destructor, which automatically deallocates the buffer memory
   when leaving function/block) : */
struct I3D_ALGO_EXPORT Buffer {
	/// allocated memory
	char *start;
	/// allocated size
	unsigned long size;
	/// explicit constructor
	explicit Buffer(const unsigned long sz = 0): start(0), size(0) 
	{if (sz>0) start = new char[sz]; size = sz;}

	/// function allocating memory block
	bool allocate(const unsigned long sz)
	{ size = 0;
	  delete[] start;
	  if (sz>0) { start = new char[sz]; size = sz; }
	  return start != 0;
	}
	/// destructor
    ~Buffer() {delete[] start;}
  };

/***************************************************************************/



/* Types used to store the sum of filter elements: */
#if !defined(_ULONGLONG)
 #define _ULONGLONG unsigned long long
#endif


struct I3D_ALGO_EXPORT RGBD
{
  double red, green,blue;

  RGBD (const double r = 0.0, const double g = 0.0, const double b = 0.0):
	  red(r), green(g), blue(b) {};

  inline RGBD operator= (const RGB v) 
  {
	  red = (double)v.red; 
	  green = (double)v.green; 
	  blue = (double)v.blue; 
	  return *this;
  }

  /** definition of a new data type which should represent 
  	one color component */
  typedef double ELEMENT_TYPE;
};
    

template <class NUMBER> struct I3D_ALGO_EXPORT SumOf;
template<> struct I3D_ALGO_EXPORT SumOf<RGB> {typedef RGBD SUMTYPE;};
template<> struct I3D_ALGO_EXPORT SumOf<double> {typedef double SUMTYPE;};
template<> struct I3D_ALGO_EXPORT SumOf<float> {typedef double SUMTYPE;};
template<> struct I3D_ALGO_EXPORT SumOf<GRAY8> {typedef double SUMTYPE;};
template<> struct I3D_ALGO_EXPORT SumOf<GRAY16> {typedef double SUMTYPE;};
template<> struct I3D_ALGO_EXPORT SumOf<unsigned long> {typedef double SUMTYPE;};
template<> struct I3D_ALGO_EXPORT SumOf<_ULONGLONG> {typedef double SUMTYPE;};

template <class NUMBER> struct I3D_ALGO_EXPORT StrictSumOf;
template<> struct I3D_ALGO_EXPORT StrictSumOf<GRAY8> {typedef long int SUMTYPE;};
template<> struct I3D_ALGO_EXPORT StrictSumOf<GRAY16> {typedef long int SUMTYPE;};
template<> struct I3D_ALGO_EXPORT StrictSumOf<float> {typedef double SUMTYPE;};

/** \ingroup if
 * General filter structure
 */
template <class NUMBER> struct I3D_ALGO_EXPORT Filter 
{
	/// size of the window
	Vector3d<size_t> size; 

	/** filter window stored line-by-line (the last index
	* changing most rapidly) */
	NUMBER *win;  

	/// sum of win[]
	typename SumOf<NUMBER>::SUMTYPE sum;

	/// constructor
	Filter(): size(), win(0), sum(0) {}

	/// destructor
	~Filter() { if (win) delete[] win; };

	/// Get size (number of voxels) of the filter.
	size_t Size() const { return size.x * size.y * size.z;}

	/** Assignment operator */
	Filter& operator= (const Filter& src);

	/** Copy constructor (uses the assignment operator) */
	Filter (const Filter& src);

	/** Conversion operator */
	template <class NUMBER2> Filter& operator= (const Filter<NUMBER2>& src);

	/** Conversion in a form of a constructor */
	template <class NUMBER2> Filter (const Filter<NUMBER2>& src);
};

/** \ingroup if
 * Filter conversion (to another arithmetic type):
 */
template <class NUMBER, class NUMBER2>
	I3D_ALGO_EXPORT void Convert(Filter<NUMBER>& out, const Filter<NUMBER2>& in);

/** \ingroup if
 * "Conversion" to the same filter type - just a deep copy:
 */
template <class NUMBER> 
	void Convert(Filter<NUMBER>& out, const Filter<NUMBER>& in) {out = in;}


/** @{ */
/** @name Gauss filtering */

/** \ingroup if
   MakeGaussFilter1D computes a window for a 1D Gaussian filter given
   by the standard deviation (sigma) and a factor influencing the size
   of the window (widthFactor). The size of the window is
   2*[sigma*widthFactor], where [x] means the lowest integer larger than x.
   The filter is multiplied by a constant to get 1 on both ends of
   the window.
   The value of sigma must be in the range [0.01, 32], otherwise InternalException
   is thrown.
*/
I3D_ALGO_EXPORT 
Filter<double> MakeGaussFilter1D( double sigma, double widthFactor = 3.0);

/** \ingroup if
   Apply a 1D Gaussian filter a vector selected from data using slc. 
   The filter is given as one of the parameters, as well as a buffer,
   which has to be of the same size as the filter window 
   ( = filter.Size() * sizeof(VOXEL) ). If the optional parameter divide
   is false, then the result of the scalar product with the filter
   window is not divided by the sum of the window, which means that 
   the function computes just a convolution with the filter window.
   The range of each result is checked and an exception is raised
   if it exceeds numeric_limits<VOXEL>::max().
*/
template <class VOXEL> 
  I3D_ALGO_EXPORT void ApplyGauss1D(
		  VOXEL* data, 
		  const std::slice& slc, 
        Filter<double>& filter, Buffer& buf, bool divide = true);

/** \ingroup if
   Gauss applies a 1-3D Gaussian filter to an image. If some of sigmax, 
   sigmay, or sigmaz are zero, then the image is not filtered in 
   the corresponding axis. For instance, the image is filtered only in 
   the z axis by calling Gauss(image, 0, 0, sigma). 

   widthFactor influences the size of the filter window: the Gauss filter
   is implemented by consecutive application of a 1D Gauss filter with
   window size of 2*[sigma*widthFactor], where [x] means the lowest integer 
   larger than x.

   2D and 3D filters are computed by a consecutive application of
   two or three 1D Gaussian filters produced by MakeGaussFilter1D.
   The widthFactor parameter has the same meaning as in MakeGaussFilter1D. 

   If the optional parameter exact is false, the computation is done 
   in situ, however some rounding errors can occur. Otherwise, 
   a temporary buffer is allocated for storing the intermediate results. 
   The size of the buffer can be up to four times of the size of the image, 
   depending on the voxel type.
*/
template <class VOXEL> 
  I3D_ALGO_EXPORT void Gauss(
		  Image3d<VOXEL>&, 
		  double sigmax, double sigmay = 0.0, double sigmaz = 0.0,
        double widthFactor = 3.0, bool exact = true);

/** \ingroup if
 * STD_SIGMA == 1/sqrt(ln(4)) */
#define STD_SIGMA 0.84932180028801904272

/**
 \ingroup if
 * SimpleGauss: applies a simple Gauss filter (1,x,1), where x increases
 * with decreasing sigma, in all available dimensions of the image.
 * The function supposes that if the image has z-dimension then is has also
 * y-dimension and if it has y-dimension then is has also x-dimension.
 * With sigma == STD_SIGMA we get filter window (1,2,1)*1/4. The parameter
 * exact has the same meaning as in the Gauss() function.
 */
template <class VOXEL> void SimpleGauss(
		Image3d<VOXEL>& img, 
		double sigma = STD_SIGMA, 
		bool exact = true);



//this one is defined later in this file
template <class VOXEL> struct I3D_ALGO_EXPORT Separable3dFilter;

/** \ingroup if
 \brief Changes the separable filter so that it be Gaussian-shaped.

 The content of input filter is removed first in all directions (along all three axes). Directions along
 axes are then filled with coefficients of Gaussian filters using respective sigmas. Also, the span of the
 filter along each direction is proportional to the value of the respective \e sigma and \e width. Axes are selected
 according to the values of respective sigmas. Non-zero value indicates the presence of given axis in the created
 filter. Default \e width values are 3.0.

 \param[in,out] filter		reference to the filter structure to be filled in
 \param[in] sigmaX		sigma of the Gauss filter's part along x-axis
 \param[in] sigmaY		sigma of the Gauss filter's part along y-axis
 \param[in] sigmaZ		sigma of the Gauss filter's part along z-axis
 \param[in] widthX		width of the filter along x-axis which would be roundup(sigma*width)*2+1 in reality
 \param[in] widthY		width of the filter along x-axis which would be roundup(sigma*width)*2+1 in reality
 \param[in] widthZ		width of the filter along x-axis which would be roundup(sigma*width)*2+1 in reality

 \author Vladimír Ulman
 \date 2007
*/
template <class VOXEL>
  I3D_ALGO_EXPORT void EstimateGaussKernel(struct Separable3dFilter <VOXEL > &filter,
						   const VOXEL sigmaX,
						   const VOXEL sigmaY,
						   const VOXEL sigmaZ,
						   const float widthX = 3.0,
						   const float widthY = 3.0,
						   const float widthZ = 3.0);

/**
 \ingroup if
 \brief Apply gaussian blur on image.

 This is a convolution with classical FIR (Finite Impulse Response) filter. Border is extended by zeros.

 The \e Sigma is the same for all involved directions of Gaussian. Also, the span of the filter along each
 direction is proportional to the value of the same single \e Sigma and \e Width. The selection of axes
 involved in the filtering depends on the respective dimensions of input image. Default \e Width value is 3.0.

 \note \b Attention: \e In and \e Out images must be different! If both references point to the same image (memory)
 the result of filtering is not valid!

\param[in] In		input Image3d<>
\param[out] Out		output (Gaussian blurred) Image3d<>
\param[in] Sigma	Sigma of the Gauss filter
\param[in] Width	Width of the Gauss filter

\author Vladimír Ulman (xulman@fi.muni.cz)
\date 2007
 */
template <class VOXEL> I3D_ALGO_EXPORT void GaussFIR(Image3d <VOXEL> const &In, Image3d <VOXEL> &Out,
				const VOXEL Sigma, const float Width=3.0);

/**
 \ingroup if
 \brief Apply gaussian blur on image.

 This is a convolution with classical FIR (Finite Impulse Response) filter. Border is extended by zeros.

 The \e Sigma is the same for all involved directions of Gaussian. Also, the span of the filter along each
 direction is proportional to the value of the same single \e Sigma and \e Width. The selection of axes
 involved in the filtering depends on the respective dimensions of input image. Default \e Width value is 3.0.

 \note Be aware of the fact that this is just a wrapper to the GaussFIR(InImage,OutImage,...) function.
 The image \e img is first copied aside what introduces some latency.

\param[in,out] img	input and output (Gaussian blurred) Image3d<>
\param[in] Sigma	Sigma of the Gauss filter
\param[in] Width	Width of the Gauss filter

\author Vladimír Ulman (xulman@fi.muni.cz)
\date 2007
 */
template <class VOXEL> I3D_ALGO_EXPORT void GaussFIR(Image3d <VOXEL> &img,
				const VOXEL Sigma, const float Width=3.0);

/**
 \ingroup if
 \brief Apply gaussian blur on image.

 This is a convolution with classical FIR (Finite Impulse Response) filter. Border is extended by zeros.

 The function uses different \e Sigma for filtering of each axis. Also, the span of the
 filter along each direction is proportional to the value of the respective \e Sigma and \e Width. Axes are selected
 according to the values of respective sigmas and according to the size of input image along direction in question.
 Non-zero value of given \e Sigma indicates the wish to filter along respective axis. Default \e Width values are 3.0.

 \note \b Attention: \e In and \e Out images must be different! If both references point to the same image (memory)
 the result of filtering is not valid!

\param[in] In		input Image3d<>
\param[out] Out		output (Gaussian blurred) Image3d<>
\param[in] SigmaX	Sigma of the Gauss filter along x-axis
\param[in] SigmaY	Sigma of the Gauss filter along y-axis
\param[in] SigmaZ	Sigma of the Gauss filter along z-axis
\param[in] WidthX	Width of the Gauss filter along x-axis
\param[in] WidthY	Width of the Gauss filter along y-axis
\param[in] WidthZ	Width of the Gauss filter along z-axis

\author Vladimír Ulman (xulman@fi.muni.cz)
\date 2007
 */
template <class VOXEL> I3D_ALGO_EXPORT void GaussFIR(Image3d <VOXEL> const &In, Image3d <VOXEL> &Out,
				const VOXEL SigmaX, const VOXEL SigmaY, const VOXEL SigmaZ,
				const float WidthX=3.0, const float WidthY=3.0, const float WidthZ=3.0);

/**
 \ingroup if
 \brief Apply gaussian blur on image.

 This is a convolution with classical FIR (Finite Impulse Response) filter. Border is extended by zeros.

 The function uses different \e Sigma for filtering of each axis. Also, the span of the
 filter along each direction is proportional to the value of the respective \e Sigma and \e Width. Axes are selected
 according to the values of respective sigmas and according to the size of input image along direction in question.
 Non-zero value of given \e Sigma indicates the wish to filter along respective axis. Default \e Width values are 3.0.

 \note Be aware of the fact that this is just a wrapper to the GaussFIR(InImage,OutImage,...) function.
 The image \e img is first copied aside what introduces some latency.

\param[in,out] img	input and output (Gaussian blurred) Image3d<>
\param[in] SigmaX	Sigma of the Gauss filter along x-axis
\param[in] SigmaY	Sigma of the Gauss filter along y-axis
\param[in] SigmaZ	Sigma of the Gauss filter along z-axis
\param[in] WidthX	Width of the Gauss filter along x-axis
\param[in] WidthY	Width of the Gauss filter along y-axis
\param[in] WidthZ	Width of the Gauss filter along z-axis

\author Vladimír Ulman (xulman@fi.muni.cz)
\date 2007
 */
template <class VOXEL> I3D_ALGO_EXPORT void GaussFIR(Image3d <VOXEL> &img,
				const VOXEL SigmaX, const VOXEL SigmaY, const VOXEL SigmaZ,
				const float WidthX=3.0, const float WidthY=3.0, const float WidthZ=3.0);

/**
 \ingroup if
 \brief Apply gaussian blur on image when the Gauss filter is aproximated by IIR filter.

 This is a recursive convolution with IIR (Infinite Impulse Response) filter. The filter is estimated
 according to [Vliet, Young and Ginkel, 2002]. The borders are treated by extending the boundary value as
 neccessary, according to [Triggs and Sdika, 2006].

 The \e Sigma is the same for all involved directions of Gaussian. The selection of axes
 involved in the filtering depends on the respective dimensions of input image.

 \e Sigma shouldn't be smaller than 1.0.

\param[in,out] img	input and output (Gaussian blurred) Image3d<>
\param[in] Sigma	Sigma of the Gauss filter

 \b Literature: I. T. Young, L. J. van Vliet and M. van Ginkel. Recursive Gabor filtering.
 In \b Signal processing 50, 11. Pages 2798-2805. 2002.

 \b Literature: B. Triggs and M. Sdika. Boundary conditions for Young-van Vliet recursive filtering.
 In \b Signal \b processing 54, 5. 2006.

 \note This is a prefered IIR implementation. It is faster then FIR Gauss. The difference becomes even more substantional
 as \e Sigma increases roughly over 3.

 The function is instantiated only for voxel types \c float and \c double.

\author Vladimír Ulman (xulman@fi.muni.cz)
\date 2007
*/
template <class VOXEL> I3D_ALGO_EXPORT void GaussIIR(Image3d <VOXEL> &img, const VOXEL Sigma);

/** A wrapper applying IIR Gaussian filter on an input grayscale image. */
template <class VOXEL, class PRECISION> I3D_ALGO_EXPORT void GrayGaussIIR(Image3d <VOXEL> &img, const PRECISION Sigma);

/**
 \ingroup if
 \brief Apply gaussian blur on image when the Gauss filter is aproximated by IIR filter.

 This is a recursive convolution with IIR (Infinite Impulse Response) filter. The filter is estimated
 according to [Vliet, Young and Ginkel, 2002]. The borders are treated by extending the boundary value as
 neccessary, according to [Triggs and Sdika, 2006].

 The function uses different \e Sigma for filtering of each axis. Axes are selected
 according to the values of respective sigmas and according to the size of input image
 along direction in question. Non-zero value of given \e Sigma indicates the wish to filter
 along respective axis.

 \e Sigma shouldn't be smaller than 1.0. Or should be exactly zero to show along which axis
 filtering shouldn't take place.

\param[in,out] img	input and output (Gaussian blurred) Image3d<>
\param[in] SigmaX	Sigma of the Gauss filter along x-axis
\param[in] SigmaY	Sigma of the Gauss filter along y-axis
\param[in] SigmaZ	Sigma of the Gauss filter along z-axis

 \b Literature: I. T. Young, L. J. van Vliet and M. van Ginkel. Recursive Gabor filtering.
 In \b Signal processing 50, 11. Pages 2798-2805. 2002.

 \b Literature: B. Triggs and M. Sdika. Boundary conditions for Young-van Vliet recursive filtering.
 In \b Signal \b processing 54, 5. 2006.

 \note This is a prefered IIR implementation. It is faster then FIR Gauss. The difference becomes even more substantional
 as \e Sigma increases roughly over 3.

 The function is instantiated only for voxel types \c float and \c double.

\author Vladimír Ulman (xulman@fi.muni.cz)
\date 2007
*/
template <class VOXEL> I3D_ALGO_EXPORT void GaussIIR(Image3d <VOXEL> &img,
			const VOXEL SigmaX, const VOXEL SigmaY, const VOXEL SigmaZ); 

/** A wrapper applying IIR Gaussian filter on an input grayscale image. */
template <class VOXEL, class PRECISION> I3D_ALGO_EXPORT void GrayGaussIIR(Image3d <VOXEL> &img,
			const PRECISION SigmaX, const PRECISION SigmaY, const PRECISION SigmaZ); 

/** @} */

/** \ingroup edge
  Sobel applies a Sobel (2D edge detector) filter to each slice of an image.
  only vertical or only horizontal filtering can be called.
  if both vertical and horizontal filtering is demanded then the resultant
  voxel is computed as a length of vector (vertical_result, horizontal_result) 
*/
template<class VOXEL> 
  I3D_ALGO_EXPORT void Sobel(Image3d<VOXEL>&, 
                           bool do_vertical = true, 
			   bool do_horizontal = true);

/** \ingroup edge
  Computes image Laplacian. (it has sense for signed data types only)
*/
template<class VOXEL> 
  I3D_ALGO_EXPORT void Laplace(const Image3d<VOXEL>&in, Image3d<VOXEL>&out);


/** \ingroup if
 * Suppress pixels differing too much from its neigbours
 * let avg(i) be the avarage intensity of the neigbours of pixel i
 * in the image in
 * then this rule is applied in each pixel:
 *    out(i) = in(i) if (abs(avg(i)-in(i)) < thres )
 *    out(i) = avg(i) otherwise
 */
  template <class T> I3D_ALGO_EXPORT 
  void SuppresHotPixels(
		  const Image3d<T>& in, Image3d<T>& out,
        const Neighbourhood& neib, T thres);



/** \ingroup edge
  \brief This non-linear filter is designed to supress high frequencies in input image and not to blur the sharp and significant edges in the image.
  
  This non-linear filter is designed to supress high frequencies in input image
  and not to blur the sharp and significant edges in the image.
  The implementation 
  of this filter is based on the article:  Jong-Sen Lee: Digital Image Smoothing
  and the Sigma Filter, Computer Vision, Graphics and Image processing, volume 
  24, 255-269, year 1983.    
  The parameters are:  
  in - input image
  out -- output image
  neib -- the type of neighbourhood, where the weighted sigma sum should be computed
  neib1 -- the type of neighbourhood, where the average of immediate neighbours 
  should be computed  sigma -- the maximal deviation (it has similar mean as the 
  sigma parameter in classic gaussian).  
  tres -- value of auxilliary treshold.

  The Algorithm:
  For every voxel of the input image:
  1) Compute first the tolerance interval \f$T\f$: \f$T = (x_i - sigma, x_i + sigma)\f$.
     
  2) Compute weighted average of voxel values in the "neib" neighbourhood.
  
     \f[WeightedSum =  \sum_{x \in AllVoxelsInNeib} ( x * delta_x )\f]
     \f[WeightedDivider = \sum_{x \in AllVoxelsInNeib} (delta_x)\f]
     \f[WeightedAverage = WeightedSum / WeightedDivider\f]

       where \f$delta_x = 1 if  x \in T\f$, otherwise \f$delta_x = 0\f$.

	     
  3) \f[OutputVoxel = WeightedSum if WeightedDivider is > tres\f]
     else
     \f[ImmediateNeighborsAverage = \sum_{x \in AllVoxelsInNeib1} x / |{AllVoxelsInNeib1}|\f]
     \f[OutputVoxel = ImmediateNeighborsAverage\f]

	  
   The Meaning:
       In steps 1 and 2 of the algorithm we make only better gaussian, We don't 
       compute the average from the voxels, which Intesity value is far from
       the value of the central voxel of the neighbourhood. This should supress
       the noise and should not blur the significcant edges.
       In the fourth step we can supress some hot cluster noise. If the central
       voxel has the intensity value far from the values of his neighbours 
       (The Weighted_Divider is small number), it is probably member of 
       "hot cluster", so we should save the Immediate_neighbours_Average in the 
       output image rather than the Weighted_average.	  	     
       
   The usage:
   input and output image should be GRAY8, GRAY16 or float.
   the "neib" parameter is supposed to be the box neighbourhood constructed with 
   function     
   void ConstructBoxNeighbourhood(Neighbourhood nb,double r1, double r2, double r3)
   (see neighbours.h)
   
   the "neib1" parameter should be the classic constant 4 or 8 neighbourhood in 2D,
   or   6, 18, or 26 neighbourhood in 3D. (See neighbours.h)

   the parameter "sigma" should be relative small (5-20) fo noisy low contrast
   images.
   the parameter "tres" shoulb be < 4 for 7x7 neighbourhood in 2D < 3 for 5x5
   neighbourhood.

   Pretty results can be obtained by iterative use of the filter with constant 
   or growing sigma. (the output of one iteration is the input of next iteration)

  */
template <class VOXEL> 
I3D_ALGO_EXPORT void SigmaFilter(
		const Image3d<VOXEL>& in, 
		Image3d<VOXEL>& out,
      const Neighbourhood& neib, 
		const Neighbourhood & neib1, 
		VOXEL sigma,
      int tres);



/** @{ */
/** @name Separable convolution */

/**
 \ingroup if
 \brief Structure for representing separable filter of arbitrary sizes in each directions/axis.

 \e xLength holds the size of the filter component for x-axis.
 
 For instance: \e xData points to an array of total length of \e xLength.
 Total length in each direction/axis must be odd number because of central
 voxel in the array. Zero length denotes that this direction is not used
 (this also allows for specifing 1D filter for given direction or 2D filter).

 Convolution is computed by convolving \e fdata over original data at some point.
 This amounts to sum of multiplications. The sum is divided afterwards by div constant
 in order to get final (and hopefully more precise) result.

 The structure also includes DisposeData() function which returns all memory allocated
 for the filter data (<em>[xyz]Data</em> variables). The structure itself is not destroyed (removed
 from memory) by the call of this function.
 
\author Vladimír Ulman (xulman@fi.muni.cz)
\date 2007
 */
template <class VOXEL> struct I3D_ALGO_EXPORT Separable3dFilter
{
    VOXEL *xData;
    VOXEL *yData;
    VOXEL *zData;

    VOXEL xDiv;
    VOXEL yDiv;
    VOXEL zDiv;

    long xLength;
    long yLength;
    long zLength;

    /** empty constructor */
    Separable3dFilter():xData(NULL), yData(NULL), zData(NULL), xDiv(1), yDiv(1), zDiv(1), xLength(0), yLength(0), zLength(0) { };
    /** copy constructor, if mirror=1 then it makes an identical copy with the only exception
     * that \e this-><em>[xyz]Data</em> are stored in the reverse order in comparison to the original <em>f,[xyz]Data</em>
     */
    Separable3dFilter(struct Separable3dFilter<VOXEL> const &f, int mirror=0);
    ~Separable3dFilter();

    /** prints the content of the structure to the screen */
    void PrintFilter(void);

    /** frees the data arrays <em>[xyz]Data</em> */
    void DisposeData(void);
};

/**
 \ingroup if
 \brief Structure containing data that is used for input image expansion.

 Two arrays are used for every direction/axis (both arrays are of the same
 length). One array acts as prefix while the second acts as postfix in the
 given direction.

 For instance: for x-axis 1D convolution rows of input image are extended in
 such way that first the \e xDataPre sequence is concatenated by original data
 and then \e xDataPost is added. The row length is increased by 2 times \e xLength.

 The structure also includes DisposeData() function which returns all memory
 allocated for the padding data (<em>[xyz]Data[Pre/Post]</em> variables). The structure
 itself is not destroyed (removed from memory) by the call of this function.
 
\author Vladimír Ulman (xulman@fi.muni.cz)
\date 2007
*/
template <class VOXEL> struct I3D_ALGO_EXPORT BorderPadding
{ 
    VOXEL *xDataPre, *xDataPost;
    VOXEL *yDataPre, *yDataPost;
    VOXEL *zDataPre, *zDataPost;
    long xLength;
    long yLength;
    long zLength;

    /** empty constructor */
    BorderPadding():xDataPre(0), xDataPost(0), yDataPre(0), yDataPost(0), zDataPre(0), zDataPost(0), xLength(0), yLength(0), zLength(0) { };
    /** copy constructor, if mirror=1 then it makes an identical copy with the only exception
     * that <em>[xyz]Data[Pre/Post]</em> are stored in the reverse order in comparison to the original <em>f,[xyz]Data[Pre/Post]</em>
     */
    BorderPadding(struct BorderPadding<VOXEL> const &f, int mirror=0);
    ~BorderPadding();

    /** prints the content of the structure to the screen */
    void PrintPaddings(void);

    /** frees the data arrays <em>[xyz]Data[Pre/Post]</em> */
    void DisposeData(void);
};

/**
 \ingroup if
 \brief Changes the BorderPadding structure to describe zero image boundary extension.

 The content of the input border paddings structure is removed in all directions (along all three axes) first.
 Some axes, according to the directions set in the convolution filter, are then filled with
 zeros so that it describes zero extension. The widths of the
 extensions (3 possible extensions due to 3 possible axes) is deduced from the filter spans.

 For example see the code of GaussFIR() in filters.cc.

 \param[in] filter		reference to a filter to be filtered with
 \param[in,out] b		reference to the paddings structure

 \author Vladimír Ulman
 \date 2007
*/
template <class VOXEL> I3D_ALGO_EXPORT
	void PrepareZeroBoundaryForFilter(struct Separable3dFilter <VOXEL > const &filter, BorderPadding<VOXEL> &b);

/**
 \ingroup if
 \brief Convolution of input image extended by given user data.

 -# \b Input image: \e d (a regular float or double i3d image)
 -# \b Output image: convolved copy of input image inc. its metadata (resolution, offset, dimensions).
 The size of output image is changed.
 -# \b Return value: non-zero on error, otherwise zero (indicating no problem).

 \b Specification:

 Input image can be either 1D, 2D or 3D, the function will learn that from the filter.

 Convolution mask is given by set of 1D arrays each of odd length (= center pixel + left and right
 parts of equal lengths). The corresponding filter would be constructed by convolving 2 or 3
 arrays extended to 2D or 3D by zero-padding, i.e. only separable filters can be
 processed by this function.

 In order to make output file of the same dimension as the input file, the input file must be
 extended by an border of specific size. The border data can be specified by border structure
 parameter. This enables one to supply own padding data. Border can also be specified by a border
 width separately for each direction/axis. In this case, each direction is extended by filling in
 constant value within the border.

 The border width in given dimension times 2 plus 1 must be exactly the size of the corresponding
 filter.

\param[in] d		const reference to the input image
\param[out] res		reference to the output image, the result
\param[in] f		the convolution filter
\param[in] b		the input image extension receipt

 The convolution algorithm itself is cache targeted. It tries to maximize cache efficiency by
 limiting the necessary number of cache-misses. This is realized by applying several
 convolution masks at parallel. On the other hand, the memory consumption is also taken into account
 which results in just sub-optimal solution to the minimum cache-misses constraint.

\b Example:
\verbatim
Image3d<GRAY8> in(argv[1]);	//input image
Image3d<GRAY8> out;		//output image
Image3d<float> res,in_f;	//temporary higher-precision images

struct Separable3dFilter<float> f;
f.xData=new float[5];		//fill in the convolution filter
f.xData[0]=1.0;
f.xData[1]=4.0;
f.xData[2]=7.0;
f.xData[3]=4.0;
f.xData[4]=1.0;
f.xLength=5;
f.xDiv=17.0;

f.yData=f.xData;
f.yDiv=17.0;
f.yLength=5;

f.zData=f.xData;
f.zDiv=17.0;
f.zLength=5;

GrayToFloat(in,in_f);
in.DisposeData();

struct BorderPadding<float> b;
PrepareZeroBoundaryForFilter<float>(f,b); //fill in the extension borders

//compute the convolution
int ret=SeparableConvolution<float>(in_f,res,f,b);
in_f.DisposeData();

f.DisposeData();		//possibly free filter memory
b.DisposeData();		//possibly free paddings memory

if (ret == 0) {
	//no error
	FloatToGrayNoWeight(res,out);
	res.DisposeData();

	out.SaveImage(argv[2],IMG_TIFF);	//2D
	out.SaveImage(argv[2],IMG_ICSv2);		//3D
} else {
	//some error, filter sizes? memory?
}

//filter memory is freed automatically due to its destructors
\endverbatim

 \note Only \c float and \c double versions of this template are available, since \c GRAY8 suffers from voxel value overflows.
 \author Vladimír Ulman (xulman@fi.muni.cz)
 \date 2007
*/
template <class VOXEL> I3D_ALGO_EXPORT
  int SeparableConvolution(Image3d<VOXEL> const &d,			//input
			Image3d<VOXEL> &res,				//output
			struct Separable3dFilter<VOXEL> const &f,	//filter to be used
			struct BorderPadding<VOXEL> const &b);		//extension receipt

/** @} */

/**
 * \ingroup if
 * \brief Full (naive) convolution of input image extended by given user constant.
 *
 * This function performs a very simple and straightforward convolution: for every voxel of the input image
 * it scans over all voxels in the kernel image resulting in the worst complexity convolution algorithm
 * available. It is desirable to use any other (better) solution, e.g. separable filtering or Fourier
 * transform, if available.
 *
 * In order to keep the size of the convolved image \e out, the input image \e in shall be extended prior
 * the convolution which squeezes the output image back to the size of the input image afterwards. The extension
 * is virtual meaning that no temporary copy of the input image is created. Instead, the value of the parameter
 * \e border is supplied to the convolution whenever a value of voxel outside the input image is required.
 *
 * The convolution algorithm in its current implementation requires that all kernel image sizes be odd,
 * e.q. (15,13,11) instead of (14,14,11).
 *
 * \param[in] in	float or double input image
 * \param[in] kern	convolution kernel image of the same voxel type
 * \param[out] out	convolved copy of input image of the same voxel type
 * \param[in] border	optionaly: voxel value with which input image is extended, default is zero
 *
 * \return
 * -  0 result returned correctly, no problem
 * - -1 when kernel image has wrong size
 * - -2 on memory allocation error
 *
 * \note This function may, and probably will, consume an great deal of time before the result is returned.
 * Perhaps one may like to use the progress reporting feature to make sure the function is really doing something.
 *
 * \note Only \c float and \c double versions of this function are available,
 * since \c GRAY8 suffers from voxel value overflows.
 *
 * \author Vladimír Ulman (xulman@fi.muni.cz)
 * \date 2009
 */

template <class VOXEL> I3D_ALGO_EXPORT
int NaiveConvolution(Image3d<VOXEL> const &in,				//input
		    Image3d<VOXEL> const &kern,				//kernel
		    Image3d<VOXEL> &out,				//output
		    const VOXEL border = 0);			//new border value

/** Apply a steerable filter based on the Hessian matrix eigendecomposition of a Gaussian-filtered floating-point input image. The filter assigns the dominant eigenvalue of the Hessian matrix to each grid point. */
template <class VOXEL> I3D_ALGO_EXPORT void HessianSteer(Image3d<VOXEL> &img, VOXEL sigma_x, VOXEL sigma_y, VOXEL sigma_z);

} //namespace i3d ends here

#endif // __FILTERS_H__
