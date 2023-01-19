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
 * FILE: threshold.h
 *
 * Thresholding of 3d image
 *
 * Petr Matula (pem@fi.muni.cz)
 * 
 */

#ifndef __THRESHOLD_H__
#define __THRESHOLD_H__

#ifdef __GNUG__
#pragma interface
#endif

#include <vector>
#include <iomanip>
#include <limits>

#include "image3d.h"
#include "histogram.h"

/**
 * \defgroup points Point based image transforms
 */

namespace i3d {
  
/***************************************************************************/
/**
 * \ingroup points
 *
 * Set intensities of voxels whose intensities are lower or equal to 
 * `t` to minimun. The rest ot htem is left unchanged. */
template < class VOXELIN, class VOXELOUT > 
  I3D_ALGO_EXPORT void SemiThreshold (const Image3d < VOXELIN > &imgin, Image3d < VOXELOUT > &imgout, VOXELIN t);

/***************************************************************************/
/** 
 * \ingroup points
 *
 * Set intensities of voxels whose intesities are >=t1 and <=t2 to maximum
   and the others to minimum of the voxel type */
template <class T> 
  I3D_ALGO_EXPORT void Threshold(Image3d<T> &i, T t1, T t2 = std::numeric_limits<T>::max(), 
	  T lower_value = std::numeric_limits<T>::min(), T upper_value = std::numeric_limits<T>::max());

/***************************************************************************/
/**
 * \ingroup points
 *
 * Thresholding with creation of a new image, possibly of other voxel
 * type.
 */
template <class VOXELIN, class VOXELOUT> 
  I3D_ALGO_EXPORT void Threshold(const Image3d<VOXELIN> &imgin, Image3d<VOXELOUT> &imgout, VOXELIN t1, VOXELIN t2 = std::numeric_limits<VOXELIN>::max());

/***************************************************************************/
/**
 * \ingroup points
 *
 * Thresholding with creation of a new image, possibly of other voxel type. 
 * The lower threshold is obtained using specified ThresholdFinder tf. The upper threshold is taken as the maximal value of the input image type.
 */
template <class VOXELIN, class VOXELOUT, class TF> 
  I3D_ALGO_EXPORT void Threshold(const Image3d<VOXELIN> &imgin, Image3d<VOXELOUT> &imgout, const TF &tf);

/***************************************************************************/
/** 
 * \ingroup hist
 *
 * HistFinder is class which provides a member function with prototype:  
      T find(const Image3d<T> &img, const VOI<PIXELS> &voi)
  
    this function is called in LocalThreshold function when a threshold for VOI in
    image have to be found. The reference to a ThresholdFinder is the last parameter
    of the LocalThreshold function.
	This function uses the member abstract function AnalyzeHist, whose implementation
	represents the method for finding the threshold from the histogram.
  */
 template <class T> class I3D_ALGO_EXPORT HistFinder
   {
   protected:
     /** represents the function used in member function HistFinder::find for histogram smoothing
      * smooth_diff == 0 -> without smoothing 
      * smooth_diff == 1 -> function SmoothHist(const Histogram &in, Histogram &out) is used 
      * smooth_diff > 1 -> function SmoothHist(const Histogram &in, Histogram &out, size_t diff) is used */
     size_t smooth_diff;
     
     bool ignore_max_column;   // if _ignore_max_column == true then the highest column (typically corresponds to zero background pixels, e.g. set by FISH2 online analysis) is ignored
     
   public:
     HistFinder(size_t _smooth_diff = 1, bool _ignore_max_column = false): 
       smooth_diff(_smooth_diff), ignore_max_column(_ignore_max_column) {};
     
     /** class method needed for searching for the threshold value 
      * the inputs are image 'img' and volume for interest 'voi'. For global
      * thresholding the 'voi' is equal to the whole image, while for local 
      * thresholding the 'voi' changes. */
     T find(const Image3d<T> &img, const VOI<UPIXELS> &voi) const;
	      
      /// destructor 
	  virtual ~HistFinder() {};

	private:
  	  virtual size_t AnalyzeHist(const Histogram &hist) const = 0;
   };
 
/***************************************************************************/
 /**
  * \ingroup hist
  */
 template <class T> class I3D_ALGO_EXPORT MaxPlusKDeltaFinder:public HistFinder<T>
   {
   private:
     double k;
     
   public:
     /// constructor - if _ignore_max_column == true then the highest column (typically corresponds to zero background pixels, e.g. set by FISH2 online analysis) is ignored
     MaxPlusKDeltaFinder(double _k = 0, size_t _smooth_dist = 1, 
			  					 bool _ignore_max_column = false): 
     HistFinder<T>(_smooth_dist, _ignore_max_column), k(_k) {};
     
   private:
     virtual size_t AnalyzeHist(const Histogram &hist) const;
  };

/***************************************************************************/
 /**
  * \ingroup hist
  */
template <class T> class I3D_ALGO_EXPORT UnimodalThresholdFinder:public HistFinder<T>
  { 
  public:
	  /// constructor - if _ignore_max_column == true then the highest column (typically corresponds to zero background pixels, e.g. set by FISH2 online analysis) is ignored
      UnimodalThresholdFinder(size_t _smooth_dist = 1, 
				bool _ignore_max_column = false): 
	    HistFinder<T>(_smooth_dist, _ignore_max_column) {};
   
  private:
    virtual size_t AnalyzeHist(const Histogram &hist) const;
  }; 
 
/***************************************************************************/
 /**
  * \ingroup hist
  */
template <class T> class I3D_ALGO_EXPORT OtsuThresholdFinder : 
	 public HistFinder<T>
   {
   public:
     /// constructor - if _ignore_max_column == true then the highest column (typically corresponds to zero background pixels, e.g. set by FISH2 online analysis) is ignored
     OtsuThresholdFinder(size_t _smooth_dist = 1, 
			  bool _ignore_max_column = false): 
		  HistFinder<T>(_smooth_dist, _ignore_max_column) {};
  
   private:
     virtual size_t AnalyzeHist(const Histogram &hist) const;
   }; 

/***************************************************************************/

/**
	computes optimal multilevel Otsu thresholds.

	\param hist			image histogram
	\param k			number of levels required (k >= 2)
	\param thresholds		the computed thresholds.
	
	Computed threshold contains indexes into image histogram hist.
	The length of the vector will be k - 1 and it defines k levels
	\verbatim
	#1:   0                     ... thresholds[0], 
	#2:   thresholds[0] + 1     ... thresholds[1], 
        ..., 
	#k-1: thresholds[k - 3] + 1 ... thresholds[k - 2],
	#k:   thresholds[k - 2] + 1 ... max image intensity
	\endverbatim

	\returns false if the number of imege levels is greater than k and true otherwise
*/

I3D_ALGO_EXPORT bool ComputeMultilevelOtsuThresholds(const Histogram &hist, size_t k, std::vector<int> &thresholds);

template <class VOXEL> I3D_ALGO_EXPORT void DoMultilevelThresholding(const Image3d<VOXEL> &img, Image3d<GRAY8> &imgout, 
																   const std::vector<int> &thresholds);

/***************************************************************************/
/** Set intensities of voxels whose intesities are >=t1 and <=t2 to maximum
   and the others to 0 */

I3D_ALGO_EXPORT void InitDivisionPoints
	  (std::vector<size_t> &div, size_t sz, size_t n);

/***************************************************************************/

I3D_ALGO_EXPORT void RecomputeDivisionPoints(std::vector<size_t> &div);

/***************************************************************************/
  /**
	* \ingroup points
	* 
    Perform local thresholding on image in and store its result to binary
    image out. The image is devided to nx*ny*nz subregions and a threshold
    is computed for each such subregion by the threshold finder (see above).
    An individual threshold for each voxel is computed from the computed
    thresholds by trilinear interpolation.
   */
template <class T, class OUTVOXEL, class TF> 
I3D_ALGO_EXPORT void LocalThreshold(const Image3d<T> &, Image3d<OUTVOXEL> &,
                      size_t nx, size_t ny, size_t nz,
                      const TF&);

/***************************************************************************/

/////////////////////////////////////////////////////////////////
//                                                             //
//                          GibouFedkiw                        //
//                                                             //
/////////////////////////////////////////////////////////////////

/** Weighted 2-means clustering based on the Gibou-Fedkiw algorithm intended for a fast minimization of the Chan-Vese model without the regularization term. The parameters fg_weight
  * and bg_weight specify the weight of fidelity terms of the Chan-Vese model. The function returns a bilevel image and the corresponding mean intensity levels. The iterative process
  * is repeated until the mean intensity levels change in two successive iterations or the maximum number of iterations is performed.
  *
  * Reference: F. Gibou and R. Fedkiw. A fast hybrid k-means level set algorithm for segmentation. In Proceedings of the 4th Annual Hawaii International 
  *            Conference on Statistics and Mathematics, 2005, pp. 281–291.
  */
template <class VOXELIN, class VOXELOUT, class PREC> 
	I3D_ALGO_EXPORT void GibouFedkiw(const Image3d<VOXELIN> &src, Image3d<VOXELOUT> &dst, PREC fg_weight, PREC bg_weight, PREC &fg_mean, PREC &bg_mean, size_t max_iter = 30);

} // namespace i3d

#endif // __THRESHOLD_H__
