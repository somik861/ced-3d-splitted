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
 * nha_advection_force.h
 *
 * Advection force used in the Nilsson-Heyden algorithm
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_NHA_ADVECTION_FORCE_H
#define FLS_NHA_ADVECTION_FORCE_H

#include "advection_force.h"
#include "grid.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                  Class NHA_AdvectionForce                   //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Advection force used in the Nilsson-Heyden algorithm for 2D grids. */
		class NHA_AdvectionForce : public AdvectionForce
		{
			protected:
				/** Computational grid. */
				const Grid<int> &m_grid;
				/** Gradient magnitude of image data. */
				const Type::Prec *m_grad_mag;
				/** Precomputed denominator intended for efficient computation of central differences in the x axis. */
				Type::Prec m_denom_x;
				/** Precomputed denominator intended for efficient computation of central differences in the y axis. */
				Type::Prec m_denom_y;

			public:
				/** Constructor. */
				NHA_AdvectionForce(const Grid<int> &grid, const Type::Prec *grad_mag) 
					: AdvectionForce(), m_grid(grid), m_grad_mag(grad_mag), m_denom_x(Type::Prec(0.25) * Sqr(grid.m_res_x)), m_denom_y(Type::Prec(0.25) * Sqr(grid.m_res_y)) {};
				/** Get the advection force at the i-th grid point. */
				virtual Type::Prec Get(Type::Size i) const;
		};

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                 Class NHA_AdvectionForce3D                  //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Advection force used in the Nilsson-Heyden algorithm for 3D grids. */
		class NHA_AdvectionForce3D : public NHA_AdvectionForce
		{
			protected:
				/** Precomputed denominator intended for efficient computation of central differences in the z axis. */
				Type::Prec m_denom_z;

			public:
				/** Constructor. */
				NHA_AdvectionForce3D(const Grid<int> &grid, const Type::Prec *grad_mag) : NHA_AdvectionForce(grid, grad_mag), m_denom_z(Type::Prec(0.25) * Sqr(grid.m_res_z)) {};
				/** Get the advection force at the i-th grid point. */
				virtual Type::Prec Get(Type::Size i) const;
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_NHA_ADVECTION_FORCE_H

