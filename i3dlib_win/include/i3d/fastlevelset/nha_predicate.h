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
 * nha_predicate.h
 *
 * Unary predicates used in the Nilsson-Heyden algorithm. They are primarily intended for relational operators taking into consideration the implicit function against a given value.
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_NHA_PREDICATE_H
#define FLS_NHA_PREDICATE_H

#include <functional>

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                    Class NHA_Predicate                      //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Unary predicate used in the Nilsson-Heyden algorithm. 
		  * It is primarily intended for relational operators taking into consideration the implicit function against a given value. */
		class NHA_Predicate : public std::function<bool(int)>
		{
			public:
				/** Constructor. */
				NHA_Predicate() {};
				/** Destructor. */
				virtual ~NHA_Predicate() {};
				/** Relational operator. */
				virtual bool operator()(const int &value) const = 0;
		};

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                  Class NHA_PredicateEqual                   //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Unary predicate intended for testing equality of the implicit function against a template parameter. */
		template <int N> class NHA_PredicateEqual : public NHA_Predicate
		{
			public:
				/** Check equality against a template parameter. */
				virtual bool operator()(const int &value) const { return (value == N); };
		};

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                  Class NHA_PredicateChoice                  //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Unary predicate intended for testing equality of the implicit function against two template parameters. */
		template <int N1, int N2> class NHA_PredicateChoice : public NHA_Predicate
		{
			public:
				/** Check equality against two template parameters. */
				virtual bool operator()(const int &value) const { return (value == N1 || value == N2); };
		};

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                   Class NHA_PredicateLess                   //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Unary predicate intended for the relational operator 'Less than' taking into consideration the implicit function against a template parameter. */
		template <int N> class NHA_PredicateLess : public NHA_Predicate
		{
			public:
				/** Check the 'Less than' property against a template parameter. */
				virtual bool operator()(const int &value) const { return (value < N); };
		};

		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                  Class NHA_PredicateGreater                 //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Unary predicate intended for the relational operator 'Greater than' taking into consideration the implicit function against a template parameter. */
		template <int N> class NHA_PredicateGreater : public NHA_Predicate
		{
			public:
				/** Check the 'Greater than' property against a template parameter. */
				virtual bool operator()(const int &value) const { return (value > N); };
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_NHA_PREDICATE_H

