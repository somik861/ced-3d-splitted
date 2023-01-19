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

/** \file component_tree.h
\brief Part of mathematical morphology routines - header.

This file provides functions for manipulating the component trees.
*/

#ifndef __COMPONENT_TREE_H__
#define __COMPONENT_TREE_H__

#ifdef __GNUG__
#	pragma interface
#endif

#include "image3d.h"
#include "neighbours.h"

namespace i3d
{
	/** \addtogroup morph */
	///@{

	// forward declarations
	template <typename T> struct I3D_ALGO_EXPORT SCompTreeNode;

	/// Representation of a single item in list of component tree nodes
	template <typename T>
	struct I3D_ALGO_EXPORT SCompTreeNodeListElem
	{
		/// creates node list element holding given value
		SCompTreeNodeListElem(SCompTreeNode<T> *value);

		/// value stored in the list of SCompTreeNodes
		SCompTreeNode<T> *value;
		/// pointer to the next element in the list
		SCompTreeNodeListElem<T> *next;
	};

	/// Representation of a list of component tree nodes
	template <typename T>
	struct I3D_ALGO_EXPORT SCompTreeNodeList
	{
		/// constructor that initializes empty list
		SCompTreeNodeList();
		/// destructor that frees all the allocated resources
		~SCompTreeNodeList();
		/// connects given second list at the end this list, second list is empty at the end
		void Merge(SCompTreeNodeList<T> &second);
		/// inserts and element at the end of this list
		void PushBack(SCompTreeNode<T> *value);

		/// first element in the list
		SCompTreeNodeListElem<T> *first;
		/// last element in the list
		SCompTreeNodeListElem<T> *last;
	};

	/// Representation of a single component tree node
	template <typename T>
	struct I3D_ALGO_EXPORT SCompTreeNode
	{
		/// constructor that initializes default parameters
		SCompTreeNode(const T &level);
		/// destructor that frees all the children
		~SCompTreeNode();

		/// level of the component
		T level;
		/// list of all the child components
		SCompTreeNodeList<T> children;
		/// additional attribudes associated to this node - we need the tree to be variable, so the user can store any attributes his algorithm needs; we also need the attributes to consume as low amount of memory as possible (during the tree building process) because of the high memory complexity of the Najman's component tree building algorithm
		void *attributes;
	};

	/// General empty handler of the additional attributes associated to the component tree node
	template <typename T>
	class I3D_ALGO_EXPORT CCompTreeNodeAttribHandler
	{
	public:
		/// virtual destructor mostly just to keep GCC quiet
		virtual ~CCompTreeNodeAttribHandler() {}

		/// called when new node has been created
		virtual void NodeCreated(SCompTreeNode<T> *node, const T &level) {}
		/// called on the node before it is deleted (usualy this should call itself on the children)
		virtual void DeletingNode(SCompTreeNode<T> *node) {}
		/// called when some node has been added to another one as a child
		virtual void ChildAdded(SCompTreeNode<T> *parentNode, SCompTreeNode<T> *childNode) {}
		/// called when some node has been merged with another one
		virtual void NodesMerged(SCompTreeNode<T> *result, SCompTreeNode<T> *mergee) {}
		/// called on the root node after the build process is finished
		virtual void BuildingFinished(SCompTreeNode<T> *node) {}
		/// prints attributes into the output stream
		virtual void PrintAttrib(std::ostream &ost, const SCompTreeNode<T> *node) {}
	};

	/** Handler of the additional attributes associated to the component tree node - parent, height, area, volume.
	Structure of the attributes during the build process: T highest; size_t area (highest level of the voxels of the component; area of the component)
	Structure of the attributes after the build process: SCompTreeNode<T> *parent; T height; size_t area; size_t volume (parent of the component, maximum height of the component; area of the component; volume of the component)
	*/
	template <typename T>
	class I3D_ALGO_EXPORT CCompTreeNodeAttribHandlerPHAV: public CCompTreeNodeAttribHandler<T>
	{
	public:
		/// constructor that initializes the default attributes
		CCompTreeNodeAttribHandlerPHAV();

		/// allocates space for highest and area in the node
		virtual void NodeCreated(SCompTreeNode<T> *node, const T &level);
		/// frees the space allocated for the attributes in the node and calls itself recursively on the children
		virtual void DeletingNode(SCompTreeNode<T> *node);
		/// increases parent's area by the child's area and sets highest of the parent component to the maximum from the highest of the parent and the child
		virtual void ChildAdded(SCompTreeNode<T> *parentNode, SCompTreeNode<T> *childNode);
		/// increases result's area by the mergee's area and sets highest of the result component to the maximum from the highest of the result and the mergee
		virtual void NodesMerged(SCompTreeNode<T> *result, SCompTreeNode<T> *mergee);
		/// changes layout of the attributes from the one used during the build process to the final one (see description of this class)
		virtual void BuildingFinished(SCompTreeNode<T> *node);
		/// prints height, area and volume into the output stream
		virtual void PrintAttrib(std::ostream &ost, const SCompTreeNode<T> *node);

		/// sets parent of the given node
		void SetParent(SCompTreeNode<T> *node, SCompTreeNode<T> *parent);
		/// returns parent of the given node
		SCompTreeNode<T> *GetParent(const SCompTreeNode<T> *node);
		/// sets height of the given node
		void SetHeight(SCompTreeNode<T> *node, T height);
		/// returns height of the given node
		T GetHeight(const SCompTreeNode<T> *node);
		/// sets area of the given node
		void SetArea(SCompTreeNode<T> *node, size_t area);
		/// reutrns area of the given node
		size_t GetArea(const SCompTreeNode<T> *node);
		/// sets volume of the given node
		void SetVolume(SCompTreeNode<T> *node, size_t volume);
		/// returns volume of the given node
		size_t GetVolume(const SCompTreeNode<T> *node);
	
	private:
		/// indicates we are in the midle of the build process
		bool building;
		/// sets height of the given node
		void SetHighestBuild(SCompTreeNode<T> *node, T highest);
		/// returns height of the given node
		T GetHighestBuild(const SCompTreeNode<T> *node);
		/// sets area of the given node
		void SetAreaBuild(SCompTreeNode<T> *node, size_t area);
		/// reutrns area of the given node
		size_t GetAreatBuild(const SCompTreeNode<T> *node);
	};

	/// Representation of the component tree
	template <typename T>
	struct I3D_ALGO_EXPORT SCompTree
	{
		/// constructor that initializes default parameters
		SCompTree(CCompTreeNodeAttribHandler<T> *atribHandler = NULL);
		/// destructor that frees all the allocated resources
		virtual ~SCompTree();

		/// root node of the tree
		SCompTreeNode<T> *root;
		/// mapping of the voxels to the nodes - array of the pointers that for each voxel maps it's (highest) component from the tree (it is an array of inputImage.GetImageSize() pointers to the SCompTreeNode<T>)
		SCompTreeNode<T> **mapping;
		/// attribute handler used to manipulate attributes of the nodes
		CCompTreeNodeAttribHandler<T> *atribHandler;
	};

	/// Prints subtree rooted at compTreeNode into the ost
	template <typename T>
	I3D_ALGO_EXPORT void PrintSCompTreeNode(std::ostream &ost, const SCompTreeNode<T> *compTreeNode, CCompTreeNodeAttribHandler<T> *atribHandler, size_t level);
	/// Output operator that visualizes an instance of the SCompTree
	template <typename T>
	I3D_ALGO_EXPORT std::ostream& operator<<(std::ostream &ost, const SCompTree<T> &compTree);
	/// Output operator that visualizes an instance of the SCompTree
	template <typename T>
	I3D_ALGO_EXPORT std::ostream& operator<<(std::ostream &ost, const SCompTree<T> *compTree);

	/** Component tree (tree organization of the connected components of the level sets) construction algorithm according to Najman et al.
	Detailed description of the algorithm can be found in
	Najman, L.; Couprie, M., "Building the Component Tree in Quasi-Linear Time," Image Processing, IEEE Transactions on , vol.15, no.11, pp.3531-3539, Nov. 2006.
	\param [in] input the input image
	\param [out] componentTree component tree representing the whole given image
	\param [in] neighbourhood the neighbourhood used for the adjacency relation
	*/
	template <typename T> 
	I3D_ALGO_EXPORT void BuildComponentTree(const Image3d<T> &input, SCompTree<T> &componentTree, const Neighbourhood &neighbourhood);

	/** Component tree (tree organization of the connected components of the level sets) construction algorithm according to Najman et al.
	Detailed description of the algorithm can be found in
	Najman, L.; Couprie, M., "Building the Component Tree in Quasi-Linear Time," Image Processing, IEEE Transactions on , vol.15, no.11, pp.3531-3539, Nov. 2006.
	\param [in] input the input image
	\param [out] componentTree component tree representing the whole given image
	\param [in] NeighbourhoodWalker the neighbourhood walker representing the neighbourhood used for the adjacency relation (has to be configured for the given input size)
	*/
	template <typename T> 
	I3D_ALGO_EXPORT void BuildComponentTree(const Image3d<T> &input, SCompTree<T> &componentTree, NeighbourhoodWalker &nbhWalker);

	///@} end of morph group part

} // namespace i3d

#endif // #ifndef __COMPONENT_TREE_H__
