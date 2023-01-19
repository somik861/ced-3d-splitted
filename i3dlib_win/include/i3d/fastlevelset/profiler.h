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
 * profiler.h
 *
 * Profiler
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_PROFILER_H
#define FLS_PROFILER_H

#include <time.h>

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                      Class Profiler                         //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Profiler. */
		class Profiler
		{
			private:
				/** Name of a profiled function. */
				const char *m_name;
				/** Number of calling of a profiled function. */
				int m_num;
				/** Minimal time. */
				clock_t m_min;
				/** Maximal time. */
				clock_t m_max;
				/** Total time. */
				clock_t m_total;
				/** Start time. */
				clock_t m_start;

			public:
				/** Constructor. */
				Profiler(const char *name) : m_name(name), m_num(0), m_min(20000), m_max(0), m_total(0), m_start() {};
				/** Destructor. */
				~Profiler() {};
				/** Start new calling a profiled function. */
				void Start();
				/** Finish calling a profiled function. */
				void Finish();
				/** Report a profile. */
				void Report() const;
		};

	} // namespace fls

} // namespace i3d

#endif // FLS_PROFILER_H

