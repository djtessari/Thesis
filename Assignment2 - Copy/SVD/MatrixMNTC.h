///////////////////////////////////////////////////////////////////////////////
//
// MatrixMNTC.h 
//
// Copyright Microsoft Corporation
//
// Microsoft Research Graphics Group
// Kineform Project
//
// Abstract: An mxn matrix class for Luciform / Kineform
//
// Revision History Abstract:
// 03Apr1999 ChuckR    Initial code start
///////////////////////////////////////////////////////////////////////////////

#ifndef _129E7523_AADB_11d2_B8F2_00C04F6881C7
#define _129E7523_AADB_11d2_B8F2_00C04F6881C7

#define OS_UNIX 1
#define OS_WINNT 2

#ifndef WIN32
#define USE_UNIX
#endif

#ifdef USE_UNIX
#   define OS OS_UNIX
#else
#   define OS OS_WINNT
#endif

#if OS == OS_WINNT
#include <comdef.h>
#else
#include "comdef.h"
#endif

template <class Coord> class GXMatrixMNTC {

public:

    GXMatrixMNTC (void);
    GXMatrixMNTC (unsigned int cRows, unsigned int cCols);
    GXMatrixMNTC (unsigned int cRows, unsigned int cCols, const Coord& initializeTo);
    GXMatrixMNTC (const GXMatrixMNTC<Coord>& toCopy);

    ~GXMatrixMNTC (void);

    void SetDim (unsigned int cRows, unsigned int cCols);
    void SetDim (unsigned int cRows, unsigned int cCols, const Coord& initializeTo);

    void Init (const Coord& initializeTo);

    unsigned int Rows (void) const;
    unsigned int Cols (void) const;

    bool IsSquare (void) const;
    bool IsDiagonal (void) const;
    bool IsScalar (void) const;
    bool IsSymmetric (void) const;
    bool IsAntiSymmetric (void) const;

    Coord* Data (void);

    const Coord& operator() (unsigned int iRow, unsigned int iCol) const;
    Coord& operator() (unsigned int iRow, unsigned int iCol);

    const GXMatrixMNTC<Coord>& operator= (const GXMatrixMNTC<Coord>& toCopy);

    const GXMatrixMNTC<Coord>& operator+= (const GXMatrixMNTC<Coord>& toAdd);
    const GXMatrixMNTC<Coord>& operator-= (const GXMatrixMNTC<Coord>& toAdd);
    const GXMatrixMNTC<Coord>& operator*= (Coord s);
    const GXMatrixMNTC<Coord>& operator/= (Coord s);

	/*
    friend GXMatrixMNTC<Coord> operator+ (const GXMatrixMNTC<Coord>& A, 
                                          const GXMatrixMNTC<Coord>& B);
    friend GXMatrixMNTC<Coord> operator- (const GXMatrixMNTC<Coord>& A, 
                                          const GXMatrixMNTC<Coord>& B);
    friend GXMatrixMNTC<Coord> operator* (const GXMatrixMNTC<Coord>& A,
                                          const GXMatrixMNTC<Coord>& B);
    friend GXMatrixMNTC<Coord> operator* (const GXMatrixMNTC<Coord>& M, Coord s);
    friend GXMatrixMNTC<Coord> operator* (Coord s, const GXMatrixMNTC<Coord>& M);
    friend GXMatrixMNTC<Coord> operator/ (const GXMatrixMNTC<Coord>& M, Coord s);

    friend GXMatrixMNTC<Coord> operator+ (const GXMatrixMNTC<Coord>& M);
    friend GXMatrixMNTC<Coord> operator- (const GXMatrixMNTC<Coord>& M);

    friend bool operator == (const GXMatrixMNTC<Coord>& A, 
                             const GXMatrixMNTC<Coord>& B);
    friend bool operator != (const GXMatrixMNTC<Coord>& A, 
                             const GXMatrixMNTC<Coord>& B);

    friend const GXMatrixMNTC<Coord> Transpose (const GXMatrixMNTC<Coord>& M);
    friend const GXMatrixMNTC<Coord> Identity (unsigned int cOrder);
    friend const GXMatrixMNTC<Coord> ScalarMatrix (unsigned int cOrder, Coord s);
	*/

protected:

    Coord*         m_pElements;
    unsigned int   m_cRows,
                   m_cCols;

private:

    const Coord& Get (unsigned int i, unsigned int j) const;

};

template <class Coord>
GXMatrixMNTC<Coord> operator+ (const GXMatrixMNTC<Coord>& A,const GXMatrixMNTC<Coord>& B);
template <class Coord>
GXMatrixMNTC<Coord> operator- (const GXMatrixMNTC<Coord>& A,const GXMatrixMNTC<Coord>& B);
template <class Coord>
GXMatrixMNTC<Coord> operator* (const GXMatrixMNTC<Coord>& A,const GXMatrixMNTC<Coord>& B);
template <class Coord>
GXMatrixMNTC<Coord> operator* (const GXMatrixMNTC<Coord>& M, Coord s);
template <class Coord>
GXMatrixMNTC<Coord> operator* (Coord s, const GXMatrixMNTC<Coord>& M);
template <class Coord>
GXMatrixMNTC<Coord> operator/ (const GXMatrixMNTC<Coord>& M, Coord s);
template <class Coord>
GXMatrixMNTC<Coord> operator+ (const GXMatrixMNTC<Coord>& M);
template <class Coord>
GXMatrixMNTC<Coord> operator- (const GXMatrixMNTC<Coord>& M);
template <class Coord>
bool operator == (const GXMatrixMNTC<Coord>& A,const GXMatrixMNTC<Coord>& B);
template <class Coord>
bool operator != (const GXMatrixMNTC<Coord>& A,const GXMatrixMNTC<Coord>& B);
template <class Coord>
const GXMatrixMNTC<Coord> Transpose (const GXMatrixMNTC<Coord>& M);
template <class Coord>
const GXMatrixMNTC<Coord> Identity (unsigned int cOrder);
template <class Coord>
const GXMatrixMNTC<Coord> ScalarMatrix (unsigned int cOrder, Coord s);


typedef GXMatrixMNTC<float> GXMatrixMNf;
typedef GXMatrixMNTC<double> GXMatrixMNd;

#include "MatrixMNTC.inl"


#endif //_129E7523_AADB_11d2_B8F2_00C04F6881C7

