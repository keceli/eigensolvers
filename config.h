/*
   Copyright (c) 2009-2013, Jack Poulson
   All rights reserved.

   This file is part of Elemental and is under the BSD 2-Clause License, 
   which can be found in the LICENSE file in the root directory, or at 
   http://opensource.org/licenses/BSD-2-Clause
*/
#ifndef EL_CONFIG_H
#define EL_CONFIG_H

/* Build type and version information */
#define EL_GIT_SHA1 "92c9ddf77c8a759ffeede62d912a98535a5deb8f"
#define EL_VERSION_MAJOR "0"
#define EL_VERSION_MINOR "85-dev"
#define EL_CMAKE_BUILD_TYPE "PureRelease"
#define EL_RELEASE

/* C compiler info */
#define EL_CMAKE_C_COMPILER    "/home/projects/llvm/wbin/bgclang"
#define EL_MPI_C_COMPILER      "/home/projects/llvm/mpi/bgclang/bin/mpiclang"
#define EL_MPI_C_INCLUDE_PATH  "/bgsys/drivers/ppcfloor/comm/include"
#define EL_MPI_C_COMPILE_FLAGS ""
#define EL_MPI_C_LINK_FLAGS    "-L/bgsys/drivers/ppcfloor/comm/lib -L/bgsys/drivers/ppcfloor/comm/sys/lib -L/bgsys/drivers/ppcfloor/spi/lib"
#define EL_MPI_C_LIBRARIES     "-L/bgsys/drivers/ppcfloor/comm/lib -L/bgsys/drivers/ppcfloor/comm/sys/lib -L/bgsys/drivers/ppcfloor/spi/lib   -lmpich-gcc -lopa-gcc -lmpl-gcc -lpami-gcc -lSPI -lSPI_cnk -lrt -lpthread -lstdc++ -lpthread"

/* C++ compiler info */
#define EL_CMAKE_CXX_COMPILER    "/home/projects/llvm/wbin/bgclang++11"
#define EL_CXX_FLAGS             "-O3 -std=c++11 "
#define EL_MPI_CXX_COMPILER      "/home/projects/llvm/mpi/bgclang/bin/mpiclang++11"
#define EL_MPI_CXX_INCLUDE_PATH  "/bgsys/drivers/ppcfloor/comm/include"
#define EL_MPI_CXX_COMPILE_FLAGS ""
#define EL_MPI_CXX_LINK_FLAGS    "-L/bgsys/drivers/ppcfloor/comm/lib -L/bgsys/drivers/ppcfloor/comm/sys/lib -L/bgsys/drivers/ppcfloor/spi/lib"
#define EL_MPI_CXX_LIBRARIES     "-L/bgsys/drivers/ppcfloor/comm/lib -L/bgsys/drivers/ppcfloor/comm/sys/lib -L/bgsys/drivers/ppcfloor/spi/lib -lmpichcxx-gcc -L/bgsys/drivers/ppcfloor/comm/lib -L/bgsys/drivers/ppcfloor/comm/sys/lib -L/bgsys/drivers/ppcfloor/spi/lib   -lmpich-gcc -lopa-gcc -lmpl-gcc -lpami-gcc -lSPI -lSPI_cnk -lrt -lpthread -lstdc++ -lpthread"

/* Math libraries */
#define EL_MATH_LIBS "-L/soft/libraries/essl/current/essl/5.1/lib64 -lesslbg -L/soft/libraries/alcf/current/xl/LAPACK/lib -llapack -L/soft/libraries/essl/current/essl/5.1/lib64 -lesslbg -L/soft/compilers/ibmcmp-aug2014/xlf/bg/14.1/bglib64 -lxlf90_r -L/soft/compilers/ibmcmp-aug2014/xlsmp/bg/3.1/bglib64 -lxlomp_ser -lxlopt -lxlfmath -lxl -lpthread -ldl -Wl,--allow-multiple-definition"
/* #undef EL_BLAS_POST */
/* #undef EL_LAPACK_POST */
/* #undef EL_HAVE_SCALAPACK */
/* #undef EL_SCALAPACK_POST */
/* #undef EL_HAVE_FLA_BSVD */
#define EL_FORT_LOGICAL int
#define EL_FORT_TRUE    1
#define EL_FORT_FALSE   0

/* Basic configuration options */
#define EL_RESTRICT __restrict__
/* #undef EL_HAVE_OPENMP */
/* #undef EL_HAVE_OMP_COLLAPSE */
/* #undef EL_HAVE_QT5 */
#define EL_HAVE_F90_INTERFACE
#define EL_AVOID_COMPLEX_MPI
#define EL_HAVE_CXX11RANDOM
#define EL_HAVE_STEADYCLOCK
#define EL_HAVE_NOEXCEPT
#define EL_HAVE_MPI_REDUCE_SCATTER_BLOCK
#define EL_HAVE_MPI_IN_PLACE
#define EL_HAVE_MPI_LONG_LONG
#define EL_HAVE_MPI_COMM_SET_ERRHANDLER
#define EL_HAVE_MPI_INIT_THREAD
#define EL_HAVE_MPI_QUERY_THREAD
/* #undef EL_HAVE_MPI3_NONBLOCKING_COLLECTIVES */
#define EL_HAVE_MPIX_NONBLOCKING_COLLECTIVES
/* #undef EL_REDUCE_SCATTER_BLOCK_VIA_ALLREDUCE */
#define EL_USE_BYTE_ALLGATHERS
/* #undef EL_USE_64BIT_INTS */

/* Advanced configuration options */
/* #undef EL_ZERO_INIT */
/* #undef EL_CACHE_WARNINGS */
/* #undef EL_UNALIGNED_WARNINGS */
/* #undef EL_VECTOR_WARNINGS */
/* #undef EL_POOL_MEMORY */
/* #undef EL_AVOID_OMP_FMA */

/* NOTE: Only EL_DISABLE_FLOAT has been tested so far */
/* #undef EL_DISABLE_FLOAT */
/* #undef EL_DISABLE_DOUBLE */
/* #undef EL_DISABLE_COMPLEX */

/* #undef EL_HAVE_VALGRIND */

#endif /* EL_CONFIG_H */
