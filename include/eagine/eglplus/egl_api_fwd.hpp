/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_EGLPLUS_EGL_API_FWD_HPP
#define EAGINE_EGLPLUS_EGL_API_FWD_HPP

namespace eagine::eglplus {
//------------------------------------------------------------------------------
class egl_api_traits;

template <typename ApiTraits>
class basic_egl_api;

/// @brief Alias for the default instantation of basic_egl_api.
/// @ingroup egl_api_wrap
using egl_api = basic_egl_api<egl_api_traits>;
//------------------------------------------------------------------------------
} // namespace eagine::eglplus

#endif // EAGINE_EGLPLUS_EGL_API_FWD_HPP
