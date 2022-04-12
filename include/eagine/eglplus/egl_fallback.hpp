/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_EGLPLUS_EGL_FALLBACK_HPP
#define EAGINE_EGLPLUS_EGL_FALLBACK_HPP

#ifndef EGL_CORE_NATIVE_ENGINE
#define EGL_CORE_NATIVE_ENGINE 0x305B
#endif

#ifndef EGL_EXTENSIONS
#define EGL_EXTENSIONS 0x3055
#endif

#ifndef EGL_PLATFORM_DEVICE_EXT
#define EGL_PLATFORM_DEVICE_EXT 0x313F
#endif

#ifndef EGL_CLIENT_APIS
#define EGL_CLIENT_APIS 0x308D
#endif

#ifndef EGL_OPENGL_BIT
#define EGL_OPENGL_BIT 0x0008
#endif

#ifndef EGL_OPENGL_ES_BIT
#define EGL_OPENGL_ES_BIT 0x0001
#endif

#ifndef EGL_OPENVG_BIT
#define EGL_OPENVG_BIT 0x0002
#endif

#ifndef EGL_FOREVER
#define EGL_FOREVER 0xFFFFFFFFFFFFFFFFULL
#endif

#endif
