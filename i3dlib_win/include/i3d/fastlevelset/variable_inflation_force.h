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
 * variable_inflation_force.h
 *
 * Variable inflation force
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_VARIABLE_INFLATION_FORCE_H
#define FLS_VARIABLE_INFLATION_FORCE_H

#include "inflation_force.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                Class VariableInflationForce                 //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Variable inflation force. */
		class VariableInflationForce : public InflationForce
		{
			protected:
				/** Variable inflation force field. */
				const Type::Prec *m_force_field;

			public:
				/** Constructor. */
				VariableInflationForce(const Type::Prec *force_field) : InflationForce(), m_force_field(force_field) {};
				/** Get the inflation force at the i-th grid point. */
				virtual Type::Prec Get(Type::Size i) const { return m_force_field[i]; };
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_VARIABLE_INFLATION_FORCE_H

