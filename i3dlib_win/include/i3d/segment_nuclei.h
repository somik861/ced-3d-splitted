/*
 * segment_nuclei.h
 *
 * Interface to segment_nuclei function
 *
 * Marek Vinkler (xvinkl@mail.muni.cz) 2009
 * 
 */

#ifndef __SEGMENT_NUCLEI_H__
#define __SEGMENT_NUCLEI_H__

#include "algo_export.h"
#include "image3d.h"

namespace i3d
{
	enum I3D_ALGO_EXPORT SNR_TreshType {Background, Median, Border};

	struct I3D_ALGO_EXPORT SNR_Params
	{
		double laplace_sigma;
		double gradmag_sigma;
		SNR_TreshType grad_thresh_type;
		size_t min_avg_gradmag;
		size_t min_fragment_size;
		size_t max_fragment_size;
		size_t min_cell_size;
		size_t closing_size;
		bool remove_faint_objects;
		bool merge_small_objects;
	};

	bool I3D_ALGO_EXPORT SegmentNuclei2d(const Image3d<i3d::GRAY16> &in, Image3d<i3d::GRAY16> &out, const SNR_Params &params);

} // namespace i3d

#endif // __SEGMENT_NUCLEI_H__

