/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_EGLPLUS_EGL_API_SURFACE_ATTRIBS_HPP
#define EAGINE_EGLPLUS_EGL_API_SURFACE_ATTRIBS_HPP

#include "config.hpp"
#include "enum_types.hpp"
#include <eagine/c_api/key_value_list.hpp>

namespace eagine::eglplus {

/// @brief Traits for EGL rendering surface attribute key/value list traits.
/// @ingroup egl_api_wrap
struct surface_attrib_traits {
    /// @brief Alias for the key type.
    using key_type = surface_attribute;
    using conv_type = egl_types::int_type;
    /// @brief Alias for the value type.
    using value_type = egl_types::int_type;

    static constexpr auto terminator() noexcept -> egl_types::int_type {
#ifdef EGL_NONE
        return EGL_NONE;
#else
        return 0;
#endif
    }
};

/// @brief Alias for EGL attribute key/value list.
/// @ingroup egl_api_wrap
using surface_attributes = c_api::key_value_list<surface_attrib_traits>;

/// @brief Alias for EGL config attribute list key/value pair.
/// @ingroup egl_api_wrap
/// @see surface_attributes
using surface_attribute_value =
  c_api::key_value_list_element<surface_attrib_traits>;

/// @brief Concatenation operator for surface attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates surface_attributes
static constexpr auto operator|(
  const surface_attribute key,
  const egl_types::int_type value) noexcept -> surface_attribute_value {
    return {key, value};
}

/// @brief Concatenation operator for surface attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates surface_attributes
static constexpr auto operator|(
  const surface_attribute key,
  const texture_format value) noexcept -> surface_attribute_value {
    return {key, egl_types::int_type(value)};
}

/// @brief Concatenation operator for surface attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates surface_attributes
static constexpr auto operator|(
  const surface_attribute key,
  const texture_target value) noexcept -> surface_attribute_value {
    return {key, egl_types::int_type(value)};
}

/// @brief Concatenation operator for surface attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates surface_attributes
static constexpr auto operator|(
  const surface_attribute key,
  const gl_colorspace value) noexcept -> surface_attribute_value {
    return {key, egl_types::int_type(value)};
}

/// @brief Concatenation operator for surface attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates surface_attributes
static constexpr auto operator|(
  const surface_attribute key,
  const bool value) noexcept -> surface_attribute_value {
#if defined(EGL_TRUE) && defined(EGL_FALSE)
    return {key, value ? EGL_TRUE : EGL_FALSE};
#else
    return {key, value ? 1 : 0};
#endif
}

} // namespace eagine::eglplus

#endif // EAGINE_EGLPLUS_EGL_API_SURFACE_ATTRIBS_HPP
