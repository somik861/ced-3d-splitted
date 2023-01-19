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
 * FastLevelSet.h
 *
 * Fast level set-like algorithms intended for image segmentation as well as binary image deformations
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FAST_LEVELSET_H
#define FAST_LEVELSET_H

#include "image3d.h"
#include "fastlevelset/routine.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                        NeumannBoundary                      //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Set the border of given image according to Neumann (zero differences on the border). The second parameter determines whether the central or forward and backward 
		  * difference scheme is used. It is assumed that the input image is already padded by 1 in each direction. */
		template <class VOXEL> I3D_ALGO_EXPORT void NeumannBoundary(Image3d<VOXEL> &img, bool central = true);

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                    GradientMagnitudeImage                   //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Create a gradient magnitude image from given one. The output image is expanded by 1 in each direction and its border is set according to Neumann. 
		  * This function should be called before creating a segmentation routine using the CreateSegRoutine() function. */
		template <class VOXEL> I3D_ALGO_EXPORT void GradientMagnitudeImage(const Image3d<VOXEL> &src, Image3d<Type::Prec> &dst);

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                    VarInflationForceField                   //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Create an inflation force field defined as a distance transform of given intensity level. The output image is expanded by 1 in each direction.
		  * This function should be called before creating a segmentation routine using the CreateVarSegRoutine() function. */
		template <class VOXEL> I3D_ALGO_EXPORT void VarInflationForceField(const Image3d<VOXEL> &src, VOXEL level, Image3d<Type::Prec> &dst); 

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//						 RegionSpeedImage                      //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Create a speed image for the region-based models from given one. The output image is expanded by 1 in each direction. This function should be called 
		  * before creating the region-based routines using, for instance, the ChanVeseRoutine() or RoussonDericheRoutine() function. */
		template <class VOXEL> I3D_ALGO_EXPORT void RegionSpeedImage(const Image3d<VOXEL> &src, Image3d<Type::Prec> &dst);

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                          SegRoutine                         //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Create a routine intended for image segmentation based on the geodesic model with a constant inflation force. */
		I3D_ALGO_EXPORT Routine<int> *SegRoutine(const Image3d<Type::Prec> &grad_mag, const Image3d<Type::BinVoxel> &mask, const Image3d<Type::BinVoxel> *domain, bool preserve_topology, 
												 Type::Size radius, Type::Prec inflation_impact, Type::Prec curvature_impact, Type::Prec advection_impact, Type::Size exponent);

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                        VarSegRoutine                        //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Create a routine intended for image segmentation based on the geodesic model with a variable inflation force. */
		I3D_ALGO_EXPORT Routine<int> *VarSegRoutine(const Image3d<Type::Prec> &grad_mag, const Image3d<Type::BinVoxel> &mask, const Image3d<Type::BinVoxel> *domain, bool preserve_topology, 
													Type::Size radius, const Image3d<Type::Prec> &inflation_impact, Type::Prec curvature_impact, Type::Prec advection_impact, Type::Size exponent);

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                          DefRoutine                         //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Create a routine intended for image deformation based of the geometric model. */
		I3D_ALGO_EXPORT Routine<int> *DefRoutine(const Image3d<Type::Prec> &speed, const Image3d<Type::BinVoxel> &mask, const Image3d<Type::BinVoxel> *domain, 
			                                     Type::Size radius, Type::Prec inflation_impact, Type::Prec curvature_impact);

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                     GlobChanVeseRoutine                     //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Create a routine intended for image segmentation based on the Chan-Vese model. The whole interface is propagated in each iteration. */
		I3D_ALGO_EXPORT Routine<int> *GlobChanVeseRoutine(const Image3d<Type::Prec> &input, const Image3d<Type::BinVoxel> &mask, const Image3d<Type::BinVoxel> *domain, bool preserve_topology, 
														  Type::Size radius, Type::Prec curvature_impact, Type::Prec foreground_impact, Type::Prec background_impact);

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                      LocChanVeseRoutine                     //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Create a routine intended for image segmentation based on the Chan-Vese model. The interface point of the minimal departure time is propagated in each iteration. */
		I3D_ALGO_EXPORT Routine<int> *LocChanVeseRoutine(const Image3d<Type::Prec> &input, const Image3d<Type::BinVoxel> &mask, const Image3d<Type::BinVoxel> *domain, 
														 Type::Size radius, Type::Prec curvature_impact, Type::Prec foreground_impact, Type::Prec background_impact);

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                    LabGlobChanVeseRoutine                   //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Create a routine intended for image segmentation based on the labelled Chan-Vese model. The whole interface is propagated in each iteration. */
		I3D_ALGO_EXPORT Routine<int> *LabGlobChanVeseRoutine(const Image3d<Type::Prec> &input, const Image3d<Type::LabVoxel> &mask, const Image3d<Type::BinVoxel> *domain, 
                                             			     Type::Size radius, Type::Prec curvature_impact, Type::Prec foreground_impact, Type::Prec background_impact, bool multiple);

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                  GlobRoussonDericheRoutine                  //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Create a routine intended for image segmentation based on the Rousson-Deriche model. The whole interface is propagated in each iteration. */
		I3D_ALGO_EXPORT Routine<int> *GlobRoussonDericheRoutine(const Image3d<Type::Prec> &input, const Image3d<Type::BinVoxel> &mask, const Image3d<Type::BinVoxel> *domain, 
															    bool preserve_topology, Type::Size radius, Type::Prec curvature_impact);

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                   LocRoussonDericheRoutine                  //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Create a routine intended for image segmentation based on the Rousson-Deriche model. The interface point of the minimal departure time is propagated in each iteration. */
		I3D_ALGO_EXPORT Routine<int> *LocRoussonDericheRoutine(const Image3d<Type::Prec> &input, const Image3d<Type::BinVoxel> &mask, const Image3d<Type::BinVoxel> *domain, 
															   Type::Size radius, Type::Prec curvature_impact);

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                 LabGlobRoussonDericheRoutine                //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Create a routine intended for image segmentation based on the labelled Rousson-Deriche model. The whole interface is propagated in each iteration. */
		I3D_ALGO_EXPORT Routine<int> *LabGlobRoussonDericheRoutine(const Image3d<Type::Prec> &input, const Image3d<Type::LabVoxel> &mask, const Image3d<Type::BinVoxel> *domain, 
															       Type::Size radius, Type::Prec curvature_impact, bool multiple);

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                          MCMRoutine                         //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Create a routine intended for deformation of binary images based on the mean curvature motion. */
		I3D_ALGO_EXPORT Routine<int> *MCMRoutine(const Image3d<Type::BinVoxel> &input, const Image3d<Type::BinVoxel> *domain, Type::Size radius);

	} // namespace fls 
	
} // namespace i3d

#endif
