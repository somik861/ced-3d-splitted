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

/** \file morphology.h
  \brief Mathematical morphology routines - header.

  This file provides mathematical morphology functions.
  \todo

  \author Martin Vach 2001 (xvach@fi.muni.cz)
  \author Petr Matula 2001 (pem@fi.muni.cz) - some updates
  \author Michal Kozubek, Petr Mejzlík 2001 (mejzlik@fi.muni.cz) - binary
  image operations
  \author Pavel Matula 2005 (pam@fi.muni.cz)- h_Max, r_Max, and e_Max functions

*/

#ifndef __MORPHOLOGY_H__
#define __MORPHOLOGY_H__

#ifdef __GNUG__
#	pragma interface
#endif

#include "image3d.h"
#include "neighbours.h"
#include "watersheds.h"

namespace i3d {
	/** \defgroup morph Mathematical morphology
	\todo Improve documentation
	*/
	///@{
	/**************************************************************************\
	*
	*                   Mathematical morphology routines
	*
	\**************************************************************************/
	/** Morphologial Dilation. */
	template <class T> I3D_ALGO_EXPORT void Dilation(
		const Image3d<T> &in, 
		Image3d<T> &out, 
		const Neighbourhood &neib);

	template <class T> I3D_ALGO_EXPORT void LocalDilation(
		const Image3d<T> &in, 
		Image3d<T> &out, 
		const Image3d<bool> &,
		const Neighbourhood &neib);

	/** Morphological Erosion. */
	template <class T> I3D_ALGO_EXPORT void Erosion(
		const Image3d<T> &in, 
		Image3d<T> &out, 
		const Neighbourhood &neib);

	template <class T> I3D_ALGO_EXPORT void LocalErosion(
		const Image3d<T> &in, 
		Image3d<T> &out, 
		const Image3d<bool> &,
		const Neighbourhood &neib);

	/** Morphological Closing. */
	template <class T> I3D_ALGO_EXPORT void Closing(
		const Image3d<T> &in,
		Image3d<T> &out,
		const Neighbourhood &neib);

	template <class T> I3D_ALGO_EXPORT void LocalClosing(
		const Image3d<T> &in,
		Image3d<T> &out,
		const Image3d<bool> &,
		const Neighbourhood &neib);

	/** Morphological Closing. - Old version (use the version with the output image - Martin Maska 2008-04-06)*/
	template <class T> I3D_ALGO_EXPORT void Closing(Image3d<T> &in, const Neighbourhood &neib);

	/** Morphological Opening. */
	template <class T> I3D_ALGO_EXPORT void Opening(
		const Image3d<T> &in,
		Image3d<T> &out,
		const Neighbourhood &neigh);

	template <class T> I3D_ALGO_EXPORT void LocalOpening(
		const Image3d<T> &in,
		Image3d<T> &out,
		const Image3d<bool> &,
		const Neighbourhood &neigh);

	/** Morphological Opening. - Old version (use the version with the output image - Martin Maska 2008-04-06)*/
	template <class T> I3D_ALGO_EXPORT void Opening(Image3d<T> &in, const Neighbourhood &neib);

    /** Morphological WhiteTopHat. */
	template <class T> I3D_ALGO_EXPORT void WhiteTopHat(
		const Image3d<T> &in, 
        Image3d<T> &out,
		const Neighbourhood &neib);

	/** Morphological BlackTopHat. */
	template <class T> I3D_ALGO_EXPORT void BlackTopHat(
		const Image3d<T> &in, 
        Image3d<T> &out,
		const Neighbourhood &neib);

	/** Morphological TopHat. - Old version (use WhiteTopHat function - Martin Maska 2008-04-06)*/
	template <class T> I3D_ALGO_EXPORT void TopHat(Image3d<T> &in, const Neighbourhood &neib);

	/** Morphological HitOrMiss. */
	template <class T> I3D_ALGO_EXPORT void HitOrMiss(
		const Image3d<T> &in, 
		Image3d<T> &out, 
		const Neighbourhood &b, 
		const Neighbourhood &w);

	/** Morphological thinning. */
	template <class T> I3D_ALGO_EXPORT void Thinning(
		const Image3d<T> &in, 
		Image3d<T> &out, 
		const Neighbourhood &b, 
		const Neighbourhood &w);

	/** Morphological thicking. */
	template <class T> I3D_ALGO_EXPORT void Thicking(
		const Image3d<T> &in, 
		Image3d<T> &out,
		const Neighbourhood &b, 
		const Neighbourhood &w);


	/** 
		Effective morphological operations with an approximation of a disk. 
		radius is in pixels
		Disk is approximated by octagon (polyhedron), uses decomposition of SE (alternating nb6 and nb 27)

		by Pavel Matula, 2009
	*/
	template <class T> I3D_ALGO_EXPORT void DilationO(const Image3d<T> &in, Image3d<T> &out, const int radius_size);
	template <class T> I3D_ALGO_EXPORT void ErosionO(const Image3d<T> &in, Image3d<T> &out, const int radius_size);
	template <class T> I3D_ALGO_EXPORT void ClosingO(const Image3d<T> &in, Image3d<T> &out, const int radius_size);
	template <class T> I3D_ALGO_EXPORT void OpeningO(const Image3d<T> &in, Image3d<T> &out, const int radius_size);
	template <class T> I3D_ALGO_EXPORT void WhiteTopHatO(const Image3d<T> &in, Image3d<T> &out, const int radius_size);
	template <class T> I3D_ALGO_EXPORT void BlackTopHatO(const Image3d<T> &in, Image3d<T> &out, const int radius_size);

	/** 
		Computes maximas of the given dymanic.  

		by Pavel Matula, 2009
	*/
	template <class T> I3D_ALGO_EXPORT void MaximaDynamic(const Image3d<T> &in, Image3d<bool> &out, const T dynamic);

	/** Effective morphological operations with disk structuring elements. 
		radius is in microns
	*/
	
	I3D_ALGO_EXPORT void Dilation(const Image3d<bool> &in, Image3d<bool> &out, const float radius);

	I3D_ALGO_EXPORT void Erosion(const Image3d<bool> &in, Image3d<bool> &out, const float radius);

	I3D_ALGO_EXPORT void Closing(const Image3d<bool> &in, Image3d<bool> &out, const float radius);

	I3D_ALGO_EXPORT void Opening(const Image3d<bool> &in, Image3d<bool> &out, const float radius);

	/** Mask image must be larger than or equal to the marker image. */
	template <class T> I3D_ALGO_EXPORT void Geodesic_dilation(
		const Image3d<T> &marker, 
		const Image3d<T> &mask, 
		Image3d<T> &out, 
		const Neighbourhood &neib);

	/** Marker image must be larger than or equal to the mask image. */
	template <class T> I3D_ALGO_EXPORT void Geodesic_erosion(
		const Image3d<T> &marker, 
		const Image3d<T> &mask, 
		Image3d<T> &out, 
		const Neighbourhood &neib);

	/** Computes h-Maxima, suppress all maxima whose 
	depth is smaller than h. */
	template <class T> I3D_ALGO_EXPORT void h_Max(
		const Image3d<T> &in, 
		T h, 
		Image3d<T> &out);

	/** Computes h-Maxima, suppress all maxima whose 
	depth is smaller than h.
	For 4-connected (2D) and 6-connected (3D) neighbourhoods ONLY. 
	Implementation using HRA algorithm. */
	template <class T> I3D_ALGO_EXPORT void HRA_h_Max(
		const Image3d<T> &in, 
		T h, 
		Image3d<T> &out);

	/** Compute h-Convex transformation. */
	template <class T> I3D_ALGO_EXPORT void h_Convex(
		const Image3d<T> &in,
		T h,
		Image3d<T> &out);

	/** TODO Comment */
	template <class T> I3D_ALGO_EXPORT void r_Max_bysweeping(
		const Image3d<T> &in, 
		Image3d<T> &out);

	/** Computes regional maxima - they will be marked with std::numeric_limits<T>::max(), nonmaxima with 0. 
	\warning For 4-connected (2D) and 6-connected (3D) neighbourhoods r_Max_bysweeping is used - is faster for some kinds of images. */
	template <class T> I3D_ALGO_EXPORT void r_Max(
		const Image3d<T> &in, 
		Image3d<T> &out, 
		const Neighbourhood &neib);

	/** Computes regional maxima - they will be marked with std::numeric_limits<T>::max(), nonmaxima with 0.
	For 4-connected (2D) and 6-connected (3D) neighbourhoods ONLY. 
	For integer data types only.
	Implementation using HRA algorithm. */
	template <class T> I3D_ALGO_EXPORT void HRA_r_Max(
		const Image3d<T> &in, 
		Image3d<T> &out, 
		const Neighbourhood &neib);

	/** Computes regional minima - they will be marked with std::numeric_limits<T>::max(), nonminima with 0.*/
	template <class T> I3D_ALGO_EXPORT void r_Min(
		const Image3d<T> &in, 
		Image3d<T> &out, 
		const Neighbourhood &neib);

	/** Computes regional minima by HRA algorithm - they will be marked with std::numeric_limits<T>::max(), nonminima with 0.
	For 4-connected (2D) and 6-connected (3D) neighbourhoods ONLY. 
	For integer data types only.
	Implementation using HRA algorithm. */
	template <class T> I3D_ALGO_EXPORT void HRA_r_Min(
		const Image3d<T> &in, 
		Image3d<T> &out, 
		const Neighbourhood &neib);

	/** Computes h-extended maxima, EMAX_h(f) = RMAX(HMAX_h(f)). */
	template <class T> I3D_ALGO_EXPORT void e_Max(
		const Image3d<T> &in, 
		T h, 
		Image3d<T> &out,
		const Neighbourhood &neib);

	/** Computes h-extended maxima, EMAX_h(f) = RMAX(HMAX_h(f)).
	For 4-connected (2D) and 6-connected (3D) neighbourhoods ONLY. 
	Implementation using HRA algorithm. */
	template <class T> I3D_ALGO_EXPORT void HRA_e_Max(
		const Image3d<T> &in, 
		T h, 
		Image3d<T> &out,
		const Neighbourhood &neib);

	/** minima imposition where mask_bin == 1 */
	template <class T> I3D_ALGO_EXPORT  void impose_minima(Image3d<T> &in_out, const Image3d<bool> &mask_bin);

	/** Holes filling algorithm computed using the morphological reconstruction by erosion. */
	template <class T> I3D_ALGO_EXPORT void Fillhole(
		const Image3d<T> &in,
		Image3d<T> &out);

	/** This implementation does not work! Please use the versions without Neighbourhood instead. */
	template <class T, class F, class G> I3D_ALGO_EXPORT void Reconstruction_by_DilEro(
		const Image3d<T> &marker, 
		const Image3d<T> &mask, 
		Image3d<T> &out, 
		const Neighbourhood &neib, 
		F func_f, 
		G func_g);

	/** General geodesic reconstruction function. */
	template <class T, class F, class G> I3D_ALGO_EXPORT void Reconstruction_by_DilEro(
		const Image3d<T> &marker,
		const Image3d<T> &mask,
		Image3d<T> &out, 
		F func_f, 
		G func_g);

	/** This implementation does not work! Please use the versions without Neighbourhood instead.
	Mask image must be larger than or equal to the marker image. */
	template <class T> I3D_ALGO_EXPORT void Reconstruction_by_dilation(
		const Image3d<T> &marker,
		const Image3d<T> &mask,
		Image3d<T> &out, 
		const Neighbourhood &neib);

	/** Mask image must be larger than or equal to the marker image. */
	template <class T> I3D_ALGO_EXPORT void Reconstruction_by_dilation(
		const Image3d<T> &marker, 
		const Image3d<T> &mask, 
		Image3d<T> &out);

	/** This implementation does not work! Please use the versions without Neighbourhood instead.
	Marker image must be larger than or equal to the mask image. */
	template <class T> I3D_ALGO_EXPORT void Reconstruction_by_erosion(
		const Image3d<T> &marker,
		const Image3d<T> &mask,
		Image3d<T> &out, 
		const Neighbourhood &neib);

	/** Marker image must be larger than or equal to the mask image. */
	template <class T> I3D_ALGO_EXPORT void Reconstruction_by_erosion(
		const Image3d<T> &marker, 
		const Image3d<T> &mask, 
		Image3d<T> &out);

	/** Morphological reconstruction by Hybrid Reconstruction Algorithm [Vincent, 93]
	Implementated Sep 14, 2010 by P. Karas
	For 4-connected (2D) and 6-connected (3D) neighbourhoods ONLY. 
	TODO: Connectivity parameter & implementation for 8- and 26-connectivities */

	/** General geodesic reconstruction function. */
	/*
	template <class T, class F, class G> I3D_ALGO_EXPORT void HRA_Reconstruction_by_DilEro(
		const Image3d<T> &marker,
		const Image3d<T> &mask,
		Image3d<T> &out, 
		F func_f, 
		G func_g);*/

	/** Mask image must be larger than or equal to the marker image. */
	template <class T> I3D_ALGO_EXPORT void HRA_Reconstruction_by_dilation(
		const Image3d<T> &marker, 
		const Image3d<T> &mask, 
		Image3d<T> &out);

	/** Marker image must be larger than or equal to the mask image. */
	template <class T> I3D_ALGO_EXPORT void HRA_Reconstruction_by_erosion(
		const Image3d<T> &marker, 
		const Image3d<T> &mask, 
		Image3d<T> &out);

	template <class T, class F, class G> I3D_ALGO_EXPORT void HRA_Reconstruction_by_DilEro(
		const Image3d<T> &marker,
		const Image3d<T> &mask,
		Image3d<T> &out, 
		F func_f, 
		G func_g);

	/**************************************************************************\
	*
	*				  Mathematical morphology related functions
	*
	\**************************************************************************/
	/** \todo Zatim pouzita pouze pri vypoctu dilatace a eroze, ale slo by ji 
	vyuzit i jinde? Aplikuje funkci F v danem okoli. */
	template <class T, class F> I3D_ALGO_EXPORT void DilEro(
		const Image3d<T> &in, 
		Image3d<T> &out,
		const Neighbourhood &neib, 
		F function);

	template <class T, class F> I3D_ALGO_EXPORT void LocalDilEro(
		const Image3d<T> &in, 
		Image3d<T> &out,
		const Image3d<bool> &,
		const Neighbourhood &neib, 
		F function);

	/** DiscreteDistance function needs 4 parameters:
	\param in input image
	\param out output (filtered) image
	\param neib neighbourhood applied to each voxel
	\param p condition, which must be hold in each voxel so that this voxel
	could be plugged into the process of computation. */
	template <class T1, class T2, class Pred> I3D_ALGO_EXPORT void DiscreteDistance(
		const Image3d<T1> &in, 
		Image3d<T2> &out,
		const Neighbourhood &neib, 
		Pred p);

	/**************************************************************************\
	*
	*                 Mathematical morphology related predicates
	*
	\**************************************************************************/
	/** \todo Could be moved to morphology.cc file? */
	template <class T> struct I3D_ALGO_EXPORT minimum
	{
		T operator() (const T& x, const T& y) const { return std::min(x,y); }
	};

	/** \todo Could be moved to morphology.cc file? */
	template <class T> struct I3D_ALGO_EXPORT maximum
	{
		T operator() (const T& x, const T& y) const { return std::max(x,y); }
	};

	/** \todo Could be moved to morphology.cc file? */
	template <class T> class I3D_ALGO_EXPORT less_than
	{
		T arg2;
	public: 
		explicit less_than(const T& x): arg2(x) { }
		bool operator() (const T& x) const { return x<arg2; }
	};

	/** \todo Could be moved to morphology.cc file? */
	template <class T> class I3D_ALGO_EXPORT greater_than
	{
		T arg2;
	public: 
		explicit greater_than(const T& x): arg2(x) { }
		bool operator() (const T& x) const { return x>arg2; }
	};

	/**************************************************************************\
	*
	*						  Helper functions
	*
	\**************************************************************************/
	/** returns true if color of all points in neighbourhoods corresponds to image. */
	template <class T> I3D_ALGO_EXPORT bool Correspond(std::vector<T*>& b, std::vector<T*>& w);

	///@} end of morph group

} // i3d namespace

#endif
