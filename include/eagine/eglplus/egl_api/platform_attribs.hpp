/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_EGLPLUS_EGL_API_PLATFORM_ATTRIBS_HPP
#define EAGINE_EGLPLUS_EGL_API_PLATFORM_ATTRIBS_HPP

#include "config.hpp"
#include "enum_types.hpp"
#include <eagine/key_val_list.hpp>

namespace eagine::eglplus {

/// @brief Traits for EGL platform attribute key/value list traits.
/// @ingroup egl_api_wrap
struct platform_attrib_traits {
    /// @brief Alias for the key type.
    using key_type = platform_attribute;
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

/// @brief Alias for EGL platform attribute key/value list.
/// @ingroup egl_api_wrap
template <std::size_t N>
using platform_attributes = key_value_list<platform_attrib_traits, N>;

/// @brief Alias for EGL platform attribute list key/value pair.
/// @ingroup egl_api_wrap
/// @see platform_attributes
using platform_attribute_value = key_value_list_element<platform_attrib_traits>;

/// @brief Concatenation operator for platform attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates platform_attributes
static constexpr auto
operator|(platform_attribute key, egl_types::int_type value) noexcept
  -> platform_attribute_value {
    return {key, value};
}

/// @brief Concatenation operator for platform attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates platform_attributes
static constexpr auto operator|(platform_attribute key, bool value) noexcept
  -> platform_attribute_value {
#if defined(EGL_TRUE) && defined(EGL_FALSE)
    return {key, value ? EGL_TRUE : EGL_FALSE};
#else
    return {key, value ? 1 : 0};
#endif
}

} // namespace eagine::eglplus

#endif // EAGINE_EGLPLUS_EGL_API_PLATFORM_ATTRIBS_HPP
