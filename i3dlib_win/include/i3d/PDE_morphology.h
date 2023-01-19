/*
 * PDEmorphology.h
 *
 * Computes basic morphology operations using PDE.
 *
 * Pavel Matula (pam@fi.muni.cz) 2007
 */

#ifndef __PDE_MORPHOLOGY_H__
#define __PDE_MORPHOLOGY_H__

#include "basic.h"
#include "image3d.h"
#include "algo_export.h"

namespace i3d {

	template <class FLOATING_VOXEL> class PDE_ExplicitSolver {
	protected:
		Image3d<FLOATING_VOXEL> *_img;		//< input/output image
		Image3d<FLOATING_VOXEL> *_buf1;		//< auxiliary image buffer (with border)
		Image3d<FLOATING_VOXEL> *_buf2;		//< auxiliary image buffer (with border)
		FLOATING_VOXEL	_tau;				//< time step required
		size_t			_num_iters;			//< number of iterations required 
		size_t			_border;			//< image border in pixels


		/** init buffers */
		void InitBuffers();
		/** release memory occupied by buffers */
		void ReleaseBuffers();

		/** reflect boundaries in given buffer */
		void ReflectBoundary(Image3d<FLOATING_VOXEL> *img);

		/** copies the given buffer into image _img. Buffer border is not copied */
		void BufferToImage(const Image3d<FLOATING_VOXEL> *buf);

		/** copies image _img into given buffer. Buffer border is not changed */
		void ImageToBuffer(Image3d<FLOATING_VOXEL> *buf);

		/**
			prepare boundary conditions
		*/
		virtual void PrepareBoundaryCondition(Image3d<FLOATING_VOXEL> *img) = 0;

		/**
			perform one explicit step 
		*/
		virtual void ExecuteExplicitStep(Image3d<FLOATING_VOXEL> *img_in, Image3d<FLOATING_VOXEL> *img_out) = 0;
	public:
		PDE_ExplicitSolver(size_t border, Image3d<FLOATING_VOXEL> *img = NULL): _img(img), _buf1(NULL), _buf2(NULL), _tau(0.1f), _num_iters(0), _border(border) {};
		virtual ~PDE_ExplicitSolver() {};
		void SetImage(Image3d<FLOATING_VOXEL> *img) { _img = img; };
		void SetTau(FLOATING_VOXEL tau) { _tau = tau; };
		void SetNumIters(size_t num_iters) { _num_iters = num_iters; };
		void Execute();
	};
	
/**
	\brief Compute grayscale dilation with spherical structural element using PDE
		The main advantage is that the sphere radius can be set with "subpixel" accuracy.
		Simple (slow) explicit solution is implemented at this moment.
		Computational time linearly increases with element radius.
		The radius is equal to num_iters * tau. 
		tau should be small (< 0.25) for stable computation. Smaller tau leads to more accurate result 
		but in longer time.

		Example:
			Image3d<float> img;
			img.ReadImage("input.ics");

			PDE_Dilation solver(&img);
			solver.SetTau(0.1);
			solver.SetNumIters(15); // leads to dilation with sphere having radius of 1.5 pixels
			solver.Execute();       // start computation

			img.SaveImage("result.ics");
*/
	template <class FLOATING_VOXEL> class I3D_ALGO_EXPORT PDE_Dilation: public PDE_ExplicitSolver<FLOATING_VOXEL> {
		virtual void PrepareBoundaryCondition(Image3d<FLOATING_VOXEL> *img);
		virtual void ExecuteExplicitStep(Image3d<FLOATING_VOXEL> *img_in, Image3d<FLOATING_VOXEL> *img_out);
	public:
		PDE_Dilation(Image3d<FLOATING_VOXEL> *in = NULL) : PDE_ExplicitSolver<FLOATING_VOXEL>(1, in) {};
	};

/**
	\brief Compute grayscale erosion with spherical structural element using PDE
		The main advantage is that the sphere radius can be set with "subpixel" accuracy.
		Simple (slow) explicit solution is implemented at this moment.
		Computational time linearly increases with element radius.
		The radius is equal to num_iters * tau. 
		tau should be small (< 0.25) for stable computation. Smaller tau leads to more accurate result 
		but in longer time.

		Example:
			Image3d<float> img;
			img.ReadImage("input.ics");

			PDE_Erosion solver(&img);
			solver.SetTau(0.1);
			solver.SetNumIters(15); // leads to erosion with sphere having radius of 1.5 pixels
			solver.Execute();       // start computation

			img.SaveImage("result.ics");
*/
	template <class FLOATING_VOXEL> class I3D_ALGO_EXPORT PDE_Erosion: public PDE_ExplicitSolver<FLOATING_VOXEL> {
		virtual void PrepareBoundaryCondition(Image3d<FLOATING_VOXEL> *img);
		virtual void ExecuteExplicitStep(Image3d<FLOATING_VOXEL> *img_in, Image3d<FLOATING_VOXEL> *img_out);
	public:
		PDE_Erosion(Image3d<FLOATING_VOXEL> *in = NULL) : PDE_ExplicitSolver<FLOATING_VOXEL>(1, in) {};
	};

}

#endif
