/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///
module;

#if __has_include(<EGL/egl.h>)
#include <EGL/egl.h>
#define EAGINE_HAS_EGL 1

#ifndef EGL_PLATFORM_DEVICE_EXT
#define EGL_PLATFORM_DEVICE_EXT 0x313F
#endif
#else
#define EAGINE_HAS_EGL 0
#endif

export module eagine.eglplus:api;
import std;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.string;
import eagine.core.c_api;
import :config;
import :enum_types;
import :api_traits;
import :attributes;
import :extensions;
import :constants;
import :objects;
import :c_api;

namespace eagine::eglplus {
using c_api::adapted_function;
using c_api::simple_adapted_function;
//------------------------------------------------------------------------------
/// @brief Class wrapping the functions from the EGL API.
/// @ingroup egl_api_wrap
/// @see basic_egl_constants
/// @see basic_egl_c_api
export template <typename ApiTraits>
class basic_egl_operations : public basic_egl_c_api<ApiTraits> {

public:
    using api_traits = ApiTraits;
    using egl_api = basic_egl_c_api<ApiTraits>;

    using void_ptr_type = typename egl_types::void_ptr_type;
    using int_type = typename egl_types::int_type;
    using bool_type = typename egl_types::bool_type;
    using char_type = typename egl_types::char_type;
    using enum_type = typename egl_types::enum_type;
    using time_type = typename egl_types::time_type;
    using attrib_type = typename egl_types::attrib_type;
    using device_type = typename egl_types::device_type;
    using native_display_type = typename egl_types::native_display_type;
    using native_window_type = typename egl_types::native_window_type;
    using native_pixmap_type = typename egl_types::native_pixmap_type;
    using client_buffer_type = typename egl_types::client_buffer_type;
    using config_type = typename egl_types::config_type;
    using output_layer_type = typename egl_types::output_layer_type;
    using output_port_type = typename egl_types::output_port_type;

    // extensions
    template <typename... Args>
    using extension = basic_egl_extension<ApiTraits, Args...>;

    extension<> EXT_device_base;
    extension<> EXT_device_enumeration;
    extension<> EXT_device_query;
    extension<> EXT_device_query_name;
    extension<device_handle> EXT_device_drm;
    extension<device_handle> MESA_device_software;

    extension<> EXT_platform_base;
    extension<> EXT_platform_device;
    extension<> EXT_platform_x11;
    extension<> EXT_platform_xcb;
    extension<> EXT_platform_wayland;
    extension<> KHR_platform_gbm;
    extension<> MESA_platform_surfaceless;

    extension<display_handle> EXT_create_context_robustness;
    extension<display_handle> EXT_swap_buffers_with_damage;

    extension<display_handle> EXT_output_base;
    extension<display_handle> EXT_output_drm;
    extension<display_handle> EXT_stream_consumer_egloutput;

    extension<display_handle> EXT_pixel_format_float;

    extension<display_handle> MESA_configless_context;
    extension<display_handle> MESA_query_driver;

    using _query_devices_t = c_api::combined<
      simple_adapted_function<
        &egl_api::QueryDevices,
        c_api::collapsed<bool_type>(span<device_type>, int_type&)>,
      simple_adapted_function<
        &egl_api::QueryDevices,
        c_api::head_transformed<int_type, 2, 1>(span<device_type>)>>;

    struct : _query_devices_t {
        using base = _query_devices_t;
        using base::base;
        using base::operator();

        auto count() const noexcept {
            int_type ret_count{0};
            return base::operator()({}, ret_count)
              .transform_if([&ret_count](auto, bool valid) {
                  return limit_cast<span_size_t>(valid ? ret_count : 0);
              });
        }
    } query_devices{*this};

    simple_adapted_function<
      &egl_api::QueryDeviceString,
      string_view(device_handle, device_string_query)>
      query_device_string{*this};

    // get_device_extensions
    auto get_device_extensions(device_handle dev) const noexcept {
        return query_device_string(dev, device_string_query(EGL_EXTENSIONS))
          .transform([](auto src) { return split_into_string_list(src, ' '); });
    }

    c_api::combined<
      simple_adapted_function<
        &egl_api::GetPlatformDisplay,
        display_handle(platform, void_ptr_type, span<const attrib_type>)>,
      simple_adapted_function<
        &egl_api::GetPlatformDisplay,
        display_handle(platform, void_ptr_type, c_api::defaulted)>,
      simple_adapted_function<
        &egl_api::GetPlatformDisplay,
        display_handle(
          c_api::substituted<EGL_PLATFORM_DEVICE_EXT>,
          device_handle,
          c_api::defaulted)>>
      get_platform_display{*this};

    using _get_display_t = simple_adapted_function<
      &egl_api::GetDisplay,
      display_handle(native_display_type)>;

    struct : _get_display_t {
        using base = _get_display_t;
        using base::base;
        using base::operator();

        constexpr auto operator()() const noexcept {
#ifdef EGL_DEFAULT_DISPLAY
            return base::operator()(EGL_DEFAULT_DISPLAY);
#else
            return base::fail();
#endif
        }
    } get_display{*this};

    simple_adapted_function<
      &egl_api::GetDisplayDriverName,
      string_view(display_handle)>
      get_display_driver_name{*this};

    using _initialize_t = simple_adapted_function<
      &egl_api::Initialize,
      c_api::collapsed<bool_type>(display_handle, int&, int&)>;

    struct : _initialize_t {
        using base = _initialize_t;
        using base::base;
        using base::operator();

        constexpr auto operator()(display_handle disp) const noexcept {
            int_type maj{-1};
            int_type min{-1};
            return base::operator()(disp, maj, min);
        }
    } initialize{*this};

    simple_adapted_function<
      &egl_api::Terminate,
      c_api::collapsed<bool_type>(display_handle)>
      terminate{*this};

    using _get_configs_t = c_api::combined<
      simple_adapted_function<
        &egl_api::GetConfigs,
        c_api::collapsed<bool_type>(display_handle, span<config_type>, int_type&)>,
      simple_adapted_function<
        &egl_api::GetConfigs,
        c_api::head_transformed<int_type, 4, 2>(
          display_handle,
          span<config_type> dest)>>;

    struct : _get_configs_t {
        using base = _get_configs_t;
        using base::base;
        using base::operator();

        auto count(display_handle disp) const noexcept {
            int_type ret_count{0};
            return base::operator()(disp, {}, ret_count)
              .transform_if([&ret_count](auto, bool valid) {
                  return limit_cast<span_size_t>(valid ? ret_count : 0);
              });
        }
    } get_configs{*this};

    using _choose_config_t = c_api::combined<
      simple_adapted_function<
        &egl_api::ChooseConfig,
        c_api::collapsed<bool_type>(
          display_handle,
          span<const int_type>,
          span<config_type>,
          int_type&)>,
      simple_adapted_function<
        &egl_api::ChooseConfig,
        c_api::head_transformed<int_type, 5, 3>(
          display_handle,
          span<const int_type>,
          span<config_type>)>>;

    struct : _choose_config_t {
        using base = _choose_config_t;
        using base::base;
        using base::operator();

        auto count(display_handle disp, span<const int_type> attribs)
          const noexcept {
            int_type ret_count{0};
            return base::operator()(disp, attribs, {}, ret_count)
              .transform_if([&ret_count](auto, bool valid) {
                  return limit_cast<span_size_t>(valid ? ret_count : 0);
              });
        }

        auto count(display_handle disp, const config_attributes& attribs)
          const noexcept {
            return count(disp, attribs.get());
        }

        auto count(display_handle disp, const config_attribute_value& attribs)
          const noexcept {
            return count(disp, config_attributes{attribs});
        }

        auto operator()(
          display_handle disp,
          const config_attribute_value& attribs,
          span<config_type> dest) const noexcept {
            return base::operator()(disp, config_attributes{attribs}, dest);
        }

        auto operator()(display_handle disp, const config_attributes& attribs)
          const noexcept {
            config_type result{};
            return (*this)(disp, attribs.get(), cover_one(&result))
              .replaced_with(result);
        }

        auto operator()(
          display_handle disp,
          const config_attribute_value& attribs) const noexcept {
            return (*this)(disp, config_attributes{attribs});
        }
    } choose_config{*this};

    simple_adapted_function<
      &egl_api::GetConfigAttrib,
      c_api::returned<int_type>(
        display_handle,
        config_type,
        config_attribute,
        c_api::returned<int_type>)>
      get_config_attrib{*this};

    simple_adapted_function<
      &egl_api::CreateWindowSurface,
      owned_surface_handle(
        display_handle,
        config_type,
        native_window_type,
        surface_attributes)>
      create_window_surface{*this};

    simple_adapted_function<
      &egl_api::CreatePbufferSurface,
      owned_surface_handle(display_handle, config_type, surface_attributes)>
      create_pbuffer_surface{*this};

    simple_adapted_function<
      &egl_api::CreatePixmapSurface,
      owned_surface_handle(
        display_handle,
        config_type,
        native_pixmap_type,
        surface_attributes)>
      create_pixmap_surface{*this};

    simple_adapted_function<
      &egl_api::DestroySurface,
      c_api::collapsed<bool_type>(display_handle, owned_surface_handle)>
      destroy_surface{*this};

    auto clean_up(owned_surface_handle surf, display_handle disp)
      const noexcept {
        return destroy_surface(disp, std::move(surf));
    }

    simple_adapted_function<
      &egl_api::GetCurrentSurface,
      surface_handle(read_draw)>
      get_current_surface{*this};

    simple_adapted_function<
      &egl_api::SurfaceAttrib,
      c_api::collapsed<
        bool_type>(display_handle, surface_handle, surface_attribute, int_type)>
      surface_attrib{*this};

    simple_adapted_function<
      &egl_api::QuerySurface,
      int_type(display_handle, surface_handle, surface_attribute)>
      query_surface{*this};

    simple_adapted_function<
      &egl_api::CreateStream,
      owned_stream_handle(display_handle, stream_attributes)>
      create_stream{*this};

    simple_adapted_function<
      &egl_api::DestroyStream,
      c_api::collapsed<bool_type>(display_handle, owned_stream_handle)>
      destroy_stream{*this};

    auto clean_up(owned_stream_handle strm, display_handle disp) const noexcept {
        return destroy_stream(disp, std::move(strm));
    }

    simple_adapted_function<
      &egl_api::StreamAttrib,
      c_api::collapsed<
        bool_type>(display_handle, stream_handle, stream_attribute, int_type)>
      stream_attrib{*this};

    simple_adapted_function<
      &egl_api::QueryStream,
      int_type(display_handle, stream_handle, stream_attribute)>
      query_stream{*this};

    simple_adapted_function<
      &egl_api::StreamConsumerGLTextureExternal,
      c_api::collapsed<bool_type>(display_handle, stream_handle)>
      stream_consumer_gl_texture_external{*this};

    simple_adapted_function<
      &egl_api::StreamConsumerAcquire,
      c_api::collapsed<bool_type>(display_handle, stream_handle)>
      stream_consumer_acquire{*this};

    simple_adapted_function<
      &egl_api::StreamConsumerRelease,
      c_api::collapsed<bool_type>(display_handle, stream_handle)>
      stream_consumer_release{*this};

    using _get_output_layers_t = c_api::combined<
      simple_adapted_function<
        &egl_api::GetOutputLayers,
        c_api::collapsed<bool_type>(
          display_handle,
          span<const attrib_type>,
          span<output_layer_type>,
          int_type&)>,
      simple_adapted_function<
        &egl_api::GetOutputLayers,
        c_api::head_transformed<int_type, 5, 3>(
          display_handle,
          output_layer_attributes,
          span<output_layer_type>)>>;

    struct : _get_output_layers_t {
        using base = _get_output_layers_t;
        using base::base;
        using base::operator();

        auto count(display_handle disp) const noexcept {
            int_type ret_count{0};
            return base::operator()(disp, {}, {}, ret_count)
              .transform_if([&ret_count](auto, bool valid) {
                  return limit_cast<span_size_t>(valid ? ret_count : 0);
              });
        }
    } get_output_layers{*this};

    simple_adapted_function<
      &egl_api::OutputLayerAttrib,
      c_api::collapsed<
        bool_type>(display_handle, output_layer_handle, output_layer_attribute)>
      output_layer_attrib{*this};

    simple_adapted_function<
      &egl_api::QueryOutputLayerAttrib,
      int_type(display_handle, output_layer_handle, output_layer_attribute)>
      query_output_layer_attrib{*this};

    simple_adapted_function<
      &egl_api::QueryOutputLayerString,
      string_view(display_handle, output_layer_handle, output_layer_string_query)>
      query_output_layer_string{*this};

    using _get_output_ports_t = c_api::combined<
      simple_adapted_function<
        &egl_api::GetOutputPorts,
        c_api::collapsed<bool_type>(
          display_handle,
          span<const attrib_type>,
          span<output_port_type>,
          int_type&)>,
      simple_adapted_function<
        &egl_api::GetOutputPorts,
        c_api::head_transformed<int_type, 5, 3>(
          display_handle,
          output_port_attributes,
          span<output_port_type>)>>;

    struct : _get_output_ports_t {
        using base = _get_output_ports_t;
        using base::base;
        using base::operator();

        auto count(display_handle disp) const noexcept {
            int_type ret_count{0};
            return base::operator()(disp, {}, {}, ret_count)
              .transform_if([&ret_count](auto, bool valid) {
                  return limit_cast<span_size_t>(valid ? ret_count : 0);
              });
        }
    } get_output_ports{*this};

    simple_adapted_function<
      &egl_api::OutputPortAttrib,
      c_api::collapsed<
        bool_type>(display_handle, output_port_handle, output_port_attribute)>
      output_port_attrib{*this};

    simple_adapted_function<
      &egl_api::QueryOutputPortAttrib,
      int_type(display_handle, output_port_handle, output_port_attribute)>
      query_output_port_attrib{*this};

    simple_adapted_function<
      &egl_api::QueryOutputPortString,
      string_view(display_handle, output_port_handle, output_port_string_query)>
      query_output_port_string{*this};

    simple_adapted_function<
      &egl_api::CreateImage,
      owned_image_handle(
        display_handle,
        context_handle,
        image_target,
        client_buffer_type,
        image_attributes)>
      create_image{*this};

    simple_adapted_function<
      &egl_api::DestroyImage,
      c_api::collapsed<bool_type>(display_handle, owned_image_handle)>
      destroy_image{*this};

    auto clean_up(owned_image_handle imge, display_handle disp) const noexcept {
        return destroy_image(disp, std::move(imge));
    }

    simple_adapted_function<
      &egl_api::BindAPI,
      c_api::collapsed<bool_type>(client_api)>
      bind_api{*this};

    simple_adapted_function<&egl_api::QueryAPI, client_api()> query_api{*this};

    simple_adapted_function<
      &egl_api::CreateContext,
      owned_context_handle(
        display_handle,
        config_type,
        context_handle,
        context_attributes)>
      create_context{*this};

    simple_adapted_function<
      &egl_api::DestroyContext,
      c_api::collapsed<bool_type>(display_handle, owned_context_handle)>
      destroy_context{*this};

    auto clean_up(owned_context_handle ctxt, display_handle disp)
      const noexcept {
        return destroy_context(disp, std::move(ctxt));
    }

    using _make_current_t = simple_adapted_function<
      &egl_api::MakeCurrent,
      c_api::collapsed<bool_type>(
        display_handle,
        surface_handle,
        surface_handle,
        context_handle)>;

    struct : _make_current_t {
        using base = _make_current_t;
        using base::base;
        using base::operator();

        constexpr auto operator()(
          display_handle disp,
          surface_handle surf,
          context_handle ctxt) const noexcept {
            return base::operator()(disp, surf, surf, ctxt);
        }

        constexpr auto none(display_handle disp) const noexcept {
            return base::operator()(
              disp, surface_handle{}, surface_handle{}, context_handle{});
        }
    } make_current{*this};

    simple_adapted_function<&egl_api::GetCurrentContext, context_handle()>
      get_current_context{*this};

    simple_adapted_function<&egl_api::WaitClient, c_api::collapsed<bool_type>()>
      wait_client{*this};

    c_api::combined<
      simple_adapted_function<
        &egl_api::WaitNative,
        c_api::collapsed<bool_type>(engine)>,
      simple_adapted_function<
        &egl_api::WaitNative,
        c_api::collapsed<bool_type>(c_api::substituted<EGL_CORE_NATIVE_ENGINE>)>>
      wait_native{*this};

    simple_adapted_function<
      &egl_api::CreateSync,
      sync_handle(display_handle, sync_type, sync_attributes)>
      create_sync{*this};

    using _client_wait_sync_t = c_api::combined<
      simple_adapted_function<
        &egl_api::ClientWaitSync,
        c_api::collapsed<
          bool_type>(display_handle, sync_handle, int_type, time_type)>,
      simple_adapted_function<
        &egl_api::ClientWaitSync,
        c_api::collapsed<bool_type>(
          display_handle,
          sync_handle,
          c_api::defaulted,
          c_api::substituted<EGL_FOREVER>)>>;

    struct : _client_wait_sync_t {
        using base = _client_wait_sync_t;
        using base::base;

        template <typename R, typename P>
        constexpr auto operator()(
          display_handle disp,
          sync_handle sync,
          std::chrono::duration<R, P> timeout) const noexcept {
            return base::operator()(
              disp, sync, 0, std::chrono::nanoseconds(timeout).count());
        }
    } client_wait_sync{*this};

    simple_adapted_function<
      &egl_api::WaitSync,
      c_api::collapsed<bool_type>(display_handle, sync_handle)>
      wait_sync{*this};

    simple_adapted_function<
      &egl_api::DestroySync,
      c_api::collapsed<bool_type>(display_handle, sync_handle)>
      destroy_sync{*this};

    simple_adapted_function<
      &egl_api::QueryString,
      string_view(display_handle, string_query)>
      query_string{*this};

    // query_strings
    auto query_strings(display_handle disp, string_query query, char separator)
      const noexcept {
        return query_string(disp, query).transform([separator](auto src) {
            return split_into_string_list(src, separator);
        });
    }

    // get_client_apis
    auto get_client_apis(display_handle disp) const noexcept {
        return query_string(disp, string_query(EGL_CLIENT_APIS))
          .transform([](auto src) { return split_into_string_list(src, ' '); });
    }

    auto get_client_api_bits(display_handle disp) const noexcept {
        c_api::enum_bitfield<client_api_bit> result{};

        if(ok apis{get_client_apis(disp)}) {
            for(auto api : apis) {
                if(are_equal(api, string_view("OpenGL"))) {
                    result.add(client_api_bit(EGL_OPENGL_BIT));
                }
                if(are_equal(api, string_view("OpenGL_ES"))) {
                    result.add(client_api_bit(EGL_OPENGL_ES_BIT));
                }
                if(are_equal(api, string_view("OpenVG"))) {
                    result.add(client_api_bit(EGL_OPENVG_BIT));
                }
            }
        }

        return result;
    }

    // get_extensions
    auto get_extensions() const noexcept {
#if defined(EGL_EXTENSIONS) && defined(EGL_NO_DISPLAY)
        return query_string(
                 display_handle(EGL_NO_DISPLAY), string_query(EGL_EXTENSIONS))
#else
        return query_string
          .fail()
#endif
          .transform([](auto src) { return split_into_string_list(src, ' '); });
    }

    // get_extensions
    auto get_extensions(display_handle disp) const noexcept {
        return query_string(disp, string_query(EGL_EXTENSIONS))
          .transform([](auto src) { return split_into_string_list(src, ' '); });
    }

    // has_extension
    auto has_extension(string_view which) const noexcept {
        if(ok extensions{get_extensions()}) {
            for(auto ext_name : extensions) {
                if(ends_with(ext_name, which)) {
                    return true;
                }
            }
        }
        return false;
    }

    auto has_extension(device_handle dev, string_view which) const noexcept {
        if(ok extensions{get_device_extensions(dev)}) {
            for(auto ext_name : extensions) {
                if(ends_with(ext_name, which)) {
                    return true;
                }
            }
        }
        return false;
    }

    auto has_extension(display_handle disp, string_view which) const noexcept {
        if(ok extensions{get_extensions(disp)}) {
            for(auto ext_name : extensions) {
                if(ends_with(ext_name, which)) {
                    return true;
                }
            }
        }
        return false;
    }

    simple_adapted_function<
      &egl_api::SwapInterval,
      c_api::collapsed<bool_type>(display_handle, int_type)>
      swap_interval{*this};

    simple_adapted_function<
      &egl_api::SwapBuffers,
      c_api::collapsed<bool_type>(display_handle, surface_handle)>
      swap_buffers{*this};

    simple_adapted_function<
      &egl_api::SwapBuffersWithDamage,
      c_api::collapsed<
        bool_type>(display_handle, surface_handle, span<const int_type>)>
      swap_buffers_with_damage{*this};

    simple_adapted_function<
      &egl_api::ReleaseThread,
      c_api::collapsed<bool_type>()>
      release_thread{*this};

    basic_egl_operations(api_traits& traits);
};
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
export template <typename ApiTraits>
class basic_egl_api
  : protected ApiTraits
  , public basic_egl_operations<ApiTraits>
  , public basic_egl_constants<ApiTraits> {
public:
    basic_egl_api(ApiTraits traits)
      : ApiTraits{std::move(traits)}
      , basic_egl_operations<ApiTraits>{*static_cast<ApiTraits*>(this)}
      , basic_egl_constants<ApiTraits> {
        *static_cast<ApiTraits*>(this),
          *static_cast<basic_egl_operations<ApiTraits>*>(this)
    }
    {}

    basic_egl_api()
      : basic_egl_api{ApiTraits{}} {}

    auto operations() const noexcept -> const basic_egl_operations<ApiTraits>& {
        return *this;
    }

    auto constants() const noexcept -> const basic_egl_constants<ApiTraits>& {
        return *this;
    }
};

export template <std::size_t I, typename ApiTraits>
auto get(const basic_egl_api<ApiTraits>& x) noexcept -> const
  typename std::tuple_element<I, basic_egl_api<ApiTraits>>::type& {
    return x;
}
//------------------------------------------------------------------------------
/// @brief Alias for the default instantation of basic_egl_api.
/// @ingroup egl_api_wrap
export using egl_api = basic_egl_api<egl_api_traits>;
//------------------------------------------------------------------------------
} // namespace eagine::eglplus

// NOLINTNEXTLINE(cert-dcl58-cpp)
namespace std {
//------------------------------------------------------------------------------
template <typename ApiTraits>
struct tuple_size<eagine::eglplus::basic_egl_api<ApiTraits>>
  : integral_constant<std::size_t, 2> {};

template <typename ApiTraits>
struct tuple_element<0, eagine::eglplus::basic_egl_api<ApiTraits>>
  : type_identity<eagine::eglplus::basic_egl_operations<ApiTraits>> {};

template <typename ApiTraits>
struct tuple_element<1, eagine::eglplus::basic_egl_api<ApiTraits>>
  : type_identity<eagine::eglplus::basic_egl_constants<ApiTraits>> {};
//------------------------------------------------------------------------------
} // namespace std
namespace eagine::eglplus {
//------------------------------------------------------------------------------
export template <typename ApiTraits>
using basic_egl_api_reference =
  c_api::basic_api_reference<basic_egl_api<ApiTraits>>;

export using egl_api_reference = basic_egl_api_reference<egl_api_traits>;
} // namespace eagine::eglplus

