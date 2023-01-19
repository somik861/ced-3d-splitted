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
 * object_manager.h
 *
 * Manager responsible for efficient computation of foreground and background object statistics
 *
 * Martin Maška (xmaska@fi.muni.cz) 2006 - 2011
 */

#ifndef FLS_OBJECT_MANAGER_H
#define FLS_OBJECT_MANAGER_H

#include "object_list.h"

namespace i3d
{
	namespace fls
	{
		/////////////////////////////////////////////////////////////////
		//                                                             //
		//                     Class ObjectManager                     //
		//                                                             //
		/////////////////////////////////////////////////////////////////

		/** Manager responsible for efficient computation of average foreground and background object statistics. */
		class ObjectManager
		{
			private:
				/** Image data. */
				const Type::Prec *m_data;
				/** List of objects. The background has always the label 0. The foreground objects have positive labels. 
				  * The base class considers only one foreground object. Therefore, the list has always only two members. */
				ObjectList m_obj_list;
				/** Accumulated differences in the average intensity of foreground and background objects. */
				Type::Prec m_diff;
				/** Number of remaining synchronizations to be performed before updating accumulated differences in the average intensity of foreground and background objects. */
				int m_remain_iter;
				/** Periodicity of updates of accumulated differeneces in the average intensity of foreground and background objects. */
				static const int m_num_iter = 2;
			
			public:
				/** Constructor. */
				ObjectManager(const Type::Prec *data) : m_data(data), m_obj_list(), m_diff(Type::Prec(10)), m_remain_iter(m_num_iter) {};			                                
				/** Destructor. */
				virtual ~ObjectManager() {};
				/** Get the foreground deviation of the i-th grid point. */
				Type::Prec DevForeground(Type::Size i) const { return m_data[i] - m_obj_list.Ref(Label(i)).AvgIntensity(); };
				/** Get the background deviation of the i-th grid point. */
				Type::Prec DevBackground(Type::Size i) const { return m_data[i] - m_obj_list.Ref(0).AvgIntensity(); };
				/** Get the square of the foreground deviation of the i-th grid point. */
				Type::Prec SqrDevForeground(Type::Size i) const { return Sqr(DevForeground(i)); };
				/** Get the square of the background deviation of the i-th grid point. */
				Type::Prec SqrDevBackground(Type::Size i) const { return Sqr(DevBackground(i)); };
				/** Get the foreground variance term of the i-th grid point. */
				Type::Prec VarForeground(Type::Size i) const; 
				/** Get the background variance term of the i-th grid point. */
				Type::Prec VarBackground(Type::Size i) const;
				/** Add the i-th grid points to the foreground. */
				void AddForeground(Type::Size i) { m_obj_list.AdvRef(Label(i)).AddPoint(m_data[i]); };
				/** Add the i-th grid points to the background. */
				void AddBackground(Type::Size i) { m_obj_list.Ref(0).AddPoint(m_data[i]); };
				/** Swap the i-th grid point from the foreground to the background. */
				void SwapForeground(Type::Size i) { m_obj_list.Ref(Label(i)).RemovePoint(m_data[i]); m_obj_list.Ref(0).AddPoint(m_data[i]); };
				/** Swap the i-th grid point from the background to the foreground. */
				void SwapBackground(Type::Size i) { m_obj_list.Ref(0).RemovePoint(m_data[i]); m_obj_list.Ref(Label(i)).AddPoint(m_data[i]); };
				/** Synchronize foreground and background objects and return the sum of absolute values of their differences in the average intensity since the previous synchronization. */
				void Synchronize();
				/** Check whether the sum of absolute values of differences in the average intensities of foreground and background objects is lower than a given value. */
				bool Converged() const { return !Positive(m_diff) && m_remain_iter % 2 == 1; };
				/** Show information about foreground and background objects on the standard output. */
				void Info() const { m_obj_list.Info(); };

			private:
				/** Get a label of the foreground object to which the i-th grid point belongs to. The default implementation returns always 1, since only one foreground object is considered. */ 
				virtual Type::LabVoxel Label(Type::Size i) const { return 1; };
		};

	} // namespace fls 

} // namespace i3d

#endif // FLS_OBJECT_MANAGER_H

