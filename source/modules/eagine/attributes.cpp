/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
module;

#if __has_include(<EGL/egl.h>)
#include <EGL/egl.h>
#define EAGINE_HAS_EGL 1
#else
#define EAGINE_HAS_EGL 0
#endif

export module eagine.eglplus:attributes;
import eagine.core.types;
import eagine.core.c_api;
import :config;
import :enum_types;

namespace eagine::eglplus {

/// @brief Traits for EGL configuration attribute key/value list traits.
/// @ingroup egl_api_wrap
export struct config_attrib_traits {
    /// @brief Alias for the key type.
    using key_type = config_attribute;
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

/// @brief Alias for EGL configuration attribute key/value list.
/// @ingroup egl_api_wrap
export using config_attributes = c_api::key_value_list<config_attrib_traits>;

/// @brief Alias for EGL config attribute list key/value pair.
/// @ingroup egl_api_wrap
/// @see config_attributes
export using config_attribute_value =
  c_api::key_value_list_element<config_attrib_traits>;

/// @brief Concatenation operator for configuration attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates config_attributes
export constexpr auto operator|(
  const config_attribute key,
  const egl_types::int_type value) noexcept -> config_attribute_value {
    return {key, value};
}

/// @brief Concatenation operator for configuration attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates config_attributes
export constexpr auto operator|(
  const config_attribute key,
  const color_buffer_type value) noexcept -> config_attribute_value {
    return {key, egl_types::int_type(value)};
}

/// @brief Concatenation operator for configuration attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates config_attributes
export constexpr auto operator|(
  const config_attribute key,
  const c_api::enum_bitfield<surface_type_bit> value) noexcept
  -> config_attribute_value {
    return {key, egl_types::int_type(value)};
}

/// @brief Concatenation operator for configuration attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates config_attributes
export constexpr auto operator|(
  const config_attribute key,
  const c_api::enum_bitfield<renderable_type_bit> value) noexcept
  -> config_attribute_value {
    return {key, egl_types::int_type(value)};
}

/// @brief Concatenation operator for configuration attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates config_attributes
export constexpr auto operator|(
  const config_attribute key,
  const bool value) noexcept -> config_attribute_value {
#if defined(EGL_TRUE) && defined(EGL_FALSE)
    return {key, value ? EGL_TRUE : EGL_FALSE};
#else
    return {key, value ? 1 : 0};
#endif
}
//------------------------------------------------------------------------------
/// @brief Traits for EGL context attribute key/value list traits.
/// @ingroup egl_api_wrap
export struct context_attrib_traits {
    /// @brief Alias for the key type.
    using key_type = context_attribute;
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

/// @brief Alias for EGL context attribute key/value list.
/// @ingroup egl_api_wrap
/// @see context_attribute_base
export using context_attributes = c_api::key_value_list<context_attrib_traits>;

/// @brief Alias for EGL context attribute list key/value pair.
/// @ingroup egl_api_wrap
/// @see context_attributes
export using context_attribute_value =
  c_api::key_value_list_element<context_attrib_traits>;

/// @brief Concatenation operator for context attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates context_attributes
export constexpr auto operator|(
  const context_attribute key,
  const egl_types::int_type value) noexcept -> context_attribute_value {
    return {key, value};
}

/// @brief Concatenation operator for context attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates context_attributes
export constexpr auto operator|(
  const context_attribute key,
  const c_api::enum_bitfield<context_opengl_profile_bit> value) noexcept
  -> context_attribute_value {
    return {key, egl_types::int_type(value)};
}

/// @brief Concatenation operator for context attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates context_attributes
export constexpr auto operator|(
  const context_attribute key,
  const bool value) noexcept -> context_attribute_value {
#if defined(EGL_TRUE) && defined(EGL_FALSE)
    return {key, value ? EGL_TRUE : EGL_FALSE};
#else
    return {key, value ? 1 : 0};
#endif
}
//------------------------------------------------------------------------------
/// @brief Traits for EGL image attribute key/value list traits.
/// @ingroup egl_api_wrap
export struct image_attrib_traits {
    /// @brief Alias for the key type.
    using key_type = image_attribute;
    using conv_type = egl_types::attrib_type;
    /// @brief Alias for the value type.
    using value_type = egl_types::attrib_type;

    static constexpr auto terminator() noexcept -> value_type {
#ifdef EGL_NONE
        return EGL_NONE;
#else
        return 0;
#endif
    }
};

/// @brief Alias for EGL image attribute key/value list.
/// @ingroup egl_api_wrap
export using image_attributes = c_api::key_value_list<image_attrib_traits>;

/// @brief Alias for EGL image attribute list key/value pair.
/// @ingroup egl_api_wrap
/// @see image_attributes
export using image_attribute_value =
  c_api::key_value_list_element<image_attrib_traits>;

/// @brief Concatenation operator for image attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates image_attributes
export constexpr auto operator|(
  const image_attribute key,
  const egl_types::int_type value) noexcept -> image_attribute_value {
    return {key, value};
}

/// @brief Concatenation operator for image attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates image_attributes
export constexpr auto operator|(
  const image_attribute key,
  const bool value) noexcept -> image_attribute_value {
#if defined(EGL_TRUE) && defined(EGL_FALSE)
    return {key, value ? EGL_TRUE : EGL_FALSE};
#else
    return {key, value ? 1 : 0};
#endif
}
//------------------------------------------------------------------------------
/// @brief Traits for EGL output layer attribute key/value list traits.
/// @ingroup egl_api_wrap
export struct output_layer_attrib_traits {
    /// @brief Alias for the key type.
    using key_type = output_layer_attribute;
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

/// @brief Alias for EGL output layer attribute key/value list.
/// @ingroup egl_api_wrap
export using output_layer_attributes =
  c_api::key_value_list<output_layer_attrib_traits>;

/// @brief Alias for EGL output layer attribute list key/value pair.
/// @ingroup egl_api_wrap
/// @see output_layer_attributes
export using output_layer_attribute_value =
  c_api::key_value_list_element<output_layer_attrib_traits>;

/// @brief Concatenation operator for output layer attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates output_layer_attributes
export constexpr auto operator|(
  const output_layer_attribute key,
  const egl_types::int_type value) noexcept -> output_layer_attribute_value {
    return {key, value};
}

/// @brief Concatenation operator for output layer attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates output_layer_attributes
export constexpr auto operator|(
  const output_layer_attribute key,
  const bool value) noexcept -> output_layer_attribute_value {
#if defined(EGL_TRUE) && defined(EGL_FALSE)
    return {key, value ? EGL_TRUE : EGL_FALSE};
#else
    return {key, value ? 1 : 0};
#endif
}
//------------------------------------------------------------------------------
/// @brief Traits for EGL output port key/value list traits.
/// @ingroup egl_api_wrap
export struct output_port_attrib_traits {
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
export using output_port_attributes =
  c_api::key_value_list<output_port_attrib_traits>;

/// @brief Alias for EGL output port attribute list key/value pair.
/// @ingroup egl_api_wrap
/// @see output_port_attributes
export using output_port_attribute_value =
  c_api::key_value_list_element<output_port_attrib_traits>;

/// @brief Concatenation operator for output port attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates output_port_attributes
export constexpr auto operator|(
  const output_port_attribute key,
  const egl_types::int_type value) noexcept -> output_port_attribute_value {
    return {key, value};
}

/// @brief Concatenation operator for output port attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates output_port_attributes
export constexpr auto operator|(
  const output_port_attribute key,
  const bool value) noexcept -> output_port_attribute_value {
#if defined(EGL_TRUE) && defined(EGL_FALSE)
    return {key, value ? EGL_TRUE : EGL_FALSE};
#else
    return {key, value ? 1 : 0};
#endif
}
//------------------------------------------------------------------------------
/// @brief Traits for EGL platform attribute key/value list traits.
/// @ingroup egl_api_wrap
export struct platform_attrib_traits {
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
export using platform_attributes =
  c_api::key_value_list<platform_attrib_traits>;

/// @brief Alias for EGL platform attribute list key/value pair.
/// @ingroup egl_api_wrap
/// @see platform_attributes
export using platform_attribute_value =
  c_api::key_value_list_element<platform_attrib_traits>;

/// @brief Concatenation operator for platform attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates platform_attributes
export constexpr auto operator|(
  const platform_attribute key,
  const egl_types::int_type value) noexcept -> platform_attribute_value {
    return {key, value};
}

/// @brief Concatenation operator for platform attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates platform_attributes
export constexpr auto operator|(
  const platform_attribute key,
  const bool value) noexcept -> platform_attribute_value {
#if defined(EGL_TRUE) && defined(EGL_FALSE)
    return {key, value ? EGL_TRUE : EGL_FALSE};
#else
    return {key, value ? 1 : 0};
#endif
}
//------------------------------------------------------------------------------
/// @brief Traits for EGL stream key/value list traits.
/// @ingroup egl_api_wrap
export struct stream_attrib_traits {
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
export using stream_attributes = c_api::key_value_list<stream_attrib_traits>;

/// @brief Alias for EGL stream attribute key/value list.
/// @ingroup egl_api_wrap
/// @see stream_attributes
export using stream_attribute_value =
  c_api::key_value_list_element<stream_attrib_traits>;

/// @brief Concatenation operator for stream attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates stream_attributes
export constexpr auto operator|(
  const stream_attribute key,
  const egl_types::int_type value) noexcept -> stream_attribute_value {
    return {key, value};
}

/// @brief Concatenation operator for stream attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates stream_attributes
export constexpr auto operator|(
  const stream_attribute key,
  const bool value) noexcept -> stream_attribute_value {
#if defined(EGL_TRUE) && defined(EGL_FALSE)
    return {key, value ? EGL_TRUE : EGL_FALSE};
#else
    return {key, value ? 1 : 0};
#endif
}
//------------------------------------------------------------------------------
/// @brief Traits for EGL rendering surface attribute key/value list traits.
/// @ingroup egl_api_wrap
export struct surface_attrib_traits {
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
export using surface_attributes = c_api::key_value_list<surface_attrib_traits>;

/// @brief Alias for EGL config attribute list key/value pair.
/// @ingroup egl_api_wrap
/// @see surface_attributes
export using surface_attribute_value =
  c_api::key_value_list_element<surface_attrib_traits>;

/// @brief Concatenation operator for surface attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates surface_attributes
export constexpr auto operator|(
  const surface_attribute key,
  const gl_colorspace value) noexcept -> surface_attribute_value {
    return {key, egl_types::int_type(value)};
}

/// @brief Concatenation operator for surface attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates surface_attributes
export constexpr auto operator|(
  const surface_attribute key,
  const bool value) noexcept -> surface_attribute_value {
#if defined(EGL_TRUE) && defined(EGL_FALSE)
    return {key, value ? EGL_TRUE : EGL_FALSE};
#else
    return {key, value ? 1 : 0};
#endif
}
//------------------------------------------------------------------------------
/// @brief Traits for EGL sync object key/value list traits.
/// @ingroup egl_api_wrap
export struct sync_attrib_traits {
    /// @brief Alias for the key type.
    using key_type = sync_attribute;
    using conv_type = egl_types::attrib_type;
    /// @brief Alias for the value type.
    using value_type = egl_types::attrib_type;

    static constexpr auto terminator() noexcept -> value_type {
#ifdef EGL_NONE
        return EGL_NONE;
#else
        return 0;
#endif
    }
};

/// @brief Alias for EGL sync object attribute key/value list.
/// @ingroup egl_api_wrap
export using sync_attributes = c_api::key_value_list<sync_attrib_traits>;

/// @brief Alias for EGL sync object attribute key/value list.
/// @ingroup egl_api_wrap
/// @see sync_attributes
export using sync_attribute_value =
  c_api::key_value_list_element<sync_attrib_traits>;

/// @brief Concatenation operator for sync object attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates sync_attributes
export constexpr auto operator|(
  const sync_attribute key,
  const egl_types::int_type value) noexcept -> sync_attribute_value {
    return {key, value};
}

/// @brief Concatenation operator for sync object attribute list key and value.
/// @ingroup egl_api_wrap
/// @relates sync_attributes
export constexpr auto operator|(
  const sync_attribute key,
  const bool value) noexcept -> sync_attribute_value {
#if defined(EGL_TRUE) && defined(EGL_FALSE)
    return {key, value ? EGL_TRUE : EGL_FALSE};
#else
    return {key, value ? 1 : 0};
#endif
}
//------------------------------------------------------------------------------
} // namespace eagine::eglplus
