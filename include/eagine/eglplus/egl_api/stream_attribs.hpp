/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_EGLPLUS_EGL_API_STREAM_ATTRIBS_HPP
#define EAGINE_EGLPLUS_EGL_API_STREAM_ATTRIBS_HPP

#include "config.hpp"
#include "enum_types.hpp"
#include <eagine/c_api/key_value_list.hpp>

namespace eagine::eglplus {

/// @brief Traits for EGL stream key/value list traits.
/// @ingroup egl_api_wrap
struct stream_attrib_traits {
    /// @brief Alias for the key type.
    using key_type = stream_attribute;
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

/// @brief Alias for EGL stream attribute key/value list.
/// @ingroup egl_api_wrap
using stream_attributes = c_api::key_value_list<stream_attrib_traits>;

/// @brief Alias for EGL stream attribute key/value list.
/// @ingroup egl_api_wrap
/// @see stream_attributes
using stream_attribute_value =
  c_api::key_value_list_element<stream_attrib_traits>;

/// @brief Concatenation operator for stream attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates stream_attributes
static constexpr auto operator|(
  const stream_attribute key,
  const egl_types::int_type value) noexcept -> stream_attribute_value {
    return {key, value};
}

/// @brief Concatenation operator for stream attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates stream_attributes
static constexpr auto operator|(
  const stream_attribute key,
  const bool value) noexcept -> stream_attribute_value {
#if defined(EGL_TRUE) && defined(EGL_FALSE)
    return {key, value ? EGL_TRUE : EGL_FALSE};
#else
    return {key, value ? 1 : 0};
#endif
}

} // namespace eagine::eglplus

#endif // EAGINE_EGLPLUS_EGL_API_STREAM_ATTRIBS_HPP
