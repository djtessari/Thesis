typedef long HRESULT;

enum {E_FAIL = 0, E_INVALIDARG, E_OUTOFMEMORY, S_OK};

class _com_error {

protected:

        HRESULT m_hr;

public:

        _com_error (HRESULT hr) {m_hr = hr;};

        HRESULT Error () { return m_hr; };
};
