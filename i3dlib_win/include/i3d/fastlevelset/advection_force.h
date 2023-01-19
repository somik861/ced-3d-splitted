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
 * advection_force.h
 *
 * Advection force
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_ADVECTION_FORCE_H
#define FLS_ADVECTION_FORCE_H

#include "defs.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                    Class AdvectionForce                     //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Advection force. */
		class AdvectionForce
		{
			public:
				/** Constructor. */
				AdvectionForce() {};
				/** Destructor. */
				virtual ~AdvectionForce() {};
				/** Get the advection force at the i-th grid point. */
				virtual Type::Prec Get(Type::Size i) const = 0;
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_ADVECTION_FORCE_H

