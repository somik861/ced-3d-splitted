/* Author: Neko <^.^> */
/* If u find any bugs, please contact me on nekochan.3.1415926@gmail.com */

#ifndef __BILATERAL_H__
#define __BILATERAL_H__

#ifdef __GNUG__
#pragma interface
#endif

#include "image3d.h"
#include "algo_export.h"

namespace i3d {
   /** \ingroup if
   \brief Computes bilateraly filtered image using naive algorithm in single precision.

   Input image is filtered using convolution kernel of size derived from the spatial sigma, which means repacement of
   each pixel/voxel with weighted average of its neighborhood up to distance 3.0 * \c SSigma. For 2D input data this
   means quadratic time complexity depending on SSigma, for 3D this complexity raises by one order higher, to the cubic
   time complexity. One should thus consider using this function only for the small \c SSigma parameter values.

   There are two variants of this function avaiable: \c BilateralNaive_Simple() and \c BilateralNaive_Double(), which
   differ in precision of the resulting image.

   To ensure independance of data type and uniform behavior of the function for RSigma parameter, one should linearly
   map RSigma to the real intensity range, i.e: RSigma * (Max intensity - Min intensity), where RSigma should be
   in interval <0.0, 1.0>.

   \param[in,out] Image		output & reference to the filtered image
   \param[in] SSigma		sigma of the Gauss filter in spatial domain
   \param[in] RSigma		sigma of the Gauss filter in intensity (range) domain

   \note Execution of this function may take enormous amount of time depending on the spatial sigma parameter
   \note Specified input image will be overwritten with the filtered one

   \author Jaroslav Žilák
   \date 2013
   */
   template <class VOXEL> I3D_ALGO_EXPORT void BilateralNaive_Simple(Image3d<VOXEL> &Image, float SSigma, float RSigma);

   /** \ingroup if
   \brief Computes bilateraly filtered image using naive algorithm in double precision.

   Input image is filtered using convolution kernel of size derived from the spatial sigma, which means repacement of
   each pixel/voxel with weighted average of its neighborhood up to distance 3.0 * \c SSigma. For 2D input data this
   means quadratic time complexity depending on SSigma, for 3D this complexity raises by one order higher, to the cubic
   time complexity. One should thus consider using this function only for the small \c SSigma parameter values.

   There are two variants of this function avaiable: \c BilateralNaive_Simple() and \c BilateralNaive_Double(), which
   differ in precision of the resulting image.

   To ensure independance of data type and uniform behavior of the function for RSigma parameter, one should linearly
   map RSigma to the real intensity range, i.e: RSigma * (Max intensity - Min intensity), where RSigma should be
   in interval <0.0, 1.0>.

   \param[in,out] Image		output & reference to the filtered image
   \param[in] SSigma		sigma of the Gauss filter in spatial domain
   \param[in] RSigma		sigma of the Gauss filter in intensity (range) domain

   \note Execution of this function may take enormous amount of time depending on the spatial sigma parameter
   \note Specified input image will be overwritten with the filtered one

   \author Jaroslav Žilák
   \date 2013
   */
   template <class VOXEL> I3D_ALGO_EXPORT void BilateralNaive_Double(Image3d<VOXEL> &Image, double SSigma, double RSigma);

   /** \ingroup if
   \brief Computes approximation of the bilateraly filtered image using recursive algorithm, publicated by YANG Q.[2012] in single precision.

   Input image is filtered using two/three pairs of extensive & antiextensive passes depending on dimensionality of
   input data. In contrast to the original algorith this function does not use input image as reference for intensity weights
   computation through whole process of filtering. Instead, partial results of every midstep is used. This results in a
   slightly degraded result quality, but in return overall space complexity is reduced by 33%.

   To ensure independance of data type and uniform behavior of the function for RSigma parameter, one should linearly
   map RSigma to the real intensity range, i.e: RSigma * (Max intensity - Min intensity), where RSigma should be
   in interval <0.0, 1.0>.

   \param[in,out] Image		reference to the output & filtered image
   \param[in] SSigma		sigma of the Gauss filter in spatial domain
   \param[in] RSigma		sigma of the Gauss filter in intensity (range) domain

   \note Function implements version that supresses staircase artifacts, which significantly worsens PSNR ratio, but visualy improves quality.
   \note Specified input image will be overwritten with the filtered version

   \author Jaroslav Žilák
   \date 2013
   */
   template <class VOXEL> I3D_ALGO_EXPORT void BilateralRecursive_Simple(Image3d<VOXEL> &Image, float SSigma, float RSigma);

   /** \ingroup if
   \brief Computes approximation of the bilateraly filtered image using recursive algorithm, publicated by YANG Q.[2012] in double precision.

   Input image is filtered using two/three pairs of extensive & antiextensive passes depending on dimensionality of
   input data. In contrast to the original algorith this function does not use input image as reference for intensity weights
   computation through whole process of filtering. Instead, partial results of every midstep is used. This results in a
   slightly degraded result quality, but in return overall space complexity is reduced by 33%.

   To ensure independance of data type and uniform behavior of the function for RSigma parameter, one should linearly
   map RSigma to the real intensity range, i.e: RSigma * (Max intensity - Min intensity), where RSigma should be
   in interval <0.0, 1.0>.

   \param[in,out] Image		reference to the output & filtered image
   \param[in] SSigma		sigma of the Gauss filter in spatial domain
   \param[in] RSigma		sigma of the Gauss filter in intensity (range) domain

   \note Function implements version that supresses staircase artifacts, which significantly worsens PSNR ratio, but visualy improves quality.
   \note Specified input image will be overwritten with the filtered version

   \author Jaroslav Žilák
   \date 2013
   */
   template <class VOXEL> I3D_ALGO_EXPORT void BilateralRecursive_Double(Image3d<VOXEL> &Image, double SSigma, double RSigma);

   /** \ingroup if
   \brief Computes approximation of bilateraly filtered image using gaussian separation properties in single precision

   The filtering is split into two/three passes along each axis depending on input image dimensionality. Although time complexity of
   this method, compared to naive algoritm, is by one order lower, it still requires large amount of time to complete. Despite of
   this problem, it's still well usable for bilateral filtering of images with small \c RSigma parameter (0.075 * intensity range) 
   where PSNR > 40dB is required. For higher sigmas however, quality drops rapidly.

   To ensure independance of data type and uniform behavior of the function for RSigma parameter, one should linearly
   map RSigma to the real intensity range, i.e: RSigma * (Max intensity - Min intensity), where RSigma should be
   in interval <0.0, 1.0>.

   \param[in,out] Image		reference to the output & filtered image
   \param[in] SSigma		sigma of the Gauss filter in spatial domain
   \param[in] RSigma		sigma of the Gauss filter in intensity (range) domain

   \note Specified input image will be overwritten with the filtered version

   \author Jaroslav Žilák
   \date 2013
   */
   template <class VOXEL> I3D_ALGO_EXPORT void BilateralSeparation_Simple(Image3d<VOXEL> &Image, float SSigma, float RSigma);

   /** \ingroup if
   \brief Computes approximation of bilateraly filtered image using gaussian separation properties in double precision

   The filtering is split into two/three passes along each axis depending on input image dimensionality. Although time complexity of
   this method, compared to naive algoritm, is by one order lower, it still requires large amount of time to complete. Despite of
   this problem, it's still well usable for bilateral filtering of images with small \c RSigma parameter (0.075 * intensity range) 
   where PSNR > 40dB is required. For higher sigmas however, quality drops rapidly.

   To ensure independance of data type and uniform behavior of the function for RSigma parameter, one should linearly
   map RSigma to the real intensity range, i.e: RSigma * (Max intensity - Min intensity), where RSigma should be
   in interval <0.0, 1.0>.

   \param[in,out] Image		reference to the output & filtered image
   \param[in] SSigma		sigma of the Gauss filter in spatial domain
   \param[in] RSigma		sigma of the Gauss filter in intensity (range) domain

   \note Specified input image will be overwritten with the filtered version

   \author Jaroslav Žilák
   \date 2013
   */
   template <class VOXEL> I3D_ALGO_EXPORT void BilateralSeparation_Double(Image3d<VOXEL> &Image, double SSigma, double RSigma);

   /** \ingroup if
   \brief Computes approximation of bilateraly filtered image using bilateral grid (CHEN, J., PARIS, S., DURAND, F [2007]) in single precision

   Image filtration uses bilateral grid structure, which for small sigma parameters might easily exceed memory limits.
   More or less this constraint limits usability of this function to either small input data or less quality outputs.
   Algorithm is divided according publication into three steps:
   1.) grid creation, which basicly subsamples input data in both, spatial and intensity domain.
   Created bilateral grid is by one dimension larger than input data,
   2.) grid convolution, which uses ordinary gaussian blur,
   3.) output reconstruction by slicing, which is the counterpart to the grid creation.
   According authors of this method grid convolution should be performed using 5-tap kernel, which is however not clearly defined.
   In this implementation it's represented by the following kernel: [0.1, 3.6788, 10.0, 3.6788, 0.1], which has been experimentaly proven
   to be PSNR friendlier than any other commonly used 5-tap kernel.
   Furthermore, due to the fixed kernel size, this convolution was implemented in an optimal way in respect to the space complexity.
   More precisely, the required buffer size was reduced from full size of the grid to the size of only three pixels.

   To ensure independance of data type and uniform behavior of the function for RSigma parameter, one should linearly
   map RSigma to the real intensity range, i.e: RSigma * (Max intensity - Min intensity), where RSigma should be
   in interval <0.0, 1.0>.

   \param[in,out] Image		reference to the output & filtered image
   \param[in] SSigma		sigma of the Gauss filter in spatial domain
   \param[in] RSigma		sigma of the Gauss filter in intensity (range) domain

   \note Method is highly precise > 50dB for smaller sigmas
   \note Specified input image will be overwritten with the filtered version

   \author Jaroslav Žilák
   \date 2013
   */
   template <class VOXEL> I3D_ALGO_EXPORT void BilateralGrid_Simple(Image3d<VOXEL> &Image, float SSigma, float RSigma);

   /** \ingroup if
   \brief Computes approximation of bilateraly filtered image using bilateral grid (CHEN, J., PARIS, S., DURAND, F [2007]) in double precision

   Image filtration uses bilateral grid structure, which for small sigma parameters might easily exceed memory limits.
   More or less this constraint limits usability of this function to either small input data or less quality outputs.
   Algorithm is divided according publication into three steps:
   1.) grid creation, which basicly subsamples input data in both, spatial and intensity domain.
   Created bilateral grid is by one dimension larger than input data,
   2.) grid convolution, which uses ordinary gaussian blur,
   3.) output reconstruction by slicing, which is the counterpart to the grid creation.
   According authors of this method grid convolution should be performed using 5-tap kernel, which is however not clearly defined.
   In this implementation it's represented by the following kernel: [0.1, 3.6788, 10.0, 3.6788, 0.1], which has been experimentaly proven
   to be PSNR friendlier than any other commonly used 5-tap kernel.
   Furthermore, due to the fixed kernel size, this convolution was implemented in an optimal way in respect to the space complexity.
   More precisely, the required buffer size was reduced from full size of the grid to the size of only three pixels.

   To ensure independance of data type and uniform behavior of the function for RSigma parameter, one should linearly
   map RSigma to the real intensity range, i.e: RSigma * (Max intensity - Min intensity), where RSigma should be
   in interval <0.0, 1.0>.

   \param[in,out] Image		reference to the output & filtered image
   \param[in] SSigma		sigma of the Gauss filter in spatial domain
   \param[in] RSigma		sigma of the Gauss filter in intensity (range) domain

   \note Method is highly precise > 50dB for smaller sigmas
   \note Specified input image will be overwritten with the filtered version

   \author Jaroslav Žilák
   \date 2013
   */

   template <class VOXEL> I3D_ALGO_EXPORT void BilateralGrid_Double(Image3d<VOXEL> &Image, double SSigma, double RSigma);

   /** \ingroup if
   \brief Computes approximation of bilateraly filtered image using intensity slices called PBFIC (YANG, Q., TAN, K., AHUJA, N [2009]) in single precision

   Same as for bilateral grid, this method is also divided into three phases:
   1.) Selected image is split into intensity slices (pixel/voxel are extracted based on their intensity value).
   2.) This slices are then blurred using gaussian filter. This operation represents up to 95% of the whole filtering process time,
   which makes this step time critical. For this reason Deriche gaussian approximation is used.
   3.) In the last step the final result is lineary approximated using two neighboring slices.

   Quality of result, same as speed of this method is directly dependant on number of slices used (the more the better, but slower).

   To ensure independance of data type and uniform behavior of the function for RSigma parameter, one should linearly
   map RSigma to the real intensity range, i.e: RSigma * (Max intensity - Min intensity), where RSigma should be
   in interval <0.0, 1.0>.

   \param[in,out] Image		reference to the output & filtered image
   \param[in] SSigma		sigma of the Gauss filter in spatial domain
   \param[in] RSigma		sigma of the Gauss filter in intensity (range) domain
   \param[in] PBFICCount		number of PBFIC slices

   \note Specified input image will be overwritten with the filtered version

   \author Jaroslav Žilák
   \date 2013
   */
   template <class VOXEL> I3D_ALGO_EXPORT void BilateralPBFIC_Simple(Image3d<VOXEL> &Image, float SSigma, float RSigma, int PBFICCount = 8);

   /** \ingroup if
   \brief Computes approximation of bilateraly filtered image using intensity slices called PBFIC (YANG, Q., TAN, K., AHUJA, N [2009]) in double precision

   Same as for bilateral grid, this method is also divided into three phases:
   1.) Selected image is split into intensity slices (pixel/voxel are extracted based on their intensity value).
   2.) This slices are then blurred using gaussian filter. This operation represents up to 95% of the whole filtering process time,
   which makes this step time critical. For this reason Deriche gaussian approximation is used.
   3.) In the last step the final result is lineary approximated using two neighboring slices.

   Quality of result, same as speed of this method is directly dependant on number of slices used (the more the better, but slower).

   To ensure independance of data type and uniform behavior of the function for RSigma parameter, one should linearly
   map RSigma to the real intensity range, i.e: RSigma * (Max intensity - Min intensity), where RSigma should be
   in interval <0.0, 1.0>.

   \param[in,out] Image		reference to the output & filtered image
   \param[in] SSigma		sigma of the Gauss filter in spatial domain
   \param[in] RSigma		sigma of the Gauss filter in intensity (range) domain
   \param[in] PBFICCount		number of PBFIC slices

   \note Specified input image will be overwritten with the filtered version

   \author Jaroslav Žilák
   \date 2013
   */
   template <class VOXEL> I3D_ALGO_EXPORT void BilateralPBFIC_Double(Image3d<VOXEL> &Image, double SSigma, double RSigma, int PBFICCount = 8);

   /** \ingroup if
   \brief Computes approximation of gaussian filtered image using Deriche recursive algorithm (DERICHE, R. [1993]) in single precision

   Input data are filtered using two/three extensive and antiextensive passes depending on dimensionality.
   Method implements zeroth derivation of gaussian filter using second order recursive approximation.

   \param[in,out] Data		reference to the output & filtered data
   \param[in] XDim		width of input data
   \param[in] YDim		height of input data
   \param[in] ZDim		depth of input data
   \param[in] Sigma		sigma of the Gauss filter

   \note The first parameter can be of any kind of data.
   \note Specified input image will be overwritten with the filtered version

   \author Jaroslav Žilák
   \date 2013
   */
   template <typename ELEMENT> I3D_ALGO_EXPORT void BlurDeriche_Simple(ELEMENT *Data, int XDim, int YDim, int ZDim, float Sigma);

   /** \ingroup if
   \brief Computes approximation of gaussian filtered image using Deriche recursive algorithm (DERICHE, R. [1993]) in double precision

   Input data are filtered using two/three extensive and antiextensive passes depending on dimensionality.
   Method implements zeroth derivation of gaussian filter using second order recursive approximation.

   \param[in,out] Data		reference to the output & filtered data
   \param[in] XDim		width of input data
   \param[in] YDim		height of input data
   \param[in] ZDim		depth of input data
   \param[in] Sigma		sigma of the Gauss filter

   \note The first parameter can be of any kind of data.
   \note Specified input image will be overwritten with the filtered version

   \author Jaroslav Žilák
   \date 2013
   */
   template <typename ELEMENT> I3D_ALGO_EXPORT void BlurDeriche_Double(ELEMENT *Data, int XDim, int YDim, int ZDim, double Sigma);

}

#endif
