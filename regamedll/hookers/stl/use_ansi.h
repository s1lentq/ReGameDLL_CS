#pragma once

#ifdef _MT
#ifdef _DLL
#ifdef _DEBUG
#pragma comment(lib,"msvcprtd")
#else // _DEBUG
#pragma comment(lib,"msvcprt")
#endif // _DEBUG

#else // _DLL
#ifdef _DEBUG
#pragma comment(lib,"libcpmtd")
#else // _DEBUG
#pragma comment(lib,"libcpmt")
#endif // _DEBUG
#endif // _DLL

#else // _MT
#ifdef _DEBUG
#pragma comment(lib,"libcpd")
#else // _DEBUG
#pragma comment(lib,"libcp")
#endif // _DEBUG
#endif // _MT
