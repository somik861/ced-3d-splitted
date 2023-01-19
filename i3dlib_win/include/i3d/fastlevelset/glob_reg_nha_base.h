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
 * glob_reg_nha_base.h
 *
 * Base of the global region-based version of the Nilsson-Heyden algorithm
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_GLOB_REG_NHA_BASE_H
#define FLS_GLOB_REG_NHA_BASE_H

#include <vector>
#include "nha_grid.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                   Class Glob_Reg_NHA_Base                   //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Base of the global region-based version of the Nilsson-Heyden algorithm. */
		class Glob_Reg_NHA_Base : public NHA_Grid
		{
			public:
				/** Buffer intended for storing the interface points. */
				std::vector<Type::Size> m_interface;

			public:
				/** Constructor. */
				Glob_Reg_NHA_Base(Type::Size sx, Type::Size sy, Type::Size sz, Type::Prec spac_x, Type::Prec spac_y, Type::Prec spac_z) 
					: NHA_Grid(sx, sy, sz, spac_x, spac_y, spac_z), m_interface() {};
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_GLOB_REG_NHA_BASE_H

