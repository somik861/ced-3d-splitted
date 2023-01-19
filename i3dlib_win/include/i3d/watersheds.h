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

/** \file watersheds.h
\brief Part of mathematical morphology routines - header.

This file provides various watershed transformation functions.
*/

#ifndef __WATERSHEDS_H__
#define __WATERSHEDS_H__

#ifdef __GNUG__
#	pragma interface
#endif

#include "image3d.h"
#include "neighbours.h"

namespace i3d
{
	/** \addtogroup morph */
	///@{

	/** Morphological Watershed. It uses Toboggan based approach implemented primarily by Lin et.al 
	and published in 
	"Comparison between immersion-based and toboggan-based watershed image segmentation"
	Yung-Chieh Lin; Yu-Pao Tsai; Yi-Ping Hung; Zen-Chung Shih, 
	IEEE Transactions on Image Processing, 15, 3, March 2006

	and altered for 3D by Martin Maska and Pavel Matula

	This algorithm sometimes produces thick watershed lines. The result of the algorithm itself is very close to the Vincent-Soille algorithm.

	\param in the input image
	\param out the output labelled image, -1 is marking the watershed line, regions are marked beginning at 1 (0 is not used for anything)
	\param connectivity is 4, 8, 6, 18, 26
	\param drawLines whether to draw watershed lines everywhere or just in the ambiguous cases
	*/
	template <class T> I3D_ALGO_EXPORT void WatershedToboggan(
		const Image3d<T> &in, 
		Image3d<int> &out,
		int connectivity,
		bool drawLines = false);

	/** Morphological Watershed. It uses Toboggan based approach implemented by Lin et.al 
	and published in 
	"Comparison between immersion-based and toboggan-based watershed image segmentation"
	Yung-Chieh Lin; Yu-Pao Tsai; Yi-Ping Hung; Zen-Chung Shih, 
	IEEE Transactions on Image Processing, 15, 3, March 2006

	It can be called for 2D images (NumSlices() is equal to 1). InternalException is raised otherwise.

	This algorithm sometimes produces thick watershed lines. The result of the algorithm itself is very close to the Vincent-Soille algorithm.

	\param in the input image
	\param out the output labelled image, -1 is marking the watershed line, regions are marked beginning at 1 (0 is not used for anything)
	\param connectivity is 4 or 8
	*/
	template <class T> I3D_ALGO_EXPORT void WatershedToboggan2D(
		const Image3d<T> &in, 
		Image3d<int> &out,
		int connectivity);

	/** Morphological Watershed. It uses Watershed function implemented primarily by Lin et.al 
	and published in 
	"Comparison between immersion-based and toboggan-based watershed image segmentation"
	Yung-Chieh Lin; Yu-Pao Tsai; Yi-Ping Hung; Zen-Chung Shih, 
	IEEE Transactions on Image Processing, 15, 3, March 2006

	and altered for 3D by Martin Maska.

	This algorithm sometimes produces thick watershed lines. The result of the algorithm itself is very close to the Vincent-Soille algorithm. Use WatershedToboggan to get the same results but in shorter time.

	\param in the input image
	\param out the output labelled image, -1 is marking the watershed line, regions are marked beginning at 1 (0 is not used for anything)
	\param connectivity is 4, 8, 6, 18, 26
	\param drawLines whether to draw watershed lines everywhere or just in the ambiguous cases
	*/
	template <class T> I3D_ALGO_EXPORT void WatershedLin(
		const Image3d<T> &in, 
		Image3d<int> &out,
		int connectivity,
		bool drawLines = false);

	/** Morphological Watershed. It uses Watershed function implemented by Lin et.al 
	and published in 
	"Comparison between immersion-based and toboggan-based watershed image segmentation"
	Yung-Chieh Lin; Yu-Pao Tsai; Yi-Ping Hung; Zen-Chung Shih, 
	IEEE Transactions on Image Processing, 15, 3, March 2006

	It can be called for 2D images (NumSlices() is equal to 1). InternalException is raised otherwise.

	Watershed lines are drawn only in the ambiguous cases. The result of the algorithm itself is very close to the Vincent-Soille algorithm. Use WatershedToboggan2D to get the same results but in shorter time.

	\param in the input image
	\param out the output labelled image, -1 is marking the watershed line, regions are marked beginning at 1 (0 is not used for anything)
	\param connectivity is 4 or 8
	*/
	template <class T> I3D_ALGO_EXPORT void WatershedLin2D(
		const Image3d<T> &in, 
		Image3d<int> &out,
		int connectivity);

	/** Morphological watershed algorithm according to Meyer. This algorithm produces thin watershed lines.
	\param input the input image
	\param marker the marker image used for the start of the region growing (non-zero values should be used for the markers, zero otherwise)
	\param output the output labelled image, 0 is marking the watershed line
	\param neighbourhood the neighbourhood used for the computation
	*/
	template <typename T> 
	I3D_ALGO_EXPORT void WatershedMeyer(const Image3d<T> &input, const Image3d<size_t> &marker, Image3d<size_t> &output, const Neighbourhood &neighbourhood);

	/** Morphological watershed algorithm according to Meyer. This algorithm produces thin watershed lines. This version uses all the regional minima as markers.
	\param input the input image
	\param output the output labelled image, 0 is marking the watershed line
	\param neighbourhood the neighbourhood used for the computation
	*/
	template <typename T> 
	I3D_ALGO_EXPORT void WatershedMeyer(const Image3d<T> &input, Image3d<size_t> &output, const Neighbourhood &neighbourhood);

	/** Morphological watershed algorithm according to Beucher. This algorithm produces completely unbiased results.
	Detailed description of the algorithm can be found in
	Serge Beucher, "Algorithmes sans biais de ligne de partage des eaux",
	Centre de Morphologie Mathématique Ecole des Mines de Paris 28 Février 2002 Révisé le 30 Avril 2004 © 2002-2004.
	\param input the input image (maximum value in the image should be lower than maximum type IN_TYPE value - largest plattau size)
	\param marker the marker image used for the start of the region growing (non-zero values should be used for the markers, zero otherwise, keep labels low if possible, maximum label value shoud be (maximum OUT_TYPE value - 1) / 2)
	\param output the output labelled image, 0 is marking the watershed line (or undecidable voxels, even when watershed lines are not drawn)
	\param neighbourhood the neighbourhood used for the computation
	\param drawWsLines whether to draw watershed lines or not (they are draw order-invariantly, this means they are one or two voxels thick); even when you set this parameter to false, there will be watershed lines in the udecidable voxels
	*/
	template <typename IN_TYPE, typename OUT_TYPE> 
	I3D_ALGO_EXPORT void WatershedBeucher(const Image3d<IN_TYPE> &input, const Image3d<OUT_TYPE> &marker, Image3d<OUT_TYPE> &output, const Neighbourhood &neighbourhood, bool drawWsLines = false);

	/** Morphological watershed algorithm according to Beucher. This algorithm produces completely unbiased results. This version uses all the regional minima as markers.
	Detailed description of the algorithm can be found in
	Serge Beucher, "Algorithmes sans biais de ligne de partage des eaux",
	Centre de Morphologie Mathématique Ecole des Mines de Paris 28 Février 2002 Révisé le 30 Avril 2004 © 2002-2004.
	\param input the input image (maximum value in the image should be lower than maximum type T value - largest plattau size)
	\param output the output labelled image, 0 is marking the watershed line (or undecidable voxels, even when watershed lines are not drawn)
	\param neighbourhood the neighbourhood used for the computation
	\param drawWsLines whether to draw watershed lines or not (they are draw order-invariantly, this means they are one or two voxels thick); even when you set this parameter to false, there will be watershed lines in the udecidable voxels
	*/
	template <typename T> 
	I3D_ALGO_EXPORT void WatershedBeucher(const Image3d<T> &input, Image3d<size_t> &output, const Neighbourhood &neighbourhood, bool drawWsLines = false);

	/** Implementation of the principle of dynamics of contours by Najman and Schmitt in
	Laurent Najman, Michel Schmitt, "Geodesic Saliency of Watershed Contours and Hierarchical Segmentation,"
	IEEE Transactions on Pattern Analysis and Machine Intelligence, 
	vol. 18, no. 12, pp. 1163-1173, December, 1996.
	For further information see also the related articles "Comments on "Geodesic Saliency of Watershed Contours and Hierarchical Segmentation"" and "Response to comment on "Geodesic Saliency of Watershed Contours and Hierarchical Segmentation""
	\param input the input image
	\param labels the labeled image (result of the watershed transformation that is expected to have labels beginning from 1 and special label 0 marking the watershed lines (that are expected to be 1 voxel thick))
	\param saliencyMap the output image
	\param neighbourhood the neighbourhood used for the computation
	*/
	template <typename T>
	I3D_ALGO_EXPORT void WatershedContourDynamics(const Image3d<T> &input, const Image3d<size_t> &labels, Image3d<T> &saliencyMap, const Neighbourhood &neighbourhood);

	/** Implementation of the topological watershed transform described in 
	Michael Couprie, Laurent Najman, Gilles Bertrand, "Quasi-linear algorithms for the topological watershed,"
	Journal of Mathematical Imaging and Vision, 
	Volume 22, Numbers 2-3 / May, 2005.
	\param input the input image
	\param output the output image (non-minima of the image are the watershed lines)
	\param neighbourhood the neighbourhood used for the computation
	\param justMWS whether to compute only the M-watershed, or both M-watershed and W-watershed
	\param labels topological watershed can also return labeled image - if you wish one, use this parameter (specify non-null pointer to a labeled output image)
	*/
	template <typename T>
	I3D_ALGO_EXPORT void WatershedTopological(const Image3d<T> &input, Image3d<T> &output, const Neighbourhood &neighbourhood, bool justMWS = false, Image3d<size_t> *labels = NULL);

	///@} end of morph group part

} // namespace i3d

#endif // #ifndef __WATERSHEDS_H__
