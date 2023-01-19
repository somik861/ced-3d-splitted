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
 * FILE: histogram.h
 *
 * histogram manipulation
 *
 * Petr Matula (pem@fi.muni.cz) 2001
 * Petr Mejzlík (mejzlik@fi.muni.cz) 2002
 */

#ifndef __HISTOGRAM_H__
#define __HISTOGRAM_H__

#ifdef __GNUG__
#pragma interface
#endif

#include <valarray>
#include <vector>
#include <algorithm>
#include "algo_export.h"
#include "image3d.h"


/**
 * \defgroup hist Histogram manipulation
 */

namespace i3d {

/// Histogram definition
typedef std::valarray<unsigned long> Histogram;

/// Histogram shape description
struct I3D_ALGO_EXPORT HistInfo 
{ 
  size_t mean1;
  size_t stdDev1;
  size_t mean2;
  size_t stdDev2;
  size_t threshold;

  HistInfo() : mean1(0), stdDev1(0), mean2(0), stdDev2(0), threshold(0) {}
};

/** Computes intensity histogram of image img. Output is stored to the
 * vector hist*/
template <class T> I3D_ALGO_EXPORT 
void IntensityHist(const Image3d<T> &img, Histogram &hist);

/** Computes intensity histogram of image img in a region specified by mask. It is assumed that the 
	image sizes are same. Pixels where the mask has given value are processed.
	Output is stored to the vector hist
	*/
template <class T, class MT> I3D_ALGO_EXPORT 
void IntensityHist(const Image3d<T> &img, Histogram &hist, const Image3d<MT> &mask);

/** 
 * \ingroup hist
 *
 * Computes histogram from RGB image. 
 * \p channel specifies for which channels the histogram is computed
 * (0 = red, 1 = green, 2 = blue) 
 **/
I3D_ALGO_EXPORT 
void IntensityHist(const Image3d<RGB> &img, Histogram &hist, int channel);

/*I3D_ALGO_EXPORT 
void IntensityHist(const Image3d<float> &img, Histogram &hist);*/

I3D_ALGO_EXPORT 
void IntensityHist(const Image3d<float> &img, 
		Histogram &hist, 
		size_t NumberOfBins = (size_t) std::numeric_limits<GRAY8>::max() + 1, 
		size_t SizeOfStep = 1);

/*I3D_ALGO_EXPORT 
void IntensityHist(const Image3d<double> &img, Histogram &hist);*/

I3D_ALGO_EXPORT 
void IntensityHist(const Image3d<double> &img, 
		Histogram &hist, 
		size_t NumberOfBins = (size_t) std::numeric_limits<GRAY8>::max() + 1, 
		size_t SizeOfStep = 1);

/** 
 * \ingroup hist
 *
 * Computes intensity histogram from voxels of image image img 
 * specified by gslice. Output is stored to the vector hist 
 */
template <class T> I3D_ALGO_EXPORT 
void IntensityHist(const Image3d<T> &img, Histogram &hist, 
		const std::gslice &slc);

I3D_ALGO_EXPORT 
void IntensityHist(const Image3d<float> &img, Histogram &hist, 
		const std::gslice &slc);

I3D_ALGO_EXPORT 
void IntensityHist(const Image3d<double> &img, Histogram &hist, 
		const std::gslice &slc);

I3D_ALGO_EXPORT 
void IntensityHist(const Image3d<Vector3d<float> > &img, Histogram &hist, 
		const std::gslice &slc);

I3D_ALGO_EXPORT 
void IntensityHist(const Image3d<Vector3d<double> > &img, Histogram &hist, 
		const std::gslice &slc);

/** 
 * \ingroup hist
 *
 * Compute histogram description. threshold is shifted according to 
 * the thres_factor value. 
 */
I3D_ALGO_EXPORT 
void ComputeHistInfo(const Histogram &hist, HistInfo &hi, double thres_factor);
 
/**
 *
 * \ingroup hist
 */
void ClearHist(Histogram &hist);

/**
 * \ingroup hist
 * out[i] = (in[i-1]+in[i]+in[i+1])/3
 */
I3D_ALGO_EXPORT 
void SmoothHist(const Histogram &in, Histogram &out);

/**
 * \ingroup hist
 * meaning: out[i] = (in[i-diff]+ ... +in[i+diff])/(2*diff+1)
 */
I3D_ALGO_EXPORT 
void SmoothHist(const Histogram &in, Histogram &out, size_t diff);

/**
 * \ingroup hist
 * Perform histogram equalization:
 * out[i] = floor ( (in.size()-1)/in.sum() * sum_j_goes_0_till_i (in[j]) )
 */
I3D_ALGO_EXPORT
void EqualizeHist(const Histogram &in, Histogram &out);

/**
 * \ingroup hist
 * Perform histogram equalization on the image. It modifies
 * the new image from the original input one such that for their
 * histograms it holds:
 * out[i] = floor ( (in.size()-1)/in.sum() * sum_j_goes_0_till_i (in[j]) )
 */
template <class VOXEL> I3D_ALGO_EXPORT
void EqualizeHist(const Image3d<VOXEL> &inImg, Image3d<VOXEL> &outImg);

/**
 * \ingroup hist
 * Perform histogram equalization on the image. It modifies
 * the new image from the original input one such that for their
 * histograms it holds:
 * out[i] = floor ( (in.size()-1)/in.sum() * sum_j_goes_0_till_i (in[j]) )
 *
 * The number of bins used is the default value
 * used in the function IntensityHist<float>().
 */
I3D_ALGO_EXPORT
void EqualizeHist(const Image3d<float> &inImg, Image3d<float> &outImg,
		size_t NumberOfBins = (size_t) std::numeric_limits<GRAY8>::max() + 1, 
		size_t SizeOfStep = 1);

/**
 * \ingroup hist
 * create cumulative histogram. \return total sum of the input histogram
 */
I3D_ALGO_EXPORT 
unsigned long CumulativeHistogram(const Histogram &in, Histogram &out);
/**
 * \ingroup hist 
 * returns the index of the maximum element in the input histogram \e h
 */
inline size_t HistMax(const Histogram &h) 
{ 
    Histogram &hh = const_cast<Histogram &>(h);
    return std::max_element(&hh[0], &hh[hh.size()]) - &hh[0];
}

/**
 * \ingroup hist
 * returns the index of the minimum element in the input histogram \e h
 */
inline size_t HistMin(const Histogram &h) 
{ 
    Histogram &hh = const_cast<Histogram &>(h);
    return std::min_element(&hh[0], &hh[hh.size()]) - &hh[0];
}

/**
 \ingroup hist 

 returns the index of \e k-percentile element in the input histogram \e h;
 \e k-percentile element is the element for which \e k-percent of elements has lower value

 param \e k must be between 0 and 100
 */
inline int HistPercentil(const Histogram &h, float k)
{
	size_t hist_sum = h.sum();
	float part_sum = 0.0;
	int i = 0;

	while (part_sum < hist_sum * k / 100.0) {
		part_sum += h[i]; ++i; 
	}
	return i;
}

/**
 * \ingroup hist
 * returns index of first non-zero element
 */
inline size_t HistFirstNonZero(const Histogram &h) 
{
    size_t i = 0;
    for (; i < h.size(); i++)
      if (h[i] != 0)
	break;
    if (i == h.size())
      throw InternalException("There is not non-zero element in histogram.");
    return i;
}


/**
 * \ingroup hist
 * returns index of last non-zero element
 */
inline size_t HistLastNonZero(const Histogram &h) 
{
    size_t i = h.size();
    for (; i > 0 ; --i)
      if (h[i - 1] != 0)
	break;
    if (i == 0)
      throw InternalException("There is not non-zero element in histogram."); 
    return i - 1;
}



/**
 * \ingroup hist
 */
I3D_ALGO_EXPORT void DiffHist(const Histogram &in, Histogram &out);

/**
 * \ingroup hist
 */
I3D_ALGO_EXPORT void DynMax(const Histogram &in, Histogram &out);

/**
 * \ingroup hist
 *
 * Create intensity mapping for intesity range improvement 
 * according to histogram.
 * Let max_pos be the position of the histogram maximum 
 * Let last be the position of the first zero intesity from max_pos to the right
 * Then 
 * - all intesities < max_pos + thres (= first) are set to zero
 * - all intesities > last are set to h.size()
 * - and every other intesity i is set to ((i-first)*h.size())/(last-first)
 * It's suggested to used smoothed histograms as an input */
template <class T> I3D_ALGO_EXPORT 
void MapLevels(const Histogram &h, std::vector<T> &map_func, int thres = 0);
 
/** 
 * \ingroup hist
 *
 * Create intensity mapping for intesity range improvement 
 * according to histogram.
 * 
 * - all intesities < left  are set to zero
 * - all intesities > right are set to h.size()
 * - and every other intesity i is set to ((i-left)*h.size())/(right-left)
 * left and right are limits found in histogram: sum(0..left) contains perm 
 per miles of intensity levels, sum(left,right) contains 1000 - 2*perm per 
 miles of intensity levels, sum(right,h.size()) ... perm*/
template <class T> I3D_ALGO_EXPORT 
void MapPermileLevels(const Histogram &h, std::vector<T> &map_func, 
		int perm = 5);
 
/** 
 * \ingroup hist
 * 
 * Reconstruction of mask 1D signal from marker 1D signal out by dilation
 * mask and out must have the same size and
 * for all i the condition: mask[i] >= out[i] must be satisfied
 * output is in written to out and the condition will hold*/
I3D_ALGO_EXPORT void RecDilHist(const Histogram &mask, Histogram &out);

/** 
 * \ingroup hist
 *
 * Reconstruction of mask 1D signal from marker 1D signal out by erosion
 * mask and out must have the same size and
 * for all i the condition: mask[i] <= out[i] must be satisfied
 * output is in written to out and the condition will hold*/
I3D_ALGO_EXPORT void RecEroHist(const Histogram &mask, Histogram &out);
  
/** 
 * \ingroup hist
 *
 * find regional maxima
 * in is input histogram, As a result
 * out[i] == 1 if i is regional maximum
 * out[i] == 0 otherwise */
inline void RegMaxHist(const Histogram &in, Histogram &out)
  {
    // RMAX=f-Rf(f-1) [Soille 1999, p.169]
    out.resize(in.size());
    out = in - (unsigned long)1;
    RecDilHist(in,out);
    out = in - out;
  }

/** 
 * \ingroup hist
 *
 * unimodal threshold finder
 */
I3D_ALGO_EXPORT size_t FindUnimodalThreshold (const Histogram & hist);

/** 
 * \ingroup hist
 * 
 * Otsu threshold finder - buggy version
 */
I3D_ALGO_EXPORT size_t OldFindOtsuThreshold (const Histogram & hist);

/** 
 * \ingroup hist
 * 
 * Otsu threshold finder 
 */
I3D_ALGO_EXPORT size_t FindOtsuThreshold(const Histogram &hist);

/** 
 * \ingroup hist
 * 
 * ISODATA threshold finder (Ridler and Calvard, 1978)
 * I haven't got the original article, but several implementations I saw used
 * mean intensity as the initial value. Setting init_thr_type to 1 allows
 * this. Some other implementations used central intensity from the range of
 * used intensities. Setting init_thr_type to 2 allows this. Leaving 
 * init_thr_type to be default 0 causes initial threshold to be set to the
 * central intensity from all the possible intensities, no matter which are
 * really preseint in the histogram.
 * Algorithmconverges differently in each case so play, children :)
 */
I3D_ALGO_EXPORT size_t FindIsoDataThreshold (const Histogram & hist,
										   int init_thr_type = 0);

}
#endif
