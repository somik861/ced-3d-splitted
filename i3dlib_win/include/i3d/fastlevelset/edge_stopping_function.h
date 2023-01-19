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
 * edge_stopping_function.h
 *
 * Edge-stopping function 
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_EDGE_STOPPING_FUNCTION_H
#define FLS_EDGE_STOPPING_FUNCTION_H

#include "speed_function.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                 Class EdgeStoppingFunction                  //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Edge-stopping function. It is usually a strictly decreasing function of the gradient magnitude image. 
		  * Its role is to slow down the interface when it reaches an edge. */
		class EdgeStoppingFunction : public SpeedFunction
		{
			protected:
				/** Gradient magnitude of image data. */
				const Type::Prec *m_grad_mag;

			public:
				/** Constructor. */
				EdgeStoppingFunction(const Type::Prec *grad_mag) : m_grad_mag(grad_mag) {};
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_EDGE_STOPPING_FUNCTION_H

