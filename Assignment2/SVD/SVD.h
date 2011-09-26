///////////////////////////////////////////////////////////////////////////////
//
// SVD.h
//
// Abstract:  Singular-Value Decomposition.  Numerous informative comments 
//            througout code.
//
// Revision History Abstract:
// xxJul1989 Ronen Barzel    Initial code
// xxFeb1990 Ronen Barzel    Bug fixes
// xxMay1993 Ronen Barzel    ANSI-C backsubst
// 21Jul1997 ChuckR          Fix array bound error in underdetermined case
// 13Apr1999 ChuckR          Templatize and decryptify the code (somewhat)
///////////////////////////////////////////////////////////////////////////////

#ifndef _032E05C2_F193_11d2_B8F2_00C04F6881C7
#define _032E05C2_F193_11d2_B8F2_00C04F6881C7


template <class REAL>
    void num_svd(const REAL *a,int m,int n,REAL *u,REAL *w,REAL *vt);

template <class REAL>
    void num_svd_backsubst(int m, int n, const REAL *u, const REAL *w, const REAL *vt,
		                   const REAL b[], REAL x[], REAL eps);


#include "SVD.inl"

#endif // _032E05C2_F193_11d2_B8F2_00C04F6881C7
