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
 * FILE: i3dcore_config.h.in
 *
 * configuration file
 *
 * David Svoboda <svoboda@fi.muni.cz> 2005
 * 
 */

/*
 * These ugly #ifdef, #define, #endif structures had to be introduced in order to
 * preserve original names of macros in the i3d source files while to be able to
 * use the new macros in CMake.
 *
 * Vladimir Ulman <xulman@fi.muni.cz>, 2008.
 */

/* sstream file is present */
#define HAVE_SSTREAM
#ifdef HAVE_SSTREAM
  #define SSTREAM
#endif

/* Lapack library is present */
#define ALGO_WITH_LAPACK
#ifdef ALGO_WITH_LAPACK
  #define WITH_LAPACK
#endif

/* Blas library is present */
#define ALGO_WITH_BLAS
#ifdef ALGO_WITH_BLAS
  #define WITH_BLAS
#endif

/* fftw library is present */
#define ALGO_WITH_FFTW
#ifdef ALGO_WITH_FFTW
  #define WITH_FFTW
#endif

/* support JPEG image format */
#define CORE_WITH_JPEG
#ifdef CORE_WITH_JPEG
  #define WITH_JPEG
#endif

/* support PNG image format */
#define CORE_WITH_PNG
#ifdef CORE_WITH_PNG
  #define WITH_PNG
#endif

/* support HDF5 image format */
/* #undef CORE_WITH_HDF5 */
#ifdef CORE_WITH_HDF5
  #define WITH_HDF5
#endif

/* support TIFF image format */
#define CORE_WITH_TIFF
#ifdef CORE_WITH_TIFF
  #define WITH_TIFF
#endif

/* support DICOM image format */
/* #undef CORE_WITH_DCM */
#ifdef CORE_WITH_DCM
  #define WITH_DCM
#endif

/* support TARGA image format */
#define CORE_WITH_TARGA
#ifdef CORE_WITH_TARGA
  #define WITH_TARGA
#endif

/* support METAIO image format */
#define CORE_WITH_METAIO
#ifdef CORE_WITH_METAIO
  #define WITH_METAIO
#endif

/* support ICS image format */
#define CORE_WITH_ICS
#ifdef CORE_WITH_ICS
  #define WITH_ICS
#endif

/* support regular expressions */
#define CORE_WITH_REGEX
#ifdef CORE_WITH_REGEX
	#define WITH_REGEX
#endif	

/* shared libraries... */
/* #undef ALGO_BUILD_SHARED_LIBS */
/* #undef CORE_BUILD_SHARED_LIBS */

/* BioFormats */
/* #undef CORE_WITH_BIOFORMATS */

/* multithreading */
/* #undef WITH_MULTITHREADING */

