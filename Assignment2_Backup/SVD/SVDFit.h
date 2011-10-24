///////////////////////////////////////////////////////////////////////////////
//
// SVDFit.h
//
// Copyright Microsoft Corporation
//
// Microsoft Research Graphics Group
// Kineform Project
//
// Abstract: Header for SVDFit routine.  This wraps up the lower level SVD 
//           stuff from Ronen Barzel.  This is the leve of abstraction used
//           by the outside system.
//
// Revision History Abstract:
// 21May1996 ChuckR    Initial code start
// 13Apr1999 ChuckR    Templatize and conform to Kineform project style
// 25Jul1999 ppsloan   SVDMat/Apply added - for saving the SVD of a matrix
///////////////////////////////////////////////////////////////////////////////

#ifndef _032E05C3_F193_11d2_B8F2_00C04F6881C7
#define _032E05C3_F193_11d2_B8F2_00C04F6881C7

#include "MatrixMNTC.h"

#include "SVD.h"

template <class REAL>
void SVDFit (GXMatrixMNTC<REAL>& A, GXMatrixMNTC<REAL>& vals,
             GXMatrixMNTC<REAL>& coeffs);

template <class REAL>
void SVDMat(GXMatrixMNTC<REAL>& A, // input - matrix to apply SVD too...
            GXMatrixMNTC<REAL>& u, // output - SVD of matrix A...
            GXMatrixMNTC<REAL>& w,
            GXMatrixMNTC<REAL>& vt);

template <class REAL>
void SVDApply(GXMatrixMNTC<REAL>& u, // input SVD of a matrix
              GXMatrixMNTC<REAL>& w,
              GXMatrixMNTC<REAL>& vt,
              GXMatrixMNTC<REAL>& vals,  // input RHS
              GXMatrixMNTC<REAL>& coefs);// output x from Ax=b 

#include "SVDFit.inl"

#endif
