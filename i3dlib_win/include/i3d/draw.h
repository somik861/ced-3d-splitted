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

/** \file draw.h
  \brief Basic drawing, filling and rasterization algorithms - header

  Drawing into 3d-image.
  \todo

  \author Pavel Matula (pam@fi.muni.cz) 2002
  \author David Svoboda (xsvobod2@fi.muni.cz) 2002 - FloodFill functions

*/

#ifndef __DRAW_H__
#define __DRAW_H__

#ifdef __GNUG__
#	pragma interface
#endif

#include <vector>
#include <list>
#include "image3d.h"
#include "regions.h"

namespace i3d {
	/** \defgroup draw Drawing & Rasterization
	\todo better documentation format, why is Offset used as a representation of 3d point?
	*/
	///@{
	/**************************************************************************\
	*
	*					Drawing and rasterization algorithms
	*
	\**************************************************************************/
	/**
	draws line 
	p1, p2
	into image img with specified color.

	points coordinates are in microns
	*/
	template <class T> I3D_ALGO_EXPORT void DrawLine(Image3d<T> &img, const Offset &p1, const Offset &p2, T color);

	/**
	draws line 
	p1, p2
	into image img with specified color.

	points coordinates are in pixels
	*/
	template <class T> I3D_ALGO_EXPORT void DrawLine(
		Image3d<T> &img, 
		Vector3d<size_t> p1, 
		Vector3d <size_t> p2,
		T color);

	/**
	draws lines 
	\verbatim
	pnts[0], pnts[1]
	pnts[2], pnts[3]
	...
	pnts[pnts.size() - 2], pnts[pnts.size() - 1]
	\endverbatim

	into image img with specified color.

	points coordinates are in microns
	*/
	template <class T> I3D_ALGO_EXPORT void DrawLines(Image3d<T> &img, const std::vector<Offset> &pnts, T color);

	/** 
	draw line
	p1, p2
	using Bres. algorithm
	and stores line points in the image
	*/
	template <class T> I3D_ALGO_EXPORT void DrawLineBres(
		Image3d<T> &img,
		Vector3d<size_t> p1,
		Vector3d<size_t> p2, 
		T color);

	/**
	draw line
	p1, p2
	using Bres. algorithm
	and stores line points in the list of points
	*/
	I3D_ALGO_EXPORT void DrawLineBres(std::list< Vector3d<int> > &ll, Vector3d<size_t> p1, Vector3d<size_t> p2);

	/** Fill given voi with specified colour, voi is in pixels. */
	template <class T> I3D_ALGO_EXPORT void DrawCube(Image3d<T> &img, const VOI<PIXELS> &voi, T color);

	/**************************************************************************\
	*
	*						Filling algorithms
	*
	\**************************************************************************/
	/** FloodFill algorithm for filling the image region with choosen color. The seed voxel is positioned at (x,y,z). 
	  * Function returns ComponentInfo so that we now everything about newly created region in image. */
	template <class VOXEL1, class VOXEL2> I3D_ALGO_EXPORT ComponentInfo<VOXEL2, VOXEL1> FloodFill(
		const Image3d<VOXEL1> &in,
		Image3d<VOXEL2> &out, 
		VOXEL2 color,
		size_t x,
		size_t y, 
		size_t z,
		const Neighbourhood &neib = nb3D_6);

	/** FloodFill algorithm for filling the image region with choosen color. The seed voxel is determined by an index. 
	  * Function returns ComponentInfo so that we now everything about newly created region in image. */
	template <class VOXEL1, class VOXEL2> I3D_ALGO_EXPORT ComponentInfo<VOXEL2, VOXEL1> FloodFill(
		const Image3d<VOXEL1> &in,
		Image3d<VOXEL2> &out, 
		VOXEL2 color,
		size_t seed_index,
		const Neighbourhood &neib = nb3D_6);

	/** FloodFill algorithm for filling the image region with choosen color. The seed voxel is positioned at (x,y,z). */
	template <class VOXEL> I3D_ALGO_EXPORT void FloodFill(
		Image3d<VOXEL> &img,
		VOXEL color, 
		size_t x, 
		size_t y,
		size_t z, 
		const Neighbourhood &neib = nb3D_6);

	/** FloodFill algorithm for filling the image region with choosen color. The seed voxel is determined by an index. */
	template <class VOXEL> I3D_ALGO_EXPORT void FloodFill(
		Image3d<VOXEL> &img,
		VOXEL color, 
		size_t seed_index, 
		const Neighbourhood &neib = nb3D_6);

	///@} end of draw group

	/**************************************************************************\
	*
	*						Other functions
	*
	\**************************************************************************/
	/** \ingroup points
	\todo Where this function move to? 
	Function necessary to inverse image colors. */
	template <class VOXEL> I3D_ALGO_EXPORT void Negative(Image3d<VOXEL> &img);

	/**************************************************************************\
	*
	*						Helper classes
	*
	\**************************************************************************/
	/** Functor for storing voxels into the image. 
	\todo Could be moved to draw.cc? */
	template <class T> class I3D_ALGO_EXPORT StoreToImage {
	public:
		/** Constructor. */
		StoreToImage(Image3d<T> *img_, T col_)
			: img(img_), color(col_)
		{};

		/** Draw point into the image 'img'. */
		void StorePoint(Vector3d<size_t> P) const
		{
			img->SetVoxel (P.x, P.y, P.z, color);
		};

	private:
		/** The image for storing voxels. */
		Image3d<T> *img;
		/** The colour of stored voxels. */
		T color;

	}; // StoreToImage

	/** Functor for storing voxels into the memory - without changing the image.
	\todo Could be moved to draw.cc? */
	class I3D_ALGO_EXPORT StoreToMem {
	public:
		/** Constructor. */
		StoreToMem(std::list< Vector3d<int> > *_ll)
			: ll(_ll) 
		{};

		/** Add point to the buffer. */
		void StorePoint(Vector3d<int> P) const
		{
			ll -> push_back(P);
		};

	private:
		/** memory buffer representing rasterized voxels. */
		std::list< Vector3d<int> > *ll;

	}; // StoreToMem

} // i3d namespace

#endif
