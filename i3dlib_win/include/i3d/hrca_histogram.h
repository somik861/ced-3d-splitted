/**
 * \file hrca_histogram.h
 * \brief histogram class
 * \author Pavel Matula (pam@fi.muni.cz) 
 * \date 2006
 */

#ifndef __HRCA_HISTOGRAM_H__
#define __HRCA_HISTOGRAM_H__

#include <limits>
#include "algo_export.h"

namespace i3d {

  /////////////////////////////////////////////////////////////////
  //                                                             //
  //                        Histogram                            //
  //                                                             //
  /////////////////////////////////////////////////////////////////
  /** 
  \brief Histogram class
  */
  template <class T> class I3D_ALGO_EXPORT HRCA_Histogram {
  protected:
	long *_hist;			///< histogram
	const long _size;		///< size of histogram
	long _max_peak;			///< maximal value in histogram
	long _max_idx;			///< index of maximal value
	long _suma;				///< histogram suma
	/** 
	\brief update \a _max_peak and \a _max_idx using i-th histogram value 
	*/
	void ComputeMax(long i) { if (_hist[i] > _max_peak) {_max_peak = _hist[i]; _max_idx = i;}};
  public:
    /** 
	\brief Constructor. 
	It creates an instance of the canvas and initialize all its attributes on its defaults.  
	*/
	  HRCA_Histogram():_size(std::numeric_limits<T>::max()+1), _max_peak(0), _max_idx(0), _suma(0) {
		  _hist = new long [_size]; Clear();
	  };

    /** 
	\brief Destructor.  
	*/
    ~HRCA_Histogram() { if (_hist) delete [] _hist; };

	/**
	\brief clears histogram
	*/
	void Clear() {memset(_hist, 0, _size*sizeof(long)); _max_peak = 0; _max_idx = 0; _suma = 0; };

	/** 
	\brief increments the frequency of i-th value by one.
	\param i 
	*/
	void Add(T i) { ++_hist[i]; ++_suma; ComputeMax(i); };

	/** 
	\brief computes data histogram
	\param data  
	\param n data length
	*/
	void Compute(const T *data, long n);

	/** 
	\brief sets the frequency of i-th value to given value.
	\param i value
	\param n frequency
	*/
	void Set(long i, long n) { _suma += n - _hist[i]; _hist[i] = n; ComputeMax(i);};

	long GetMax() const { return _max_peak; };
	long GetMaxID() const { return _max_idx; };

	/*void Compute(const T* data, long size) { Clear(); for(long i = 0; i < size; ++i) {Add(*data++); } }; */
	
	/** 
	\brief return index of certain percentil in histogram 
	\param percent percentil (value from 0 to 100) for 0 you get index of the first nonzero value.
	\return index (i.e. intenzity)
	*/
	long GetLeftPercentilID(int percent) const;
	long GetRightPercentilID(int percent) const;	
  };

} // namespace hrca
#endif

