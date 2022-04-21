/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_EGLPLUS_EGL_API_ENUM_CLASS_HPP
#define EAGINE_EGLPLUS_EGL_API_ENUM_CLASS_HPP

#include "config.hpp"
#include <eagine/c_api/enum_bitfield.hpp>
#include <eagine/c_api/enum_class.hpp>
#include <eagine/identifier.hpp>

namespace eagine::eglplus {
//------------------------------------------------------------------------------
/// @brief Typed wrapper class for EGL enum constants/values.
/// @ingroup egl_api_wrap
///
/// This wrapper uses the specified Id to group various EGL constants logically
/// belonging together and prevents accidental mismatches and use of EGL constants
/// from unrelated groups. For example using a config attribute constant in place
/// of context attribute constants. Such mismatches result in compilation errors.
template <typename Self, identifier_t Id>
using egl_int_class =
  c_api::enum_class<Self, egl_types::int_type, EAGINE_ID_V(EGL), Id>;

template <typename Self, identifier_t Id>
using egl_enum_class =
  c_api::enum_class<Self, egl_types::enum_type, EAGINE_ID_V(EGL), Id>;

/// @brief Type erasure alias for EGL enum classes.
/// @ingroup egl_api_wrap
using egl_any_enum_class = c_api::any_enum_class<EAGINE_ID_V(EGL)>;

/// @brief Type erasure alias for EGL enum values.
/// @ingroup egl_api_wrap
using egl_any_enum_value = c_api::any_enum_value<EAGINE_ID_V(EGL)>;

static constexpr auto same_enum_class(
  const egl_any_enum_class a,
  const egl_any_enum_class b) noexcept -> bool {
    return ::eagine::c_api::same_enum_class(a, b);
}
//------------------------------------------------------------------------------
} // namespace eagine::eglplus

#endif // EAGINE_EGLPLUS_EGL_API_ENUM_CLASS_HPP
