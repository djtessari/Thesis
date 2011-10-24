///////////////////////////////////////////////////////////////////////////////
//
// SVDFit.inl
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

template <class REAL>
void SVDFit (GXMatrixMNTC<REAL>& A, 
             GXMatrixMNTC<REAL>& vals,
             GXMatrixMNTC<REAL>& coeffs)
{
    GXMatrixMNTC<REAL> u, w, vt;
    unsigned int       m, n, min;

    m = A.Rows();
    n = A.Cols();

    min = (m < n) ? m : n;

    coeffs.SetDim (n,1);

    u.SetDim (m,min,0.0);

    w.SetDim (min, 1, 0.0);

    vt.SetDim (min,n,0.0);

//    num_svd<REAL> (A.Data(), m, n, u.Data(), w.Data(), vt.Data());
num_svd (A.Data(), m, n, u.Data(), w.Data(), vt.Data());
    REAL wmax = ((REAL) 0.0f), 
         threshold;

    for (unsigned int i = 0, cCount = w.Rows() ; i < cCount ; i++)
        wmax = (wmax > w(i,0)) ? wmax : w(i,0);

    threshold = wmax * ((REAL) 1.0e-5);

//    num_svd_backsubst<REAL> (m,n,u.Data(),w.Data(),vt.Data(),
//                             vals.Data(),coeffs.Data(),threshold);
num_svd_backsubst (m,n,u.Data(),w.Data(),vt.Data(),
                             vals.Data(),coeffs.Data(),threshold);
}


template <class REAL>
void SVDMat(GXMatrixMNTC<REAL>& A, // input - matrix to apply SVD too...
            GXMatrixMNTC<REAL>& u, // output - SVD of matrix A...
            GXMatrixMNTC<REAL>& w,
            GXMatrixMNTC<REAL>& vt)
{
    unsigned int       m, n, min;
    
    m = A.Rows();
    n = A.Cols();
    
    min = (m < n) ? m : n;
    
    u.SetDim (m,min,0.0);
    
    w.SetDim (min, 1, 0.0);
    
    vt.SetDim (min,n,0.0);
    
    num_svd<REAL> (A.Data(), m, n, u.Data(), w.Data(), vt.Data());
}

template <class REAL>
void SVDApply(GXMatrixMNTC<REAL>& u, // input SVD of a matrix
              GXMatrixMNTC<REAL>& w,
              GXMatrixMNTC<REAL>& vt,
              GXMatrixMNTC<REAL>& vals,  // input RHS
              GXMatrixMNTC<REAL>& coeffs)// output x from Ax=b 
{
    unsigned int       m, n, min;
    
    m = u.Rows();
    n = vt.Cols();
    
    min = (m < n) ? m : n;
    
    coeffs.SetDim (n,1);
    
    REAL wmax = ((REAL) 0.0f), 
        threshold;
    
    for (unsigned int i = 0, cCount = w.Rows() ; i < cCount ; i++)
        wmax = (wmax > w(i,0)) ? wmax : w(i,0);
    
    threshold = wmax * ((REAL) 1.0e-5);
    
    num_svd_backsubst<REAL> (m,n,u.Data(),w.Data(),vt.Data(),
                             vals.Data(),coeffs.Data(),threshold);
}
