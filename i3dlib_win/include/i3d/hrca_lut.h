/*
 * \file hrca_lut.h
 *
 * \brief implements look up table (LUT) for unsigned types
 *
 * \author Pavel Matula (pam@fi.muni.cz) 
 * \date 2006, 2007
 */

#ifndef __HRCA_LUT_H__
#define __HRCA_LUT_H__

#include <limits>
#include "lut.h"
#include "hrca_histogram.h"
//#include <string>
//#include <image3d.h>

namespace i3d {

  /////////////////////////////////////////////////////////////////
  //                                                             //
  //                           LUT                               //
  //                                                             //
  /////////////////////////////////////////////////////////////////

/**
	\brief class implements operations with LUT for unsigned numerical types (unsigned char and unsigned short)
*/
	template <class ITYPE, class OTYPE> class I3D_ALGO_EXPORT HRCA_LUT: public LUT<ITYPE, OTYPE> {
	public:
		HRCA_LUT():LUT<ITYPE, OTYPE>() { this -> Init(std::numeric_limits<ITYPE>::max() + 1, std::numeric_limits<ITYPE>::min(), std::numeric_limits<ITYPE>::max()); };
		HRCA_LUT(const HRCA_LUT &lut): LUT<ITYPE, OTYPE>(lut) {};
		
		/**
		   \brief creates LUT for linear stretching

		   computes coefficients a and b for affine transformation so that 
		   the lowest value of input histogram is mapped to 0 and the highest value 
		   is mapped to maximal value of OTYPE

		   \param histogram histogram of ITYPE values, size of histogram is numeric_limits<ITYPE>::max()
		*/
		void CreateLinearStretch(const HRCA_Histogram<ITYPE> &histogram);

		/**
		   \brief creates LUT for percentile stretching, 

		   same as linear stretch but certain amount of leftmost and rightmost histogram values is lost.
		   you get linear stretching for lp = rp = 0;

		   \param histogram histogram of ITYPE values, size of histogram is numeric_limits<ITYPE>::max()
		   \param lp values below this percentil are lost
		   \param rp values beyond this percentil are lost
		*/
		void CreatePercentileStretch(const HRCA_Histogram<ITYPE> &histogram, int lp, int rp);
		
		/**
		   \brief creates LUT for histogram equalization

		   \param histogram histogram of ITYPE values, size of histogram is numeric_limits<ITYPE>::max()

		   NOT IMPLEMENTED
		*/	
		void CreateEqualization(const HRCA_Histogram<ITYPE> &histogram);

		/**
		   \brief creates LUT for gamma correction

		   \param histogram 
		   \param gamma

		   NOT IMPLEMENTED
		*/	
		void CreateGamma(const HRCA_Histogram<ITYPE> &histogram, float gamma);

		using LUT<ITYPE, OTYPE>::CreateAffine;
	};
}
#endif

