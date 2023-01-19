/*
 * \file lut.h
 *
 * \brief implements look up table (LUT)
 * This file is based on an older HRCA_LUT code. New implementation allows working with intervals 
 * in input type (typical for int and float types). The HRCA_LUT class (see files hrca_lut.h and hrca_lut.cpp) was 
 * reimplemented using the following new LUT (more general) class.
 *
 * \author Pavel Matula (pam@fi.muni.cz) 
 * \date 2007
 */

#ifndef __LUT_H__
#define __LUT_H__

#include <limits>
#ifndef _MSC_VER
#include <math.h>
#endif
#include "basic.h"
#include "algo_export.h"

namespace i3d {
#define i3dASSERT(x) {if (!(x)) throw LibException("ASSERT FAILED: " #x); };

  /////////////////////////////////////////////////////////////////
  //                                                             //
  //                           LUT                               //
  //                                                             //
  /////////////////////////////////////////////////////////////////

/**
	\brief class implements operations with LUT for voxel types

	Look Up Table holds mapping of values between minimal (m) and maximal (M) value (input, ITYPE) 
	to another value (output, OTYPE). 
	
	LUT is implemented as an array of N values, where i-th value in the array (i = 0, ..., N-1) is an output value 
	for input values in interval (m + i * d - d/2, m + i * d  + d/2) of uniform length d = (M - m)/(N - 1)

	LUT should be initialized using Init() function.
*/
	template <class ITYPE, class OTYPE> class I3D_ALGO_EXPORT LUT {
	protected:
		long _lut_size;			///< size of LUT
		ITYPE _min_value;		///< minimal value
		ITYPE _max_value;		///< maximal value
		OTYPE *_lut;			///< LUT for conversion from ITYPE to OTYPE, size of LUT is _lut_size
	public:
		/** 
		\brief contructor creates empty LUT.

		use Init() function for initialisation.
		*/
		LUT():_lut_size(0), _min_value(0),  _max_value(0), _lut(NULL) {};

		/** 
		\brief copy constructor

		\param lut LUT to copy 
		*/
		LUT(const LUT &lut): _lut_size(lut._lut_size), 
			_min_value(lut._min_value), _max_value(lut._max_value) { 
			if (lut._lut_size) {
				_lut = new OTYPE[lut._lut_size];

				OTYPE *p1 = _lut;
				OTYPE *p2 = lut._lut;
				for ( ; p1 != _lut + _lut_size; ++p1, ++p2) 
					*p1 = *p2;
			} else {
				_lut = NULL;
			}
		}

		/** 
		\brief destructor
		*/
		~LUT() { if (_lut) delete [] _lut; };

		/** 
		\brief initialises LUT

		\param num_bins		length of LUT array (must be bigger then 1)
		\param min_value	minimal input value 
		\param max_value	maximal input value s
		*/
		void Init(long num_bins = long(std::numeric_limits<ITYPE>::max() - std::numeric_limits<ITYPE>::min() + 1), 
			ITYPE min_value = std::numeric_limits<ITYPE>::min(), 
			ITYPE max_value = std::numeric_limits<ITYPE>::max()) 
		{
			i3dASSERT(num_bins > 1);
			i3dASSERT(min_value < max_value);
			_min_value = min_value;
			_max_value = max_value;
			if (_lut) delete [] _lut;
			_lut = new OTYPE[num_bins];
			_lut_size = num_bins;
		}

		/**
		   \brief creates affine LUT

		   creates affine LUT, i.e. 
		   \verbatim
		   lut[i] = min_OTYPE				if (a * in[i] + b) <= min_OTYPE
		   lut[i] = max_OTYPE				if (a * in[i] + b) >= max_OTYPE
		   lut[i] = round(a * in[i] + b)	otherwise
		   \endverbatim
		   where min_OTYPE and max_OTYPE are the minimal and the maximal output values. 
		   These values are implicitly set to std::numeric_limits<OTYPE>::min() and 
		   std::numeric_limits<OTYPE>::max(). 
		   
		   Note: This function cannot be used for RGB images yet.

		   \param a
		   \param b
		   \param min
		   \param max
		*/
		void CreateAffine(double a, double b, OTYPE min = std::numeric_limits<OTYPE>::min(), OTYPE max = std::numeric_limits<OTYPE>::max());

		/**
			\brief linearly maps all input values to all output values
		*/
		void CreateIdentity() { CreateLinearMapping(_min_value, _max_value);};

		/**
		  \brief creates affine LUT for selecting 8 bits from 16-bit signal

		  Note: This function is implemented for ITYPE = i3d::GRAY16, OTYPE = i3d::GRAY8 only 

		  \param last index of the last selected bit, bits are indexed from 1. If last == 0 then zero mapping is created
        	*/
		void Select8Bits(int last);

		/**
		   \brief creates LUT for linear stretching

		   computes coefficients a and b for affine transformation so that 
		   the imin value is mapped to 0 and the omax is mapped to maximal value of OTYPE

		   \param imin
		   \param imax
		   \param omin
		   \param omax
		*/
		void CreateLinearMapping(ITYPE imin, ITYPE imax, OTYPE omin = std::numeric_limits<OTYPE>::min(), 
			              OTYPE omax = std::numeric_limits<OTYPE>::max());

		/**
		   \brief creates LUT for thresholding
		*/	
		void CreateThresholding(ITYPE min_threshold, ITYPE max_threshold = std::numeric_limits<ITYPE>::max(), 
			OTYPE min_value = std::numeric_limits<OTYPE>::min(), OTYPE max_value = std::numeric_limits<OTYPE>::max());


		/**
		   \brief creates LUT for gamma correction of values between imin and imax into values between omin and omax

		   \param imin
		   \param imax
		   \param gamma
		   \param omin
		   \param omax
		*/	
		void CreateGamma(ITYPE imin, ITYPE imax, float gamma, OTYPE omin, OTYPE omax);

		/**
		   \brief applies LUT on data

		   \param idata
		   \param odata
		   \param size size of data
		*/	
		void Apply(const ITYPE *idata, OTYPE *odata, long size) const;

		/**
		   \brief get LUT value for input value \e i

		   LUT should be initialized
		*/	
		inline OTYPE Get(ITYPE i) const { 
			i3dASSERT(_lut);
			i3dASSERT(i >= _min_value && i <= _max_value);
			return _lut[GetPos(i)]; 
		};

		/**
		   \brief set LUT value
		   LUT should be initialized
		*/	
		inline void Set(ITYPE i, const OTYPE &o) { i3dASSERT(_lut); _lut[GetPos(i)] = o; };

		OTYPE *begin() { return _lut; };
		OTYPE *end() { return _lut + _lut_size; };
		long size() { return _lut_size; };
		ITYPE max_elem() const { return _max_value; };

		protected:
		/**
		   \brief get position in LUT array

		   \param i input value between _min_value and _max_value
		   \return position in LUT array, i.e. integer in interval [0,_lut_size)
		*/	
		inline int GetPos(ITYPE i) const { 
			return int(round(double(i - _min_value) * (_lut_size - 1) / double(_max_value - _min_value))); 
		};

		/**
		   \brief get central input value for i-th position in LUT array

		   \param i position in LUT array in interval [0,_lut_size)
		   \return central input value 
		*/	
		inline ITYPE GetCenter(int i) const { 
			return _min_value + ITYPE((i * double(_max_value - _min_value)) / (_lut_size - 1)); 
		};

	};
}
#endif

