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
 * const_edge_stopping_function.h
 *
 * Constant edge-stopping function 
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_CONST_EDGE_STOPPING_FUNCTION_H
#define FLS_CONST_EDGE_STOPPING_FUNCTION_H

#include "edge_stopping_function.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//               Class ConstEdgeStoppingFunction               //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		class ConstEdgeStoppingFunction : public EdgeStoppingFunction
		{
			public:
				/** Constructor. */
				ConstEdgeStoppingFunction(const Type::Prec *grad_mag) : EdgeStoppingFunction(grad_mag) {};
				/** Get the speed at the i-th grid point. */
				virtual Type::Prec Get(Type::Size i) const { return m_grad_mag[i]; };
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_CONST_EDGE_STOPPING_FUNCTION_H

