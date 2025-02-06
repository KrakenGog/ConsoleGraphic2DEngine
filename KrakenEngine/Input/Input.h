#pragma once

#include <Windows.h>

template<typename InputProviderType>
class InputWrap {
public:
	static bool IsPressed(int keyCode) {
		return InputProviderType::IsPressed(keyCode);
	}
};
class WindowsInput {
public:
	static bool IsPressed(int keyCode) {
		return GetAsyncKeyState(keyCode) < 0;
}
};

#ifdef UNIX
using Input = InputWrap<UnixInput>;
#else
using Input = InputWrap<WindowsInput>;
#endif

