/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_EGLPLUS_EGL_HPP
#define EAGINE_EGLPLUS_EGL_HPP

#if __has_include(<EGL/egl.h>)
#include <EGL/egl.h>
#endif

#ifndef EGL_CORE_NATIVE_ENGINE
#define EGL_CORE_NATIVE_ENGINE 0x305B
#endif

#endif // EAGINE_EGLPLUS_EGL_HPP
