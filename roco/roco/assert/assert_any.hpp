#pragma once

#ifndef _ROCO_ASSERT_ASSERT_ANY_HPP_
#define _ROCO_ASSERT_ASSERT_ANY_HPP_

#pragma warning(disable:4996) // _snwprintf()

#include <Windows.h>

#include <corecrt.h>
#include <stdlib.h>
#include <stdio.h>

_CRT_BEGIN_C_HEADER

/**
* __func__
* __FILE__
* __LINE__
* __TIME__
* __DATE__
*/

inline void __cdecl wassert_(
	_In_z_ wchar_t const* _Message,
	_In_z_ wchar_t const* _File,
	_In_z_ wchar_t const* _Func,
	_In_   unsigned       _Line,
	_In_z_ wchar_t const* _Date,
	_In_z_ wchar_t const* _Time)
{
	wchar_t* msgbuf = (wchar_t*)malloc(8192 * sizeof(wchar_t));

	if (!_File || _File[0] == 0)
		_File = L"<unknown>";

	if (!_Message || _Message[0] == 0)
		_Message = L"?";

	_snwprintf(msgbuf, 8191,
		L"Assertion failed!\nFile: %ws, function: %ws, Line: %u\nRun time: %ws at %ws\nExpression: %ws",
		_File, _Func, _Line, _Date, _Time, _Message);

	fwprintf(stderr, L"%ws\n", msgbuf);
	OutputDebugStringW(msgbuf);

	abort();
}

/**
* @brief assert can be used what ever debug or release mode in running
*/
#define ASSERT_ANY(expression) (void)(												         \
            (!!(expression)) ||                                                              \
            (wassert_(_CRT_WIDE(#expression), _CRT_WIDE(__FILE__), _CRT_WIDE(__FUNCTION__), (unsigned)(__LINE__),_CRT_WIDE(__DATE__), _CRT_WIDE(__TIME__)), 0) \
        )

_CRT_END_C_HEADER

#endif // _ROCO_ASSERT_ASSERT_ANY_HPP_