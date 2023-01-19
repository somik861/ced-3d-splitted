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
 * routine.h
 *
 * Computational routine interface
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_ROUTINE_H
#define FLS_ROUTINE_H

#include "../algo_export.h"
#include "grid.h"
#include "result_creator.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                       Class Routine                         //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Computational routine interface. The template parameter describes a type of the implicit function which the routine works with. */
		template <class T> class I3D_ALGO_EXPORT Routine
		{
			private:
				/** Pointer to the Grid object. */
				const Grid<T> *m_grid;
				/** Pointer to the ResultCreator object. */
				const ResultCreator *m_result_creator;
				/** Counter of performed iterations. */
				Type::Size m_num_iter;

			public:
				/** Constructor. */
				Routine(const Grid<T> *grid, const ResultCreator *result_creator) : m_grid(grid), m_result_creator(result_creator), m_num_iter(0) {};
				/** Destructor. */
				virtual ~Routine() { delete m_grid; delete m_result_creator; };
				/** Get a pointer to the implicit function. */
				const T *ImplicitFunction() const { return m_grid -> m_implicit_function.ptr(0); };
				/** Perform a given number of iterations. The computation is stopped when either the given number of iterations has been performed or another one cannot be performed. */
				void Iterate(Type::Size num_iter);
				/** Iterate until convergence. The computation is stopped when a convergence criterion is reached, another iteration cannot be performed, or the maximal number of 
				  * iterations has been performed. By default, the empty convergence criterion is considered. Therefore, this function behaves in the same manner as the Iterate() function, 
				  * until a specific criterion is not redefined using the Converged() function. */
				void IterateUntilConvergence(Type::Size max_num_iter);
				/** Create a binary mask for given result type to preallocated buffer. The last parameter determines whether the mask is computed over
				  * the whole image or only inside the domain. In the latter case, the mask image is only changed inside the domain. */
				void Mask(Type::BinVoxel *mask, ResultCreator::ResType type, bool only_in_domain = false) const { m_result_creator -> GetMask(mask, type, only_in_domain); };
				/** Create a labeled image of foreground components to preallocated buffer. The last parameter determines whether the labeled image is computed over
				  * the whole image or only inside the domain. In the latter case, the labeled image is only changed inside the domain. */
				void Labels(Type::LabVoxel *labels, bool only_in_domain = false) const { m_result_creator -> GetLabels(labels, only_in_domain); };
				
				////////////////////// THESE PUBLIC FUNCTIONS MUST BE DEFINED IN DERIVED CLASSES /////////////////////

				/** Initialize the routine. */
				virtual void Initialize() = 0;
				/** Get the number of grid points belonging to the interface. */
				virtual Type::Size InterfaceSize() const = 0;
				/** Check whether the next iteration can be performed. */
				virtual bool Ready() const = 0;
				/** Perform one iteration. */
				virtual void PerformIteration() = 0;

				////////////////////// THESE PUBLIC FUNCTIONS COULD BE REDEFINED IN DERIVED CLASSES /////////////////////
				/** Check whether a convergence criterion has been reached. */
				virtual bool Converged() const { return false; };
				/** Show information about the routine on the standard output. By default, the status of the routine as well as the number of performed iterations is shown. */ 
				virtual void Info() const;
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_ROUTINE_H

