/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_EGLPLUS_EGL_API_OUTPUT_PORT_ATTRIBS_HPP
#define EAGINE_EGLPLUS_EGL_API_OUTPUT_PORT_ATTRIBS_HPP

#include "config.hpp"
#include "enum_types.hpp"
#include <eagine/c_api/key_value_list.hpp>

namespace eagine::eglplus {

/// @brief Traits for EGL output port key/value list traits.
/// @ingroup egl_api_wrap
struct output_port_attrib_traits {
    /// @brief Alias for the key type.
    using key_type = output_port_attribute;
    using conv_type = egl_types::int_type;
    /// @brief Alias for the value type.
    using value_type = egl_types::attrib_type;

    static constexpr auto terminator() noexcept -> egl_types::int_type {
#ifdef EGL_NONE
        return EGL_NONE;
#else
        return 0;
#endif
    }
};

/// @brief Alias for EGL output port attribute key/value list.
/// @ingroup egl_api_wrap
using output_port_attributes = c_api::key_value_list<output_port_attrib_traits>;

/// @brief Alias for EGL output port attribute list key/value pair.
/// @ingroup egl_api_wrap
/// @see output_port_attributes
using output_port_attribute_value =
  c_api::key_value_list_element<output_port_attrib_traits>;

/// @brief Concatenation operator for output port attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates output_port_attributes
static constexpr auto operator|(
  const output_port_attribute key,
  const egl_types::int_type value) noexcept -> output_port_attribute_value {
    return {key, value};
}

/// @brief Concatenation operator for output port attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates output_port_attributes
static constexpr auto operator|(
  const output_port_attribute key,
  const bool value) noexcept -> output_port_attribute_value {
#if defined(EGL_TRUE) && defined(EGL_FALSE)
    return {key, value ? EGL_TRUE : EGL_FALSE};
#else
    return {key, value ? 1 : 0};
#endif
}

} // namespace eagine::eglplus

#endif // EAGINE_EGLPLUS_EGL_API_OUTPUT_PORT_ATTRIBS_HPP
