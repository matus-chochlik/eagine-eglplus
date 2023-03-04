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

#ifndef EGL_PLATFORM_DEVICE_EXT
#define EGL_PLATFORM_DEVICE_EXT 0x313F
#endif

#define EAGINE_HAS_EGL 1
#else
#define EAGINE_HAS_EGL 0
#endif

export module eagine.eglplus:constants;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.c_api;
import :config;
import :enum_types;
import :c_api;
import std;

namespace eagine {
//------------------------------------------------------------------------------
export template <>
struct within_limits<eglplus::color_buffer_type, eglplus::egl_types::enum_type> {
    auto check(eglplus::egl_types::enum_type) const noexcept -> bool;
};
//------------------------------------------------------------------------------
export template <>
struct within_limits<eglplus::texture_target, eglplus::egl_types::enum_type> {
    auto check(eglplus::egl_types::enum_type) const noexcept -> bool;
};
//------------------------------------------------------------------------------
namespace eglplus {
export auto egl_enum_by_name(const string_view name) noexcept
  -> std::optional<egl_types::enum_type>;
//------------------------------------------------------------------------------
/// @brief Class wrapping the constants from the EGL API.
/// @ingroup egl_api_wrap
/// @see basic_egl_c_api
/// @see basic_egl_operations
export template <typename ApiTraits>
class basic_egl_constants {
public:
#if EAGINE_HAS_EGL
    static constexpr const typename egl_types::config_type no_config{nullptr};
#else
    static constexpr const typename egl_types::config_type no_config{0};
#endif

    static constexpr const typename egl_types::int_type dont_care{
#ifdef EGL_DONT_CARE
      EGL_DONT_CARE
#else
      0
#endif
    };

    using enum_type = typename egl_types::enum_type;
    using enum_type_i = std::type_identity<enum_type>;
    template <enum_type value>
    using enum_type_c = std::integral_constant<enum_type, value>;

    using int_type = typename egl_types::int_type;
    using int_type_i = std::type_identity<int_type>;
    template <int_type value>
    using int_type_c = std::integral_constant<int_type, value>;

    /// @var success
    /// @eglconstwrap{SUCCESS}
    c_api::opt_constant<
      mp_list<error_code>,
#ifdef EGL_SUCCESS
      int_type_c<EGL_SUCCESS>>
#else
      int_type_i>
#endif
      success;

    /// @var not_initialized
    /// @eglconstwrap{NOT_INITIALIZED}
    c_api::opt_constant<
      mp_list<error_code>,
#ifdef EGL_NOT_INITIALIZED
      int_type_c<EGL_NOT_INITIALIZED>>
#else
      int_type_i>
#endif
      not_initialized;

    /// @var bad_access
    /// @eglconstwrap{BAD_ACCESS}
    c_api::opt_constant<
      mp_list<error_code>,
#ifdef EGL_BAD_ACCESS
      int_type_c<EGL_BAD_ACCESS>>
#else
      int_type_i>
#endif
      bad_access;

    /// @var bad_alloc
    /// @eglconstwrap{BAD_ALLOC}
    c_api::opt_constant<
      mp_list<error_code>,
#ifdef EGL_BAD_ALLOC
      int_type_c<EGL_BAD_ALLOC>>
#else
      int_type_i>
#endif
      bad_alloc;

    /// @var bad_attribute
    /// @eglconstwrap{BAD_ATTRIBUTE}
    c_api::opt_constant<
      mp_list<error_code>,
#ifdef EGL_BAD_ATTRIBUTE
      int_type_c<EGL_BAD_ATTRIBUTE>>
#else
      int_type_i>
#endif
      bad_attribute;

    /// @var bad_context
    /// @eglconstwrap{BAD_CONTEXT}
    c_api::opt_constant<
      mp_list<error_code>,
#ifdef EGL_BAD_CONTEXT
      int_type_c<EGL_BAD_CONTEXT>>
#else
      int_type_i>
#endif
      bad_context;

    /// @var bad_config
    /// @eglconstwrap{BAD_CONFIG}
    c_api::opt_constant<
      mp_list<error_code>,
#ifdef EGL_BAD_CONFIG
      int_type_c<EGL_BAD_CONFIG>>
#else
      int_type_i>
#endif
      bad_config;

    /// @var bad_current_surface
    /// @eglconstwrap{BAD_CURRENT_SURFACE}
    c_api::opt_constant<
      mp_list<error_code>,
#ifdef EGL_BAD_CURRENT_SURFACE
      int_type_c<EGL_BAD_CURRENT_SURFACE>>
#else
      int_type_i>
#endif
      bad_current_surface;

    /// @var bad_display
    /// @eglconstwrap{BAD_DISPLAY}
    c_api::opt_constant<
      mp_list<error_code>,
#ifdef EGL_BAD_DISPLAY
      int_type_c<EGL_BAD_DISPLAY>>
#else
      int_type_i>
#endif
      bad_display;

    /// @var bad_surface
    /// @eglconstwrap{BAD_SURFACE}
    c_api::opt_constant<
      mp_list<error_code>,
#ifdef EGL_BAD_SURFACE
      int_type_c<EGL_BAD_SURFACE>>
#else
      int_type_i>
#endif
      bad_surface;

    /// @var bad_match
    /// @eglconstwrap{BAD_MATCH}
    c_api::opt_constant<
      mp_list<error_code>,
#ifdef EGL_BAD_MATCH
      int_type_c<EGL_BAD_MATCH>>
#else
      int_type_i>
#endif
      bad_match;

    /// @var bad_parameter
    /// @eglconstwrap{BAD_PARAMETER}
    c_api::opt_constant<
      mp_list<error_code>,
#ifdef EGL_BAD_PARAMETER
      int_type_c<EGL_BAD_PARAMETER>>
#else
      int_type_i>
#endif
      bad_parameter;

    /// @var bad_native_pixmap
    /// @eglconstwrap{BAD_NATIVE_PIXMAP}
    c_api::opt_constant<
      mp_list<error_code>,
#ifdef EGL_BAD_NATIVE_PIXMAP
      int_type_c<EGL_BAD_NATIVE_PIXMAP>>
#else
      int_type_i>
#endif
      bad_native_pixmap;

    /// @var bad_native_window
    /// @eglconstwrap{BAD_NATIVE_WINDOW}
    c_api::opt_constant<
      mp_list<error_code>,
#ifdef EGL_BAD_NATIVE_WINDOW
      int_type_c<EGL_BAD_NATIVE_WINDOW>>
#else
      int_type_i>
#endif
      bad_native_window;

    /// @var context_lost
    /// @eglconstwrap{CONTEXT_LOST}
    c_api::opt_constant<
      mp_list<error_code>,
#ifdef EGL_CONTEXT_LOST
      int_type_c<EGL_CONTEXT_LOST>>
#else
      int_type_i>
#endif
      context_lost;

    /// @var true_
    /// @eglconstwrap{TRUE}
    c_api::opt_constant<
      mp_list<eglplus::true_false>,
#ifdef EGL_TRUE
      enum_type_c<EGL_TRUE>>
#else
      enum_type_i>
#endif
      true_;

    /// @var false_
    /// @eglconstwrap{FALSE}
    c_api::opt_constant<
      mp_list<eglplus::true_false>,
#ifdef EGL_FALSE
      enum_type_c<EGL_FALSE>>
#else
      enum_type_i>
#endif
      false_;

    /// @var platform_device
    /// @eglconstwrap{PLATFORM_DEVICE_EXT}
    c_api::opt_constant<
      mp_list<platform>,
#ifdef EGL_PLATFORM_DEVICE_EXT
      enum_type_c<EGL_PLATFORM_DEVICE_EXT>>
#else
      enum_type_i>
#endif
      platform_device;

    /// @var platform_x11
    /// @eglconstwrap{PLATFORM_X11_EXT}
    c_api::opt_constant<mp_list<platform>, enum_type_c<0x31D5>> platform_x11;

    /// @var platform_xcb
    /// @eglconstwrap{PLATFORM_XCB_EXT}
    c_api::opt_constant<mp_list<platform>, enum_type_c<0x31DC>> platform_xcb;

    /// @var platform_wayland
    /// @eglconstwrap{PLATFORM_WAYLAND}
    c_api::opt_constant<mp_list<platform>, enum_type_c<0x31D8>> platform_wayland;

    /// @var platform_gbm_mesa
    /// @eglconstwrap{PLATFORM_GBM_MESA}
    c_api::opt_constant<mp_list<platform>, enum_type_c<0x31D7>>
      platform_gbm_mesa;

    /// @var platform_surfaceless
    /// @eglconstwrap{PLATFORM_SURFACELESS_EXT}
    c_api::opt_constant<mp_list<platform>, enum_type_c<0x31DD>>
      platform_surfaceless;

    /// @var platform_android
    /// @eglconstwrap{PLATFORM_ANDROID_EXT}
    c_api::opt_constant<mp_list<platform>, enum_type_c<0x3141>> platform_android;

    /// @var client_apis
    /// @eglconstwrap{CLIENT_APIS}
    c_api::opt_constant<
      mp_list<string_query>,
#ifdef EGL_CLIENT_APIS
      int_type_c<EGL_CLIENT_APIS>>
#else
      int_type_i>
#endif
      client_apis;

    /// @var vendor
    /// @eglconstwrap{VENDOR}
    c_api::opt_constant<
      mp_list<string_query>,
#ifdef EGL_VENDOR
      int_type_c<EGL_VENDOR>>
#else
      int_type_i>
#endif
      vendor;

    /// @var version
    /// @eglconstwrap{VERSION}
    c_api::opt_constant<
      mp_list<string_query>,
#ifdef EGL_VERSION
      int_type_c<EGL_VERSION>>
#else
      int_type_i>
#endif
      version;

    /// @var renderer
    /// @eglconstwrap{RENDERER}
    c_api::opt_constant<mp_list<device_string_query>, int_type_c<0x335E>>
      renderer;

    /// @var extensions
    /// @eglconstwrap{EXTENSIONS}
    c_api::opt_constant<
      mp_list<string_query, device_string_query>,
#ifdef EGL_EXTENSIONS
      int_type_c<EGL_EXTENSIONS>>
#else
      int_type_i>
#endif
      extensions;

    /// @var drm_device_file
    /// @eglconstwrap{DRM_DEVICE_FILE_EXT}
    c_api::opt_constant<
      mp_list<string_query, device_string_query>,
      int_type_c<0x3233>>
      drm_device_file;

    /// @var drm_device_file
    /// @eglconstwrap{DRM_DEVICE_FILE_EXT}
    c_api::opt_constant<mp_list<platform_attribute>, int_type_c<0x333C>>
      drm_master_fd;

    c_api::opt_constant<
      mp_list<config_attribute>,
#ifdef EGL_CONFIG_ID
      int_type_c<EGL_CONFIG_ID>>
#else
      int_type_i>
#endif
      config_id;

    c_api::opt_constant<
      mp_list<config_attribute>,
#ifdef EGL_CONFORMANT
      int_type_c<EGL_CONFORMANT>>
#else
      int_type_i>
#endif
      conformant;

    c_api::opt_constant<
      mp_list<config_attribute>,
#ifdef EGL_SURFACE_TYPE
      int_type_c<EGL_SURFACE_TYPE>>
#else
      int_type_i>
#endif
      surface_type;

    c_api::opt_constant<
      mp_list<config_attribute>,
#ifdef EGL_RENDERABLE_TYPE
      int_type_c<EGL_RENDERABLE_TYPE>>
#else
      int_type_i>
#endif
      renderable_type;

    c_api::opt_constant<
      mp_list<config_attribute>,
#ifdef EGL_COLOR_BUFFER_TYPE
      int_type_c<EGL_COLOR_BUFFER_TYPE>>
#else
      int_type_i>
#endif
      color_buffer_type;

    c_api::opt_constant<
      mp_list<config_attribute>,
#ifdef EGL_BUFFER_SIZE
      int_type_c<EGL_BUFFER_SIZE>>
#else
      int_type_i>
#endif
      buffer_size;

    c_api::opt_constant<
      mp_list<config_attribute>,
#ifdef EGL_RED_SIZE
      int_type_c<EGL_RED_SIZE>>
#else
      int_type_i>
#endif
      red_size;

    c_api::opt_constant<
      mp_list<config_attribute>,
#ifdef EGL_GREEN_SIZE
      int_type_c<EGL_GREEN_SIZE>>
#else
      int_type_i>
#endif
      green_size;

    c_api::opt_constant<
      mp_list<config_attribute>,
#ifdef EGL_BLUE_SIZE
      int_type_c<EGL_BLUE_SIZE>>
#else
      int_type_i>
#endif
      blue_size;

    c_api::opt_constant<
      mp_list<config_attribute>,
#ifdef EGL_LUMINANCE_SIZE
      int_type_c<EGL_LUMINANCE_SIZE>>
#else
      int_type_i>
#endif
      luminance_size;

    c_api::opt_constant<
      mp_list<config_attribute>,
#ifdef EGL_ALPHA_SIZE
      int_type_c<EGL_ALPHA_SIZE>>
#else
      int_type_i>
#endif
      alpha_size;

    c_api::opt_constant<
      mp_list<config_attribute>,
#ifdef EGL_ALPHA_MASK_SIZE
      int_type_c<EGL_ALPHA_MASK_SIZE>>
#else
      int_type_i>
#endif
      alpha_mask_size;

    c_api::opt_constant<
      mp_list<config_attribute>,
#ifdef EGL_DEPTH_SIZE
      int_type_c<EGL_DEPTH_SIZE>>
#else
      int_type_i>
#endif
      depth_size;

    c_api::opt_constant<
      mp_list<config_attribute>,
#ifdef EGL_STENCIL_SIZE
      int_type_c<EGL_STENCIL_SIZE>>
#else
      int_type_i>
#endif
      stencil_size;

    c_api::opt_constant<
      mp_list<config_attribute>,
#ifdef EGL_SAMPLE_BUFFERS
      int_type_c<EGL_SAMPLE_BUFFERS>>
#else
      int_type_i>
#endif
      sample_buffers;

    c_api::opt_constant<
      mp_list<config_attribute>,
#ifdef EGL_SAMPLES
      int_type_c<EGL_SAMPLES>>
#else
      int_type_i>
#endif
      samples;

    c_api::opt_constant<
      mp_list<config_attribute>,
#ifdef EGL_TRANSPARENT_TYPE
      int_type_c<EGL_TRANSPARENT_TYPE>>
#else
      int_type_i>
#endif
      transparent_type;

    c_api::opt_constant<
      mp_list<config_attribute>,
#ifdef EGL_TRANSPARENT_RED_VALUE
      int_type_c<EGL_TRANSPARENT_RED_VALUE>>
#else
      int_type_i>
#endif
      transparent_red_value;

    c_api::opt_constant<
      mp_list<config_attribute>,
#ifdef EGL_TRANSPARENT_GREEN_VALUE
      int_type_c<EGL_TRANSPARENT_GREEN_VALUE>>
#else
      int_type_i>
#endif
      transparent_green_value;

    c_api::opt_constant<
      mp_list<config_attribute>,
#ifdef EGL_TRANSPARENT_BLUE_VALUE
      int_type_c<EGL_TRANSPARENT_BLUE_VALUE>>
#else
      int_type_i>
#endif
      transparent_blue_value;

    c_api::opt_constant<mp_list<config_attribute>, int_type_c<0x3339>>
      color_component_type;

    c_api::opt_constant<
      mp_list<config_attribute>,
#ifdef EGL_LEVEL
      int_type_c<EGL_LEVEL>>
#else
      int_type_i>
#endif
      level;

    c_api::opt_constant<
      mp_list<config_attribute>,
#ifdef EGL_PBUFFER_WIDTH
      int_type_c<EGL_PBUFFER_WIDTH>>
#else
      int_type_i>
#endif
      pbuffer_width;

    c_api::opt_constant<
      mp_list<config_attribute>,
#ifdef EGL_PBUFFER_HEIGHT
      int_type_c<EGL_PBUFFER_HEIGHT>>
#else
      int_type_i>
#endif
      pbuffer_height;

    c_api::opt_constant<
      mp_list<config_attribute>,
#ifdef EGL_PBUFFER_PIXELS
      int_type_c<EGL_PBUFFER_PIXELS>>
#else
      int_type_i>
#endif
      pbuffer_pixels;

    c_api::opt_constant<
      mp_list<config_attribute>,
#ifdef EGL_MAX_SWAP_INTERVAL
      int_type_c<EGL_MAX_SWAP_INTERVAL>>
#else
      int_type_i>
#endif
      max_swap_interval;

    c_api::opt_constant<
      mp_list<config_attribute>,
#ifdef EGL_MIN_SWAP_INTERVAL
      int_type_c<EGL_MIN_SWAP_INTERVAL>>
#else
      int_type_i>
#endif
      min_swap_interval;

    c_api::opt_constant<
      mp_list<surface_attribute>,
#ifdef EGL_WIDTH
      int_type_c<EGL_WIDTH>>
#else
      int_type_i>
#endif
      width;

    c_api::opt_constant<
      mp_list<surface_attribute>,
#ifdef EGL_HEIGHT
      int_type_c<EGL_HEIGHT>>
#else
      int_type_i>
#endif
      height;

    c_api::opt_constant<
      mp_list<surface_attribute>,
#ifdef EGL_LARGEST_PBUFFER
      int_type_c<EGL_LARGEST_PBUFFER>>
#else
      int_type_i>
#endif
      largest_pbuffer;

    c_api::opt_constant<
      mp_list<surface_attribute>,
#ifdef EGL_GL_COLORSPACE
      int_type_c<EGL_GL_COLORSPACE>,
#else
      int_type_i,
#endif
      eglplus::gl_colorspace>
      gl_colorspace;

    c_api::opt_constant<
      mp_list<surface_attribute>,
#ifdef EGL_TEXTURE_TARGET
      int_type_c<EGL_TEXTURE_TARGET>,
#else
      int_type_i,
#endif
      eglplus::texture_target>
      texture_target;

    c_api::opt_constant<
      mp_list<surface_attribute>,
#ifdef EGL_MIPMAP_LEVEL
      int_type_c<EGL_MIPMAP_LEVEL>>
#else
      int_type_i>
#endif
      mipmap_level;

    c_api::opt_constant<
      mp_list<surface_attribute>,
#ifdef EGL_MULTISAMPLE_RESOLVE
      int_type_c<EGL_MULTISAMPLE_RESOLVE>>
#else
      int_type_i>
#endif
      multisample_resolve;

    c_api::opt_constant<
      mp_list<surface_attribute>,
#ifdef EGL_SWAP_BEHAVIOR
      int_type_c<EGL_SWAP_BEHAVIOR>>
#else
      int_type_i>
#endif
      swap_behavior;

    c_api::opt_constant<
      mp_list<context_attribute>,
#ifdef EGL_CONTEXT_MAJOR_VERSION
      int_type_c<EGL_CONTEXT_MAJOR_VERSION>>
#else
      int_type_i>
#endif
      context_major_version;

    c_api::opt_constant<
      mp_list<context_attribute>,
#ifdef EGL_CONTEXT_MINOR_VERSION
      int_type_c<EGL_CONTEXT_MINOR_VERSION>>
#else
      int_type_i>
#endif
      context_minor_version;

    c_api::opt_constant<
      mp_list<context_attribute>,
#ifdef EGL_CONTEXT_OPENGL_PROFILE_MASK
      int_type_c<EGL_CONTEXT_OPENGL_PROFILE_MASK>>
#else
      int_type_i>
#endif
      context_opengl_profile_mask;

    c_api::opt_constant<
      mp_list<context_attribute>,
#ifdef EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE
      int_type_c<EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE>>
#else
      int_type_i>
#endif
      context_opengl_forward_compatible;

    c_api::opt_constant<
      mp_list<context_attribute>,
#ifdef EGL_CONTEXT_OPENGL_DEBUG
      int_type_c<EGL_CONTEXT_OPENGL_DEBUG>>
#else
      int_type_i>
#endif
      context_opengl_debug;

    c_api::opt_constant<
      mp_list<context_attribute>,
#ifdef EGL_CONTEXT_OPENGL_ROBUST_ACCESS
      int_type_c<EGL_CONTEXT_OPENGL_ROBUST_ACCESS>>
#else
      int_type_i>
#endif
      context_opengl_robust_access;

    c_api::opt_constant<
      mp_list<surface_type_bit>,
#ifdef EGL_WINDOW_BIT
      int_type_c<EGL_WINDOW_BIT>>
#else
      int_type_i>
#endif
      window_bit;

    c_api::opt_constant<
      mp_list<surface_type_bit>,
#ifdef EGL_PIXMAP_BIT
      int_type_c<EGL_PIXMAP_BIT>>
#else
      int_type_i>
#endif
      pixmap_bit;

    c_api::opt_constant<
      mp_list<surface_type_bit>,
#ifdef EGL_PBUFFER_BIT
      int_type_c<EGL_PBUFFER_BIT>>
#else
      int_type_i>
#endif
      pbuffer_bit;

    c_api::opt_constant<mp_list<surface_type_bit>, int_type_c<0x0800>>
      stream_bit;

    c_api::opt_constant<
      mp_list<surface_type_bit>,
#ifdef EGL_MULTISAMPLE_RESOLVE_BOX_BIT
      int_type_c<EGL_MULTISAMPLE_RESOLVE_BOX_BIT>>
#else
      int_type_i>
#endif
      multisample_resolve_box_bit;

    c_api::opt_constant<
      mp_list<surface_type_bit>,
#ifdef EGL_SWAP_BEHAVIOR_PRESERVED_BIT
      int_type_c<EGL_SWAP_BEHAVIOR_PRESERVED_BIT>>
#else
      int_type_i>
#endif
      swap_behavior_preserved_bit;

    c_api::opt_constant<
      mp_list<surface_type_bit>,
#ifdef EGL_VG_COLORSPACE_LINEAR_BIT
      int_type_c<EGL_VG_COLORSPACE_LINEAR_BIT>>
#else
      int_type_i>
#endif
      vg_colorspace_linear_bit;

    c_api::opt_constant<
      mp_list<surface_type_bit>,
#ifdef EGL_VG_ALPHA_FORMAT_PRE_BIT_BIT
      int_type_c<EGL_VG_ALPHA_FORMAT_PRE_BIT_BIT>>
#else
      int_type_i>
#endif
      vg_alpha_format_pre_bit_bit;

    c_api::opt_constant<mp_list<stream_attribute>, int_type_c<0x3210>>
      consumer_latency_usec;

    c_api::opt_constant<mp_list<stream_attribute>, int_type_c<0x321E>>
      consumer_acquire_timeout_usec;

    c_api::opt_constant<mp_list<stream_attribute>, int_type_c<0x3212>>
      producer_frame;

    c_api::opt_constant<mp_list<stream_attribute>, int_type_c<0x3213>>
      consumer_frame;

    c_api::opt_constant<mp_list<stream_attribute>, int_type_c<0x3214>>
      stream_state;

    c_api::opt_constant<mp_list<eglplus::stream_state>, int_type_c<0x3215>>
      stream_state_created;

    c_api::opt_constant<mp_list<eglplus::stream_state>, int_type_c<0x3216>>
      stream_state_connecting;

    c_api::opt_constant<mp_list<eglplus::stream_state>, int_type_c<0x3217>>
      stream_state_empty;

    c_api::opt_constant<mp_list<eglplus::stream_state>, int_type_c<0x3218>>
      stream_state_new_frame_available;

    c_api::opt_constant<mp_list<eglplus::stream_state>, int_type_c<0x3219>>
      stream_state_old_frame_available;

    c_api::opt_constant<mp_list<eglplus::stream_state>, int_type_c<0x321A>>
      stream_state_disconnected;

    c_api::opt_constant<mp_list<image_attribute>, int_type_c<0x30D2>>
      image_preserved;

    c_api::opt_constant<
      mp_list<client_api_bit, renderable_type_bit>,
#ifdef EGL_OPENGL_BIT
      int_type_c<EGL_OPENGL_BIT>>
#else
      int_type_i>
#endif
      opengl_bit;

    c_api::opt_constant<
      mp_list<client_api_bit, renderable_type_bit>,
#ifdef EGL_OPENGL_ES_BIT
      int_type_c<EGL_OPENGL_ES_BIT>>
#else
      int_type_i>
#endif
      opengl_es_bit;

    c_api::opt_constant<
      mp_list<client_api_bit, renderable_type_bit>,
#ifdef EGL_OPENGL_ES2_BIT
      int_type_c<EGL_OPENGL_ES2_BIT>>
#else
      int_type_i>
#endif
      opengl_es2_bit;

    c_api::opt_constant<
      mp_list<client_api_bit, renderable_type_bit>,
#ifdef EGL_OPENGL_ES3_BIT
      int_type_c<EGL_OPENGL_ES3_BIT>>
#else
      int_type_i>
#endif
      opengl_es3_bit;

    c_api::opt_constant<
      mp_list<client_api_bit, renderable_type_bit>,
#ifdef EGL_OPENVG_BIT
      int_type_c<EGL_OPENVG_BIT>>
#else
      int_type_i>
#endif
      openvg_bit;

    c_api::opt_constant<
      mp_list<client_api>,
#ifdef EGL_OPENGL_API
      enum_type_c<EGL_OPENGL_API>>
#else
      enum_type_i>
#endif
      opengl_api;

    c_api::opt_constant<
      mp_list<client_api>,
#ifdef EGL_OPENGL_ES_API
      enum_type_c<EGL_OPENGL_ES_API>>
#else
      enum_type_i>
#endif
      opengl_es_api;

    c_api::opt_constant<
      mp_list<client_api>,
#ifdef EGL_OPENVG_API
      enum_type_c<EGL_OPENVG_API>>
#else
      enum_type_i>
#endif
      openvg_api;

    c_api::opt_constant<
      mp_list<eglplus::context_opengl_profile_bit>,
#ifdef EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT
      int_type_c<EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT>>
#else
      int_type_i>
#endif
      context_opengl_core_profile_bit;

    c_api::opt_constant<
      mp_list<eglplus::context_opengl_profile_bit>,
#ifdef EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT
      int_type_c<EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT>>
#else
      int_type_i>
#endif
      context_opengl_compatibility_profile_bit;

    c_api::opt_constant<
      mp_list<eglplus::color_buffer_type>,
#ifdef EGL_RGB_BUFFER
      int_type_c<EGL_RGB_BUFFER>>
#else
      int_type_i>
#endif
      rgb_buffer;

    c_api::opt_constant<
      mp_list<eglplus::color_buffer_type>,
#ifdef EGL_LUMINANCE_BUFFER
      int_type_c<EGL_LUMINANCE_BUFFER>>
#else
      int_type_i>
#endif
      luminance_buffer;

    c_api::
      opt_constant<mp_list<eglplus::color_component_type>, int_type_c<0x333A>>
        color_component_type_fixed;

    c_api::
      opt_constant<mp_list<eglplus::color_component_type>, int_type_c<0x333B>>
        color_component_type_float;

    c_api::opt_constant<
      mp_list<eglplus::read_draw>,
#ifdef EGL_READ
      int_type_c<EGL_READ>>
#else
      int_type_i>
#endif
      read;

    c_api::opt_constant<
      mp_list<eglplus::read_draw>,
#ifdef EGL_DRAW
      int_type_c<EGL_DRAW>>
#else
      int_type_i>
#endif
      draw;

    c_api::opt_constant<
      mp_list<eglplus::sync_type>,
#ifdef EGL_SYNC_FENCE
      enum_type_c<EGL_SYNC_FENCE>>
#else
      enum_type_i>
#endif
      sync_fence;

    c_api::opt_constant<
      mp_list<eglplus::sync_type>,
#ifdef EGL_SYNC_CL_EVENT
      enum_type_c<EGL_SYNC_CL_EVENT>>
#else
      enum_type_i>
#endif
      sync_cl_event;

    c_api::opt_constant<
      mp_list<eglplus::texture_format, eglplus::texture_target>,
#ifdef EGL_NO_TEXTURE
      int_type_c<EGL_NO_TEXTURE>>
#else
      int_type_i>
#endif
      no_texture;

    c_api::opt_constant<
      mp_list<eglplus::texture_target>,
#ifdef EGL_TEXTURE_2D
      int_type_c<EGL_TEXTURE_2D>>
#else
      int_type_i>
#endif
      texture_2d;

    c_api::opt_constant<
      mp_list<eglplus::texture_format>,
#ifdef EGL_TEXTURE_RGB
      int_type_c<EGL_TEXTURE_RGB>>
#else
      int_type_i>
#endif
      texture_rgb;

    c_api::opt_constant<
      mp_list<eglplus::texture_format>,
#ifdef EGL_TEXTURE_RGBA
      int_type_c<EGL_TEXTURE_RGBA>>
#else
      int_type_i>
#endif
      texture_rgba;

    c_api::opt_constant<
      mp_list<eglplus::gl_colorspace>,
#ifdef EGL_GL_COLORSPACE_LINEAR
      int_type_c<EGL_GL_COLORSPACE_LINEAR>>
#else
      int_type_i>
#endif
      gl_colorspace_linear;

    c_api::opt_constant<
      mp_list<eglplus::gl_colorspace>,
#ifdef EGL_GL_COLORSPACE_SRGB
      int_type_c<EGL_GL_COLORSPACE_SRGB>>
#else
      int_type_i>
#endif
      gl_colorspace_srgb;

    c_api::opt_constant<
      mp_list<eglplus::config_caveat>,
#ifdef EGL_NONE
      int_type_c<EGL_NONE>>
#else
      int_type_i>
#endif
      none;

    basic_egl_constants(ApiTraits& traits, basic_egl_c_api<ApiTraits>& api);
};
//------------------------------------------------------------------------------
template <typename ApiTraits>
basic_egl_constants<ApiTraits>::basic_egl_constants(
  ApiTraits& traits,
  basic_egl_c_api<ApiTraits>& api)
  : success("SUCCESS", traits, api)
  , not_initialized("NOT_INITIALIZED", traits, api)
  , bad_access("BAD_ACCESS", traits, api)
  , bad_alloc("BAD_ALLOC", traits, api)
  , bad_attribute("BAD_ATTRIBUTE", traits, api)
  , bad_context("BAD_CONTEXT", traits, api)
  , bad_config("BAD_CONFIG", traits, api)
  , bad_current_surface("BAD_CURRENT_SURFACE", traits, api)
  , bad_display("BAD_DISPLAY", traits, api)
  , bad_surface("BAD_SURFACE", traits, api)
  , bad_match("BAD_MATCH", traits, api)
  , bad_parameter("BAD_PARAMETER", traits, api)
  , bad_native_pixmap("BAD_NATIVE_PIXMAP", traits, api)
  , bad_native_window("BAD_NATIVE_WINDOW", traits, api)
  , context_lost("CONTEXT_LOST", traits, api)
  , true_("TRUE", traits, api)
  , false_("FALSE", traits, api)
  , platform_device("PLATFORM_DEVICE_EXT", traits, api)
  , platform_x11("PLATFORM_X11_EXT", traits, api)
  , platform_xcb("PLATFORM_XCB_EXT", traits, api)
  , platform_wayland("PLATFORM_WAYLAND_EXT", traits, api)
  , platform_gbm_mesa("PLATFORM_GBM_MESA", traits, api)
  , platform_surfaceless("PLATFORM_SURFACELESS_MESA", traits, api)
  , platform_android("PLATFORM_ANDROID_KHR", traits, api)
  , client_apis("CLIENT_APIS", traits, api)
  , vendor("VENDOR", traits, api)
  , version("VERSION", traits, api)
  , renderer("RENDERER_EXT", traits, api)
  , extensions("EXTENSIONS", traits, api)
  , drm_device_file("DRM_DEVICE_FILE_EXT", traits, api)
  , drm_master_fd("DRM_MASTER_FD_EXT", traits, api)
  , config_id("CONFIG_ID", traits, api)
  , conformant("CONFORMANT", traits, api)
  , surface_type("SURFACE_TYPE", traits, api)
  , renderable_type("RENDERABLE_TYPE", traits, api)
  , color_buffer_type("RENDERABLE_TYPE", traits, api)
  , buffer_size("BUFFER_SIZE", traits, api)
  , red_size("RED_SIZE", traits, api)
  , green_size("GREEN_SIZE", traits, api)
  , blue_size("BLUE_SIZE", traits, api)
  , luminance_size("LUMINANCE_SIZE", traits, api)
  , alpha_size("ALPHA_SIZE", traits, api)
  , alpha_mask_size("ALPHA_MASK_SIZE", traits, api)
  , depth_size("DEPTH_SIZE", traits, api)
  , stencil_size("STENCIL_SIZE", traits, api)
  , sample_buffers("SAMPLE_BUFFERS", traits, api)
  , samples("SAMPLES", traits, api)
  , transparent_type("TRANSPARENT_TYPE", traits, api)
  , transparent_red_value("TRANSPARENT_RED_VALUE", traits, api)
  , transparent_green_value("TRANSPARENT_GREEN_VALUE", traits, api)
  , transparent_blue_value("TRANSPARENT_BLUE_VALUE", traits, api)
  , color_component_type("COLOR_COMPONENT_TYPE_EXT", traits, api)
  , level("LEVEL", traits, api)
  , pbuffer_width("PBUFFER_WIDTH", traits, api)
  , pbuffer_height("PBUFFER_HEIGHT", traits, api)
  , pbuffer_pixels("PBUFFER_PIXELS", traits, api)
  , max_swap_interval("MAX_SWAP_INTERVAL", traits, api)
  , min_swap_interval("MIN_SWAP_INTERVAL", traits, api)
  , width("WIDTH", traits, api)
  , height("HEIGHT", traits, api)
  , largest_pbuffer("LARGEST_PBUFFER", traits, api)
  , gl_colorspace("GL_COLORSPACE", traits, api)
  , texture_target("TEXTURE_TARGET", traits, api)
  , mipmap_level("MIPMAP_LEVEL", traits, api)
  , multisample_resolve("MULTISAMPLE_RESOLVE", traits, api)
  , swap_behavior("SWAP_BEHAVIOR", traits, api)
  , context_major_version("CONTEXT_MAJOR_VERSION", traits, api)
  , context_minor_version("CONTEXT_MINOR_VERSION", traits, api)
  , context_opengl_profile_mask("CONTEXT_OPENGL_PROFILE_MASK", traits, api)
  , context_opengl_forward_compatible(
      "CONTEXT_OPENGL_FORWARD_COMPATIBLE",
      traits,
      api)
  , context_opengl_debug("CONTEXT_OPENGL_DEBUG", traits, api)
  , context_opengl_robust_access("CONTEXT_OPENGL_ROBUST_ACCESS", traits, api)
  , window_bit("WINDOW_BIT", traits, api)
  , pixmap_bit("PIXMAP_BIT", traits, api)
  , pbuffer_bit("PBUFFER_BIT", traits, api)
  , stream_bit("STREAM_BIT_KHR", traits, api)
  , multisample_resolve_box_bit("MULTISAMPLE_RESOLVE_BOX_BIT", traits, api)
  , swap_behavior_preserved_bit("SWAP_BEHAVIOR_PRESERVED_BIT", traits, api)
  , vg_colorspace_linear_bit("VG_COLORSPACE_LINEAR_BIT", traits, api)
  , vg_alpha_format_pre_bit_bit("VG_ALPHA_FORMAT_PRE_BIT_BIT", traits, api)
  , consumer_latency_usec("CONSUMER_LATENCY_USEC_KHR", traits, api)
  , consumer_acquire_timeout_usec(
      "CONSUMER_ACQUIRE_TIMEOUT_USEC_KHR",
      traits,
      api)
  , producer_frame("PRODUCER_FRAME_KHR", traits, api)
  , consumer_frame("CONSUMER_FRAME_KHR", traits, api)
  , stream_state("STREAM_STATE_KHR", traits, api)
  , stream_state_created("STREAM_STATE_CREATED_KHR", traits, api)
  , stream_state_connecting("STREAM_STATE_CONNECTING_KHR", traits, api)
  , stream_state_empty("STREAM_STATE_EMPTY_KHR", traits, api)
  , stream_state_new_frame_available(
      "STREAM_STATE_NEW_FRAME_AVAILABLE_KHR",
      traits,
      api)
  , stream_state_old_frame_available(
      "STREAM_STATE_OLD_FRAME_AVAILABLE_KHR",
      traits,
      api)
  , stream_state_disconnected("STREAM_STATE_DISCONNECTED_KHR", traits, api)
  , image_preserved("IMAGE_PRESERVED_KHR", traits, api)
  , opengl_bit("OPENGL_BIT", traits, api)
  , opengl_es_bit("OPENGL_ES_BIT", traits, api)
  , opengl_es2_bit("OPENGL_ES2_BIT", traits, api)
  , opengl_es3_bit("OPENGL_ES3_BIT", traits, api)
  , openvg_bit("OPENVG_BIT", traits, api)
  , opengl_api("OPENGL_API", traits, api)
  , opengl_es_api("OPENGL_ES_API", traits, api)
  , openvg_api("OPENVG_API", traits, api)
  , context_opengl_core_profile_bit(
      "CONTEXT_OPENGL_CORE_PROFILE_BIT",
      traits,
      api)
  , context_opengl_compatibility_profile_bit(
      "CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT",
      traits,
      api)
  , rgb_buffer("RGB_BUFFER", traits, api)
  , luminance_buffer("LUMINANCE_BUFFER", traits, api)
  , color_component_type_fixed("COLOR_COMPONENT_TYPE_FIXED_EXT", traits, api)
  , color_component_type_float("COLOR_COMPONENT_TYPE_FLOAT_EXT", traits, api)
  , read("READ", traits, api)
  , draw("DRAW", traits, api)
  , sync_fence("sync_fence", traits, api)
  , sync_cl_event("sync_cl_event", traits, api)
  , no_texture("no_texture", traits, api)
  , texture_2d("texture_rgba", traits, api)
  , texture_rgb("texture_rgb", traits, api)
  , texture_rgba("texture_rgba", traits, api)
  , gl_colorspace_linear("gl_colorspace_linear", traits, api)
  , gl_colorspace_srgb("gl_colorspace_srgb", traits, api)
  , none("NONE", traits, api) {}
//------------------------------------------------------------------------------
} // namespace eglplus
} // namespace eagine
