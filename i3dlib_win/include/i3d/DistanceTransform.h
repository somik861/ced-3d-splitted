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

/** \file DistanceTransform.h
  \brief Distance transform routines - header.

  This file is intended for functions that compute distance transforms
  of 2D or 3D images.
  
  \author Jan Havelka <60609@mail.muni.cz> 2005
  
*/

#ifndef __DISTANCE_TRANSFORM_H__
#define __DISTANCE_TRANSFORM_H__

#include "image3d.h"
#include "algo_export.h"

namespace i3d {
	/** \defgroup transforms Image transforms */
	///@{
	/***************************************************************************\
	*
	*                     City-block distance transforms          
	*
	\***************************************************************************/
	/** This function computes City-block distance transform for 2D or 3D images. 
	\todo better documentation. */
	template <typename T> I3D_ALGO_EXPORT void CityBlock(Image3d<T> &Obraz, T Image_background = 0);

	/***************************************************************************\
	*
	*                     Chamfer distance transforms          
	*
	\***************************************************************************/
	/** This function computes Chamfer distance transform for 2D or 3D images.
	\todo better documentation. */
	template <typename T> I3D_ALGO_EXPORT void Chamfer(Image3d<T> &Obraz, T Image_background = 0);

	/***************************************************************************\
	*
	*                     Euclidean distance transforms          
	*
	\***************************************************************************/
	/** \brief Computes the distance transform for binary images.

	This function computes Euclidean distance transform.
	This function is established on Danielsson's algorithms for 2D images and Corner EDM for 3D images.

	The parameters are:
	\arg \c Image3d<T>& \c Obraz - reference to input image from which is the distance transform computed 
	and the result is saved to. The value of T should be float or double.
	\arg \c byte \c kvalita - This parameter determines what kind of neighbour is supposed to be used.  
	For value 0 is used 4-neighbour (for 2D images) and 6-neighbour (for 3D images). 
	For value != 0 is used 8-neighbour (for 2D images) and 26-neighbour (for 3D images).
	\arg \c T \c Image_background - This parametr determines what kind of color is used for image background.
	\arg \c bool \c odmocnina - This parameter determines if the result is supposed to be extracted the root.

	The implementation of this function is based on articles <br>
	Per-Erik Danielsson, <em> Euclidean Distance Mapping </em>, Departmnet of Electrical Engineering, Linkoping University 1980.
	Ingemar Ragnemalm, <em> The Euclidean distance transform in arbitrary dimensions </em>, Image Processing Group. Dept. of EE, Linkoping University 1992

	\author Jan Havelka 60609@mail.muni.cz
	\date 28. 11. 2005
	*/
	template <typename T> I3D_ALGO_EXPORT void EDM(
		Image3d<T> &Obraz, 
		byte kvalita = 0,
		T Image_background = 0, 
		bool odmocnina = false);

	/** \brief Computes the distance transform for binary images.

	This function computes Euclidean distance transform.
	This functiom combines Danielsson's algorithms(4SED or 8SED) and Saito's algoritm. Danielsson's algorithm
	is used for 2D images and for 3D images is used 4SED (or 8SED) for each slice and then is used the third 
	step of Saito's algorithm.

	The parameters are:
	\arg \c Image3d<T>& \c Obraz - reference to input image from which is the distance transform computed 
	and the result is saved to. The value of T should be float or double.
	\arg \c byte \c kvalita - This parameter determines what kind of neighbour is supposed to be used.  
	For value 0 is used 4-neighbour and for value != 0 is used 8-neighbour.
	\arg \c T \c Image_background - This parametr determines what kind of color is used for image background.
	\arg \c bool \c odmocnina - This parameter determines if the result is supposed to be extracted the root.

	The implementation of this function is based on article <br>
	Oliver Cuisenaire, <em> Distance transformations: Fast algoritms and applications to medical image processing </em>, 1999

	\author Jan Havelka 60609@mail.muni.cz
	\date 28. 11. 2005
	*/
	template<typename T> I3D_ALGO_EXPORT void HybridSaito(
		Image3d<T> &Obraz, 
		byte kvalita = 0,
		T Image_background = 0, 
		bool odmocnina = false);

	/** \brief Computes the distance transform for binary images.

	This function cumputes Euclidean distance transform.
	This function is implemantation of version 3 of Saito's algorithm that is presented in Saito's article.

	The parameters are:
	\arg \c Image3d<T>& \c Obraz - reference to input image from which is the distance transform computed
	and the result is saved to. The value of T should be float or double.
	\arg \c T \c Image_background - This parametr determines what kind of color is used for image background.
	\arg \c bool \c odmocnina - This parameter determines if the result is supposed to be extracted the root.

	The implementation of this function is based on article <br>
	Toyofumi Saito and Jun-Ichiro Toriwaki, <em> New algoritms for euclidean distance transformation of an n-dimensional digitized picture with applications </em>, Department of Informatin Engineering, Faculty of Engineering, Nagoya University 1994

	\author Jan Havelka 60609@mail.muni.cz
	\date 28. 11. 2005
	*/
	template <typename T> I3D_ALGO_EXPORT void SlowSaito(
		Image3d<T> &Obraz,
		T Image_background = 0, 
		bool odmocnina = false);

	/** \brief Computes the distance transform for binary images.

	This function cumputes Euclidean distance transform.
	This function is implemantation of fast version of Saito's algorithm that is presented in Saito's article.

	The parameters are:
	\arg \c Image3d<T>& \c Obraz - reference to input image from which is the distance transform computed 
	and the result is saved to. The value of T should be float or double.
	\arg \c T \c Image_background - This parametr determines what kind of color is used for image background.
	\arg \c bool \c odmocnina - This parameter determines if the result is supposed to be extracted the root.

	The implementation of this function is based on article <br>
	Toyofumi Saito and Jun-Ichiro Toriwaki, <em> New algorithms for euclidean distance transformation of an n-dimensional digitized picture with applications </em>, Department of Informatin Engineering, Faculty of Engineering, Nagoya University 1994

	\author Jan Havelka 60609@mail.muni.cz
	\date 28. 11. 2005
	*/
	template <typename T> I3D_ALGO_EXPORT void FastSaito(
		Image3d<T> &Obraz,
		T Image_background = 0, 
		bool odmocnina = false);

	/***************************************************************************\
	*
	*                     D-Euclidean distance transforms          
	*
	\***************************************************************************/
	/** This function computes D-Euclidean distance transform for 2D or 3D images.
	\todo better documentation. */
	template <typename T> I3D_ALGO_EXPORT void DeuclideanDistance(
		Image3d<T> &Obraz,
		byte kvalita = 0,
		T Image_background = 0,
		bool odmocnina = false);

	///@} end of transforms group

} // i3d namespace

#endif
