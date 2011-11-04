///////////////////////////////////////////////////////////////////////////////
//
// MatrixMNTC.inl
//
// Copyright Microsoft Corporation
//
// Microsoft Research Graphics Group
// Kineform Project
//
// Abstract: An mxn matrix class for luciform / kineform
//
// Revision History Abstract:
// 03Apr1999 ChuckR    Initial code start
///////////////////////////////////////////////////////////////////////////////

#define OS_UNIX 1
#define OS_WINNT 2

#ifdef USE_UNIX
#   define OS OS_UNIX
#else
#   define OS OS_WINNT
#endif


template <class Coord>
    GXMatrixMNTC<Coord>::GXMatrixMNTC (void) : m_pElements (NULL),
                                               m_cRows (0),
                                               m_cCols (0)
{
}

template <class Coord>
    GXMatrixMNTC<Coord>::GXMatrixMNTC (unsigned int cRows, unsigned int cCols) 
{
    unsigned int cTotalSize = cRows * cCols;

    if (cTotalSize > 0)
    {
        m_pElements = new Coord[cTotalSize];

        if (!m_pElements)
            throw _com_error(E_OUTOFMEMORY);
    }

    m_cRows = cRows;
    m_cCols = cCols;
}

template <class Coord>
    GXMatrixMNTC<Coord>::GXMatrixMNTC (unsigned int cRows, unsigned int cCols, const Coord& initializeTo)
{
    unsigned int cTotalSize = cRows * cCols;

    if (cTotalSize > 0)
    {
        m_pElements = new Coord[cTotalSize];

        if (!m_pElements)
            throw _com_error(E_OUTOFMEMORY);
    }

    m_cRows = cRows;
    m_cCols = cCols;

    for (unsigned int i = 0 ; i < (cRows * cCols) ; i++)
        m_pElements[i] = initializeTo;
}

template <class Coord>
    GXMatrixMNTC<Coord>::GXMatrixMNTC (const GXMatrixMNTC<Coord>& toCopy) 
{
    unsigned int cTotalSize = toCopy.m_cRows * toCopy.m_cCols;

    if (cTotalSize > 0)
    {
        m_pElements = new Coord[cTotalSize];

        if (!m_pElements)
            throw _com_error(E_OUTOFMEMORY);
    }

    m_cRows = toCopy.m_cRows;
    m_cCols = toCopy.m_cCols;

    for (unsigned int i = 0 ; i < cTotalSize ; i++)
        m_pElements[i] = toCopy.m_pElements[i];
}

template <class Coord>
    GXMatrixMNTC<Coord>::~GXMatrixMNTC (void)
{
    if (m_pElements)
        delete[] m_pElements;
}

template <class Coord>
    inline unsigned int GXMatrixMNTC<Coord>::Cols (void) const
{
    return m_cCols;
}

template <class Coord>
    inline Coord* GXMatrixMNTC<Coord>::Data (void)
{
    return m_pElements;
}

template <class Coord>
    inline const Coord& GXMatrixMNTC<Coord>::Get (unsigned int i, unsigned int j) const
{
    return m_pElements [j + (i * m_cCols)];
}

template <class Coord>
    void GXMatrixMNTC<Coord>::Init (const Coord& initializeTo)
{
    for (unsigned int i = 0, cCount = m_cRows * m_cCols ; i < cCount ; i++)
        m_pElements[i] = initializeTo;
}

template <class Coord>
    bool GXMatrixMNTC<Coord>::IsAntiSymmetric (void) const
{
    if ((m_cRows != 0) || (m_cRows != m_cCols))
        return false;

    for (unsigned int i = 0 ; i < m_cRows ; i++)
        for (unsigned int j = 0 ; j <= i ; j++)
            if ((i != j) && (Get(i,j) != -Get(j,i)))
                return false;
            else if ((i == j) && (Get(i,i) != 0))
                return false;

    return true;
}

template <class Coord>
    bool GXMatrixMNTC<Coord>::IsDiagonal (void) const
{
    if ((m_cRows == 0) || (m_cCols != m_cRows))
        return false;

    for (unsigned int i = 0 ; i < m_cRows ; i++)
        for (unsigned int j = 0 ; j < m_cCols ; j++)
            if ((i != j) && (Get(i,j) != 0))
                return false;

    return true;
}

template <class Coord>
    bool GXMatrixMNTC<Coord>::IsScalar (void) const
{
    if ((m_cRows == 0) || (m_cCols != m_cRows))
        return false;

    Coord val = Get(0,0);

    for (unsigned int i = 0 ; i < m_cRows ; i++)
        for (unsigned int j = 0 ; j < m_cCols ; j++)
            if (((i != j) && (Get(i,j) != 0)) 
                || 
                ((i == j) && (Get(i,j) != val)))
                return false;

    return true;
}

template <class Coord>
    bool GXMatrixMNTC<Coord>::IsSquare (void) const
{
    return ((m_cRows != 0) && (m_cRows == m_cCols));
}

template <class Coord>
    bool GXMatrixMNTC<Coord>::IsSymmetric (void) const
{
    if ((m_cRows == 0) || (m_cRows != m_cCols))
        return false;

    for (unsigned int i = 0 ; i < m_cRows ; i++)
        for (unsigned int j = 0 ; j <= i ; j++)
            if (Get(i,j) != Get(j,i))
                return false;

    return true;
}

template <class Coord>
    inline unsigned int GXMatrixMNTC<Coord>::Rows (void) const
{
    return m_cRows;
}

template <class Coord>
    void GXMatrixMNTC<Coord>::SetDim (unsigned int cRows, unsigned int cCols)
{
    unsigned int cTotalSize = cRows * cCols;

    if (m_pElements)
    {
        delete[] m_pElements;
    }

    if (cTotalSize > 0)
    {
        m_pElements = new Coord[cTotalSize];

        if (!m_pElements)
            throw _com_error(E_OUTOFMEMORY);
    }
    else
        m_pElements = NULL;

    m_cRows = cRows;
    m_cCols = cCols;
}

template <class Coord>
    void GXMatrixMNTC<Coord>::SetDim (unsigned int cRows, unsigned int cCols, const Coord& initializeTo)
{
    unsigned int cTotalSize = cRows * cCols;

    if (m_pElements)
    {
        delete[] m_pElements;
    }

    if (cTotalSize > 0)
    {
        m_pElements = new Coord[cTotalSize];

        if (!m_pElements)
            throw _com_error(E_OUTOFMEMORY);
    }
    else
        m_pElements = NULL;

    m_cRows = cRows;
    m_cCols = cCols;

    for (unsigned int i = 0 ; i < cTotalSize ; i++)
        m_pElements[i] = initializeTo;
}

//////// member operators /////////////////////////////////////////////////

template <class Coord>
    const GXMatrixMNTC<Coord>& GXMatrixMNTC<Coord>::operator= (const GXMatrixMNTC<Coord>& toCopy)
{
    unsigned int cTotalSize = toCopy.m_cRows * toCopy.m_cCols;

    if (m_pElements)
    {
        delete[] m_pElements;
    }

    if (cTotalSize > 0)
    {
        m_pElements = new Coord[cTotalSize];

        if (!m_pElements)
            throw _com_error(E_OUTOFMEMORY);
    }
    else
        m_pElements = NULL;

    m_cRows = toCopy.m_cRows;
    m_cCols = toCopy.m_cCols;

    for (unsigned int i = 0 ; i < cTotalSize ; i++)
        m_pElements[i] = toCopy.m_pElements[i];

    return *this;
}


template <class Coord>
    const GXMatrixMNTC<Coord>& GXMatrixMNTC<Coord>::operator+= (const GXMatrixMNTC<Coord>& toAdd)
{
    if ((m_cRows != toAdd.m_cRows) || (m_cCols != toAdd.m_cCols))
        throw _com_error (E_INVALIDARG);

    for (unsigned int i = 0, cCount = m_cRows * m_cCols ; i < cCount ; i++)
        m_pElements[i] += toAdd.m_pElements[i];

    return *this;
}

template <class Coord>
    const GXMatrixMNTC<Coord>& GXMatrixMNTC<Coord>::operator-= (const GXMatrixMNTC<Coord>& toAdd)
{
    if ((m_cRows != toAdd.m_cRows) || (m_cCols != toAdd.m_cCols))
        throw _com_error (E_INVALIDARG);

    for (unsigned int i = 0, cCount = m_cRows * m_cCols ; i < cCount ; i++)
        m_pElements[i] -= toAdd.m_pElements[i];

    return *this;
}

template <class Coord>
    const GXMatrixMNTC<Coord>& GXMatrixMNTC<Coord>::operator*= (Coord s)
{
    for (unsigned int i = 0, cCount = m_cRows * m_cCols ; i < cCount ; i++)
        m_pElements[i] *= s;

    return *this;
}

template <class Coord>
    const GXMatrixMNTC<Coord>& GXMatrixMNTC<Coord>::operator/= (Coord s)
{
    if (s == ((Coord) 0.0f))
        throw _com_error (E_INVALIDARG);

    for (unsigned int i = 0, cCount = m_cRows * m_cCols ; i < cCount ; i++)
        m_pElements[i] /= s;

    return *this;
}

template <class Coord>
    inline const Coord& GXMatrixMNTC<Coord>::operator() (unsigned int iRow, unsigned int iCol) const
{
    if ((iRow >= m_cRows) || (iCol >= m_cCols))
        throw _com_error(E_INVALIDARG);

    return m_pElements[iCol + (m_cCols * iRow)];
}

template <class Coord>
    inline Coord& GXMatrixMNTC<Coord>::operator() (unsigned int iRow, unsigned int iCol) 
{
    if ((iRow >= m_cRows) || (iCol >= m_cCols))
        throw _com_error(E_INVALIDARG);

    return m_pElements[iCol + (m_cCols * iRow)];
}

// non-member operators ////////////////////////////////////////////////////////////////

template <class Coord>
    bool operator== (const GXMatrixMNTC<Coord>& A,
                     const GXMatrixMNTC<Coord>& B)
{
    if ((A.m_cRows != B.m_cRows) ||
        (A.m_cCols != B.m_cCols))
        return false;

    for (unsigned int i = 0, cCount = A.m_cRows * A.m_cCols ; i < cCount ; i++)
        if (A.m_pElements[i] != B.m_pElements[i])
            return false;

    return true;
}

template <class Coord>
    bool operator!= (const GXMatrixMNTC<Coord>& A,
                     const GXMatrixMNTC<Coord>& B)
{
    if ((A.m_cRows != B.m_cRows) ||
        (A.m_cCols != B.m_cCols))
        return true;

    for (unsigned int i = 0, cCount = A.m_cRows * A.m_cCols ; i < cCount ; i++)
        if (A.m_pElements[i] != B.m_pElements[i])
            return true;

    return false;
}

template <class Coord>
    GXMatrixMNTC<Coord> operator + (const GXMatrixMNTC<Coord>& A, const GXMatrixMNTC<Coord>& B)
{
    unsigned int cRows = A.m_cRows,
                 cCols = A.m_cCols;

    if ((cRows != B.m_cRows) || (cCols != B.m_cCols))
        throw _com_error (E_INVALIDARG);

    GXMatrixMNTC<Coord>  ApB (A);

    ApB += B;

    return ApB;
}

template <class Coord>
    GXMatrixMNTC<Coord> operator - (const GXMatrixMNTC<Coord>& A, const GXMatrixMNTC<Coord>& B)
{
    unsigned int cRows = A.m_cRows,
                 cCols = A.m_cCols;

    if ((cRows != B.m_cRows) || (cCols != B.m_cCols))
        throw _com_error (E_INVALIDARG);

    GXMatrixMNTC<Coord>  AmB (A);

    AmB -= B;

    return AmB;
}

template <class Coord>
    GXMatrixMNTC<Coord> operator * (const GXMatrixMNTC<Coord>& A, const GXMatrixMNTC<Coord>& B)
{
    unsigned int m (A.Rows()),
                 p (A.Cols()),
                 n (B.Cols()),
                 i,
                 j,
                 k;
    Coord        fTotal;

    if (p != B.Rows())
        throw _com_error (E_INVALIDARG);

    GXMatrixMNTC<Coord> AB (m,n);

    for (i = 0 ; i < m ; i++)
        for (j = 0 ; j < n ; j++)
        {
            fTotal = (Coord) 0.0f;

            for (k = 0 ; k < p ; k++)
                fTotal += A(i,k) * B(k,j);

            AB(i,j) = fTotal;
        }

    return AB;
}

template <class Coord>
    GXMatrixMNTC<Coord> operator * (const GXMatrixMNTC<Coord>& M, Coord s)
{
    GXMatrixMNTC<Coord> Ms(M);

    for (unsigned int i = 0, cCount = M.m_cRows * M.m_cCols ; i < cCount ; i++)
        Ms.m_pElements[i] *= s;
    
    return Ms;
}

template <class Coord>
    GXMatrixMNTC<Coord> operator * (Coord s, const GXMatrixMNTC<Coord>& M)
{
    GXMatrixMNTC<Coord> Ms(M);

    for (unsigned int i = 0, cCount = M.m_cRows * M.m_cCols ; i < cCount ; i++)
        Ms.m_pElements[i] *= s;
    
    return Ms;
}

template <class Coord>
    GXMatrixMNTC<Coord> operator / (const GXMatrixMNTC<Coord>& M, Coord s)
{
    if (s == ((Coord) 0.0f))
        throw _com_error (E_INVALIDARG);

    GXMatrixMNTC<Coord> Mds(M);

    for (unsigned int i = 0, cCount = M.m_cRows * M.m_cCols ; i < cCount ; i++)
        Mds.m_pElements[i] /= s;
    
    return Mds;
}

template <class Coord> 
    GXMatrixMNTC<Coord> operator - (const GXMatrixMNTC<Coord>& M)
{
    GXMatrixMNTC<Coord> Mneg (M);

    Mneg *= -1;

    return Mneg;
}

template <class Coord>
    GXMatrixMNTC<Coord> operator + (const GXMatrixMNTC<Coord>& M)
{
    return M;
}

//// non-member named functions ///////////////////////////////////////////

template <class Coord>
#if OS == OS_UNIX
    const GXMatrixMNTC<Coord> Identity (Coord cOrder)
#else
    const GXMatrixMNTC<Coord> Identity (unsigned int cOrder)
#endif
{
    if (cOrder == 0)
        throw _com_error (E_INVALIDARG);

    GXMatrixMNTC<Coord> I(cOrder,cOrder,(Coord) 0.0f);

    for (unsigned int i = 0 ; i < cOrder ; i++)
        I(i,i) = (Coord) 1.0f;

    return I;
}

template <class Coord>
    const GXMatrixMNTC<Coord> ScalarMatrix (unsigned int cOrder, Coord s)
{
    if (cOrder == 0)
        throw _com_error (E_INVALIDARG);

    GXMatrixMNTC<Coord> S(cOrder,cOrder,(Coord) 0.0f);

    for (unsigned int i = 0 ; i < cOrder ; i++)
        S(i,i) = s;

    return S;
}

template <class Coord>
    const GXMatrixMNTC<Coord> Transpose (const GXMatrixMNTC<Coord>& M)
{
    GXMatrixMNTC<Coord> Mt (M.m_cCols,M.m_cRows);

    for (unsigned int i = 0 ; i < M.m_cRows ; i++)
        for (unsigned int j = 0 ; j < M.m_cCols ; j++)
            Mt(j,i) = M(i,j);

    return Mt;
}
