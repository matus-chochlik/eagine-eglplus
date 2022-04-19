/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_EGLPLUS_EGL_API_API_HPP
#define EAGINE_EGLPLUS_EGL_API_API_HPP

#include "c_api.hpp"
#include "config_attribs.hpp"
#include "context_attribs.hpp"
#include "enum_types.hpp"
#include "extensions.hpp"
#include "image_attribs.hpp"
#include "objects.hpp"
#include "output_layer_attribs.hpp"
#include "output_port_attribs.hpp"
#include "platform_attribs.hpp"
#include "stream_attribs.hpp"
#include "surface_attribs.hpp"
#include "sync_attribs.hpp"
#include <eagine/c_api/adapted_function.hpp>
#include <eagine/scope_exit.hpp>
#include <eagine/string_list.hpp>
#include <chrono>

namespace eagine::eglplus {
using c_api::adapted_function;
//------------------------------------------------------------------------------
/// @brief Class wrapping the functions from the EGL API.
/// @ingroup egl_api_wrap
/// @see basic_egl_constants
/// @see basic_egl_c_api
template <typename ApiTraits>
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
      adapted_function<
        &egl_api::QueryDevices,
        c_api::collapsed<bool_type>(span<device_type>, int_type&)>,
      adapted_function<
        &egl_api::QueryDevices,
        c_api::head_transformed<int_type, 2, 1>(span<device_type>)>>;

    struct : _query_devices_t {
        using base = _query_devices_t;
        using base::base;
        using base::operator();

        auto count() const noexcept {
            int_type ret_count{0};
            return base::operator()({}, ret_count)
              .transformed([&ret_count](bool valid) {
                  return limit_cast<span_size_t>(valid ? ret_count : 0);
              });
        }
    } query_devices{*this};

    adapted_function<
      &egl_api::QueryDeviceString,
      string_view(device_handle, device_string_query)>
      query_device_string{*this};

    // get_device_extensions
    auto get_device_extensions(device_handle dev) const noexcept {
        return query_device_string(dev, device_string_query(EGL_EXTENSIONS))
          .transformed(
            [](auto src, bool) { return split_into_string_list(src, ' '); });
    }

    c_api::combined<
      adapted_function<
        &egl_api::GetPlatformDisplay,
        display_handle(platform, void_ptr_type, span<const attrib_type>)>,
      adapted_function<
        &egl_api::GetPlatformDisplay,
        display_handle(platform, void_ptr_type, c_api::defaulted)>,
      adapted_function<
        &egl_api::GetPlatformDisplay,
        display_handle(
          c_api::substituted<EGL_PLATFORM_DEVICE_EXT>,
          device_handle,
          c_api::defaulted)>>
      get_platform_display{*this};

    using _get_display_t =
      adapted_function<&egl_api::GetDisplay, display_handle(native_display_type)>;

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

    adapted_function<&egl_api::GetDisplayDriverName, string_view(display_handle)>
      get_display_driver_name{*this};

    using _initialize_t = adapted_function<
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

    adapted_function<
      &egl_api::Terminate,
      c_api::collapsed<bool_type>(display_handle)>
      terminate{*this};

    using _get_configs_t = c_api::combined<
      adapted_function<
        &egl_api::GetConfigs,
        c_api::collapsed<bool_type>(display_handle, span<config_type>, int_type&)>,
      adapted_function<
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
              .transformed([&ret_count](bool valid) {
                  return limit_cast<span_size_t>(valid ? ret_count : 0);
              });
        }
    } get_configs{*this};

    using _choose_config_t = c_api::combined<
      adapted_function<
        &egl_api::ChooseConfig,
        c_api::collapsed<bool_type>(
          display_handle,
          span<const int_type>,
          span<config_type>,
          int_type&)>,
      adapted_function<
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
              .transformed([&ret_count](bool valid) {
                  return limit_cast<span_size_t>(valid ? ret_count : 0);
              });
        }

        auto count(display_handle disp, const config_attributes& attribs) const {
            return count(disp, attribs.get());
        }

        auto count(display_handle disp, const config_attribute_value& attribs)
          const {
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

    adapted_function<
      &egl_api::GetConfigAttrib,
      c_api::returned<int_type>(
        display_handle,
        config_type,
        config_attribute,
        c_api::returned<int_type>)>
      get_config_attrib{*this};

    adapted_function<
      &egl_api::CreateWindowSurface,
      surface_handle(
        display_handle,
        config_type,
        native_window_type,
        surface_attributes)>
      create_window_surface{*this};

    adapted_function<
      &egl_api::CreatePbufferSurface,
      surface_handle(display_handle, config_type, surface_attributes)>
      create_pbuffer_surface{*this};

    adapted_function<
      &egl_api::CreatePixmapSurface,
      surface_handle(
        display_handle,
        config_type,
        native_pixmap_type,
        surface_attributes)>
      create_pixmap_surface{*this};

    adapted_function<
      &egl_api::DestroySurface,
      c_api::collapsed<bool_type>(display_handle, surface_handle)>
      destroy_surface{*this};

    adapted_function<&egl_api::GetCurrentSurface, surface_handle(read_draw)>
      get_current_surface{*this};

    adapted_function<
      &egl_api::SurfaceAttrib,
      c_api::collapsed<
        bool_type>(display_handle, surface_handle, surface_attribute, int_type)>
      surface_attrib{*this};

    adapted_function<
      &egl_api::QuerySurface,
      int_type(display_handle, surface_handle, surface_attribute)>
      query_surface{*this};

    adapted_function<
      &egl_api::CreateStream,
      stream_handle(display_handle, stream_attributes)>
      create_stream{*this};

    adapted_function<
      &egl_api::DestroyStream,
      c_api::collapsed<bool_type>(display_handle, stream_handle)>
      destroy_stream{*this};

    adapted_function<
      &egl_api::StreamAttrib,
      c_api::collapsed<
        bool_type>(display_handle, stream_handle, stream_attribute, int_type)>
      stream_attrib{*this};

    adapted_function<
      &egl_api::QueryStream,
      int_type(display_handle, stream_handle, stream_attribute)>
      query_stream{*this};

    adapted_function<
      &egl_api::StreamConsumerGLTextureExternal,
      c_api::collapsed<bool_type>(display_handle, stream_handle)>
      stream_consumer_gl_texture_external{*this};

    adapted_function<
      &egl_api::StreamConsumerAcquire,
      c_api::collapsed<bool_type>(display_handle, stream_handle)>
      stream_consumer_acquire{*this};

    adapted_function<
      &egl_api::StreamConsumerRelease,
      c_api::collapsed<bool_type>(display_handle, stream_handle)>
      stream_consumer_release{*this};

    using _get_output_layers_t = c_api::combined<
      adapted_function<
        &egl_api::GetOutputLayers,
        c_api::collapsed<bool_type>(
          display_handle,
          span<const attrib_type>,
          span<output_layer_type>,
          int_type&)>,
      adapted_function<
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
              .transformed([&ret_count](bool valid) {
                  return limit_cast<span_size_t>(valid ? ret_count : 0);
              });
        }
    } get_output_layers{*this};

    adapted_function<
      &egl_api::OutputLayerAttrib,
      c_api::collapsed<
        bool_type>(display_handle, output_layer_handle, output_layer_attribute)>
      output_layer_attrib{*this};

    adapted_function<
      &egl_api::QueryOutputLayerAttrib,
      int_type(display_handle, output_layer_handle, output_layer_attribute)>
      query_output_layer_attrib{*this};

    adapted_function<
      &egl_api::QueryOutputLayerString,
      string_view(display_handle, output_layer_handle, output_layer_string_query)>
      query_output_layer_string{*this};

    using _get_output_ports_t = c_api::combined<
      adapted_function<
        &egl_api::GetOutputPorts,
        c_api::collapsed<bool_type>(
          display_handle,
          span<const attrib_type>,
          span<output_port_type>,
          int_type&)>,
      adapted_function<
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
              .transformed([&ret_count](bool valid) {
                  return limit_cast<span_size_t>(valid ? ret_count : 0);
              });
        }
    } get_output_ports{*this};

    adapted_function<
      &egl_api::OutputPortAttrib,
      c_api::collapsed<
        bool_type>(display_handle, output_port_handle, output_port_attribute)>
      output_port_attrib{*this};

    adapted_function<
      &egl_api::QueryOutputPortAttrib,
      int_type(display_handle, output_port_handle, output_port_attribute)>
      query_output_port_attrib{*this};

    adapted_function<
      &egl_api::QueryOutputPortString,
      string_view(display_handle, output_port_handle, output_port_string_query)>
      query_output_port_string{*this};

    adapted_function<
      &egl_api::CreateImage,
      image_handle(
        display_handle,
        context_handle,
        image_target,
        client_buffer_type,
        image_attributes)>
      create_image{*this};

    adapted_function<
      &egl_api::DestroyImage,
      c_api::collapsed<bool_type>(display_handle, image_handle)>
      destroy_image{*this};

    adapted_function<&egl_api::BindAPI, c_api::collapsed<bool_type>(client_api)>
      bind_api{*this};

    adapted_function<&egl_api::QueryAPI, client_api()> query_api{*this};

    adapted_function<
      &egl_api::CreateContext,
      context_handle(
        display_handle,
        config_type,
        context_handle,
        context_attributes)>
      create_context{*this};

    adapted_function<
      &egl_api::DestroyContext,
      c_api::collapsed<bool_type>(display_handle, context_handle)>
      destroy_context{*this};

    using _make_current_t = adapted_function<
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

    adapted_function<&egl_api::GetCurrentContext, context_handle()>
      get_current_context{*this};

    adapted_function<&egl_api::WaitClient, c_api::collapsed<bool_type>()>
      wait_client{*this};

    c_api::combined<
      adapted_function<&egl_api::WaitNative, c_api::collapsed<bool_type>(engine)>,
      adapted_function<
        &egl_api::WaitNative,
        c_api::collapsed<bool_type>(c_api::substituted<EGL_CORE_NATIVE_ENGINE>)>>
      wait_native{*this};

    adapted_function<
      &egl_api::CreateSync,
      sync_handle(display_handle, sync_type, sync_attributes)>
      create_sync{*this};

    using _client_wait_sync_t = c_api::combined<
      adapted_function<
        &egl_api::ClientWaitSync,
        c_api::collapsed<
          bool_type>(display_handle, sync_handle, int_type, time_type)>,
      adapted_function<
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

    adapted_function<
      &egl_api::WaitSync,
      c_api::collapsed<bool_type>(display_handle, sync_handle)>
      wait_sync{*this};

    adapted_function<
      &egl_api::DestroySync,
      c_api::collapsed<bool_type>(display_handle, sync_handle)>
      destroy_sync{*this};

    adapted_function<
      &egl_api::QueryString,
      string_view(display_handle, string_query)>
      query_string{*this};

    // query_strings
    auto query_strings(display_handle disp, string_query query, char separator)
      const noexcept {
        return query_string(disp, query)
          .transformed([separator](auto src, bool) {
              return split_into_string_list(src, separator);
          });
    }

    // get_client_apis
    auto get_client_apis(display_handle disp) const noexcept {
        return query_string(disp, string_query(EGL_CLIENT_APIS))
          .transformed(
            [](auto src, bool) { return split_into_string_list(src, ' '); });
    }

    auto get_client_api_bits(display_handle disp) const noexcept {
        enum_bitfield<client_api_bit> result{};

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
          .transformed(
            [](auto src, bool) { return split_into_string_list(src, ' '); });
    }

    // get_extensions
    auto get_extensions(display_handle disp) const noexcept {
        return query_string(disp, string_query(EGL_EXTENSIONS))
          .transformed(
            [](auto src, bool) { return split_into_string_list(src, ' '); });
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

    adapted_function<
      &egl_api::SwapInterval,
      c_api::collapsed<bool_type>(display_handle, int_type)>
      swap_interval{*this};

    adapted_function<
      &egl_api::SwapBuffers,
      c_api::collapsed<bool_type>(display_handle, surface_handle)>
      swap_buffers{*this};

    adapted_function<
      &egl_api::SwapBuffersWithDamage,
      c_api::collapsed<
        bool_type>(display_handle, surface_handle, span<const int_type>)>
      swap_buffers_with_damage{*this};

    adapted_function<&egl_api::ReleaseThread, c_api::collapsed<bool_type>()>
      release_thread{*this};

    basic_egl_operations(api_traits& traits);
};
//------------------------------------------------------------------------------
} // namespace eagine::eglplus

#endif // EAGINE_EGLPLUS_EGL_API_API_HPP
