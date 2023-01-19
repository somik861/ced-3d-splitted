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
 * License along with this library; if not, write to the Freere
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
 
/** 
 * \file haralick.h
   \brief 2D and 3D Haralick texture features.

DESCRIPTION:

	This file contains functions for calculating 2D/3D Haralick features
	defined in the following papers:

	[1] Haralick, Robert M. Shanmugam, K. Dinstein, Its'Hak; 
	Textural Features for Image Classification; 
	IEEE Transactions on Systems, Man and Cybernetics; 
	Publication Date: Nov. 1973; Volume: 3, Issue: 6; On page(s): 610-621; 
	ISSN: 0018-9472
	
	[2] Tesaø, L., Smutek, D., Shimizu, A., and Kobatake, H. 
	3D extension of Haralick texture features for medical image analysis. 
	In Proceedings of the Fourth Conference 
	on IASTED international Conference: Signal Processing, Pattern Recognition, 
	and Applications (Innsbruck, Austria, February 14 - 16, 2007). R. Sablatnig 
	and O. Scherzer, Eds. ACTA Press, Anaheim, CA, 350-355.
	
   \author David Svoboda <svoboda@fi.muni.cz>
   \author Jana Matejkova <256364@mail.muni.cz>
	\date 2010


NOTE:
	An example of use of the class HaralickFeatures<> can be found in
	the file '../../examples/haralicktest.cc'.
  			
*/

#ifndef __HARALICK_H__
#define __HARALICK_H__

#ifdef __GNUG__
#  pragma interface
#endif

#include <valarray>
#include <limits>

#include "image3d.h"
#include "algo_export.h"

namespace i3d {

/****************************************************************************\
*
*                    Some important constants and datatypes
*
\****************************************************************************/

///	The pixel neighbourhood defined by Haralick in [1].
const Vector3d<int> Haralick2D_neighbourhood[] =
{
	Vector3d<int>( 1, 0, 0),
	Vector3d<int>( 0, 1, 0),
	Vector3d<int>(-1, 0, 0),
	Vector3d<int>( 0,-1, 0),
	Vector3d<int>( 1, 1, 0),
	Vector3d<int>(-1,-1, 0),
	Vector3d<int>( 1,-1, 0),
	Vector3d<int>(-1, 1, 0)
};

/// The pixel neighbourhood defined by Tesar in [2].
const Vector3d<int> Tesar3D_neighbourhood[] =
{
	 Vector3d<int>( 1, 0, 0),
	 Vector3d<int>(-1, 0, 0),
	 Vector3d<int>( 0, 1, 0),
	 Vector3d<int>( 0,-1, 0),
	 Vector3d<int>( 0, 0, 1),
	 Vector3d<int>( 0, 0,-1)
};

/// All the implemented Haralick texture features.
typedef enum I3D_ALGO_EXPORT 
{
	 Entropy,
	 TextureContrast,
	 TextureCorrelation,
	 TextureHomogeneity,
	 InverseDifferenceMoment,
	 MaximumProbability,
	 UniformityOfEnergy,
	 Contrast,
	 SumAverage,
	 SumEntropy,
	 DifferenceEntropy,
	 Variance,
	 InfMeasureOfCorrelationA,
	 InfMeasureOfCorrelationB,
	 MaximalCorrelationCoefficient
} ListOfHaralickFeatures;


/****************************************************************************\
*
*                     2D & 3D Haralick features
*
\****************************************************************************/

template <class T> class I3D_ALGO_EXPORT HaralickFeatures
{
		private: 
				  /// modified & re-sampled image
				  i3d::Image3d<T> analyzed_image;
				  
				  /// separation vector
				  const i3d::Vector3d<int> *separation_vectors;

				  /// number of separation vectors
				  size_t amount;

				  /// quantization level - expected number of color in the image
				  size_t quantization_level;

				  /// image range
				  bool use_full_bitdepth;

				  /// data storage for the matrix itself indexed cell[x][y]
				  typedef std::valarray<double> matrix_row;
				  std::valarray<matrix_row> *cooc_matrix; 
				  
				  /// \f$\mi_x\f$
				  double *mi_x; 

				  /// \f$\mi_y\f$
				  double *mi_y; 

				  /// \f$var_x\f$
				  double *var_x; 
				  
				  /// \f$var_y\f$
				  double *var_y; 
				  
				  /// line sum \f$c_x(i)\f$
				  double c_x(size_t order, size_t i) const; 
				  
				  /// line sum \f$c_y(j)\f$
				  double c_y(size_t order, size_t j) const; 
				  
				  /// \f$c_x_plus_y(k)\f$
				  double c_x_plus_y(size_t order, size_t k) const; 
				  
				  /// \f$c_x_minus_y(k)\f$
				  double c_x_minus_y(size_t order, size_t k) const;
				  
				  /// some Haralick specific variables
				  double *HXY, *HX, *HY, *HXY1, *HXY2; 
				  
				  /// method for verification of the input parameters
				  void TestInputs();

				  /// method for taking care of memory management
				  void MemoryAllocation();

				  /// method for preparing the image for further analysis
				  void ImagePreprocessing(const i3d::VOI<i3d::PIXELS> &);

				  /// method with some math routines included
				  void MathPreprocessing();

				  /// function for calculating statistics
				  void PrecalculateStatistics(size_t order); 
				  
				  /// function for creating/calculating cooccurrence matrix
				  void CreateCoocMatrix(size_t order, 
												const i3d::Image3d<T> &image);

				  /// hidden methods for giving the required Haralick feature
					double GetEntropy(size_t order) const;
					double GetTextureContrast(size_t order) const;
					double GetTextureCorrelation(size_t order) const;
					double GetTextureHomogeneity(size_t order) const;
					double GetInverseDifferenceMoment(size_t order) const;
					double GetMaximumProbability(size_t order) const;
					double GetUniformityOfEnergy(size_t order) const;
					double GetContrast(size_t order) const;
					double GetSumAverage(size_t order) const;
					double GetSumEntropy(size_t order) const;
					double GetDifferenceEntropy(size_t order) const;
					double GetVariance(size_t order) const;
					double GetInfMeasureOfCorrelationA(size_t order) const;
					double GetInfMeasureOfCorrelationB(size_t order) const;
					double GetMaximalCorrelationCoefficient(size_t order) const;


		public: 
				  /// constructor 
				  HaralickFeatures(
						const i3d::Image3d<T> &image,
						const i3d::Vector3d<int> &_separation_vector, 
						size_t _quantization_level = 0,
						const i3d::VOI<i3d::PIXELS> &_voi = 0,
						bool _use_full_bitdepth = false); 

				  // constructor
				  HaralickFeatures(
						const i3d::Image3d<T> &image,
						const i3d::Vector3d<int> *_separation_vectors, 
						size_t _amount,
						size_t _quantization_level = 0,
						const i3d::VOI<i3d::PIXELS> &_voi = 0,
						bool _use_full_bitdepth = false); 

				  /// destructor
				  ~HaralickFeatures();

				  /// method for printing the cooccurrence matrix/matrices
				  void ShowMatrices() const;

				  /// method for printing the separation vector(s)
				  void ShowSeparationVectors() const;

				  /// output method
				  double GetFeature(ListOfHaralickFeatures, size_t) const;

				  /// output method
				  double GetMeanFeature(ListOfHaralickFeatures) const;
};

}

#endif





