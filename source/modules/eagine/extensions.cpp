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

export module eagine.eglplus:extensions;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.c_api;
import :config;
import :objects;

namespace eagine::eglplus {

export template <typename ApiTraits>
class basic_egl_operations;

/// @brief Wrapper for EGL extension information getter.
/// @ingroup egl_api_wrap
export template <typename ApiTraits, typename...>
class basic_egl_extension {
public:
    constexpr basic_egl_extension(
      const string_view name,
      const basic_egl_operations<ApiTraits>& api) noexcept
      : _api{api}
      , _name{name} {}

    /// @brief Tests if this extension is available.
    explicit operator bool() const noexcept {
        return _api.has_extension(_name);
    }

    /// @brief Tests if this extension is available.
    auto operator()() const noexcept -> bool {
        return _api.has_extension(_name);
    }

private:
    const basic_egl_operations<ApiTraits>& _api;
    string_view _name;
};

/// @brief Wrapper for display-specific EGL extension information getter.
/// @ingroup egl_api_wrap
export template <typename ApiTraits>
class basic_egl_extension<ApiTraits, display_handle> {
public:
    constexpr basic_egl_extension(
      const string_view name,
      const basic_egl_operations<ApiTraits>& api) noexcept
      : _api{api}
      , _name{name} {}

    /// @brief Tests if this extension is available on the specified display.
    auto operator()(const display_handle disp) const noexcept -> bool {
        return _api.has_extension(disp, _name);
    }

private:
    const basic_egl_operations<ApiTraits>& _api;
    string_view _name;
};

/// @brief Wrapper for device-specific EGL extension information getter.
/// @ingroup egl_api_wrap
export template <typename ApiTraits>
class basic_egl_extension<ApiTraits, device_handle> {
public:
    constexpr basic_egl_extension(
      const string_view name,
      const basic_egl_operations<ApiTraits>& api) noexcept
      : _api{api}
      , _name{name} {}

    /// @brief Tests if this extension is available on the specified device.
    auto operator()(const device_handle dev) const noexcept -> bool {
        return _api.has_extension(dev, _name);
    }

private:
    const basic_egl_operations<ApiTraits>& _api;
    string_view _name;
};

} // namespace eagine::eglplus

