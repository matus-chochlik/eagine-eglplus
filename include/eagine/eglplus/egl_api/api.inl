/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

namespace eagine::eglplus {
//------------------------------------------------------------------------------
template <typename ApiTraits>
basic_egl_operations<ApiTraits>::basic_egl_operations(api_traits& traits)
  : egl_api{traits}
  , EXT_device_base{"EXT_device_base", *this}
  , EXT_device_enumeration{"EXT_device_enumeration", *this}
  , EXT_device_query{"EXT_device_query", *this}
  , EXT_device_query_name{"EXT_device_query_name", *this}
  , EXT_device_drm{"EXT_device_drm", *this}
  , MESA_device_software{"MESA_device_software", *this}
  , EXT_platform_base{"EXT_platform_base", *this}
  , EXT_platform_device{"EXT_platform_device", *this}
  , EXT_platform_x11{"EXT_platform_x11", *this}
  , EXT_platform_xcb{"EXT_platform_xcb", *this}
  , EXT_platform_wayland{"EXT_platform_wayland", *this}
  , KHR_platform_gbm{"KHR_platform_gbm", *this}
  , MESA_platform_surfaceless{"MESA_platform_surfaceless", *this}
  , EXT_create_context_robustness{"EXT_create_context_robustness", *this}
  , EXT_swap_buffers_with_damage{"EXT_swap_buffers_with_damage", *this}
  , EXT_output_base{"EXT_output_base", *this}
  , EXT_output_drm{"EXT_output_drm", *this}
  , EXT_stream_consumer_egloutput{"EXT_stream_consumer_egloutput", *this}
  , EXT_pixel_format_float{"EXT_pixel_format_float", *this}
  , MESA_configless_context{"MESA_configless_context", *this}
  , MESA_query_driver{"MESA_query_driver", *this} {}
//------------------------------------------------------------------------------
} // namespace eagine::eglplus
