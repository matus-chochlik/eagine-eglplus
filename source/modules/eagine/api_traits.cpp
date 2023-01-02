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

export module eagine.eglplus:api_traits;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.c_api;
import :config;
import :result;
import <string>;

namespace eagine::eglplus {
//------------------------------------------------------------------------------
/// @brief Policy customizing the generic C-API wrappers for the EGL API
/// @ingroup egl_api_wrap
export class egl_api_traits : public c_api::default_traits {
public:
    /// @brief Alias for result type of currently unavailable functions.
    template <typename R>
    using no_result = egl_no_result<R>;

    /// @brief Alias for result type of functions.
    template <typename R>
    using result = egl_result<R>;

    /// @brief Alias for result type of optionally available functions.
    template <typename R>
    using opt_result = egl_opt_result<R>;

    /// @brief Links an EGL function with the specified name and Signature.
    template <typename Api, typename Tag, typename Signature>
    auto link_function(
      Api& api,
      const Tag,
      const string_view name,
      const std::type_identity<Signature>) -> std::add_pointer_t<Signature>;

private:
    std::string _full_name;
};
//------------------------------------------------------------------------------
template <typename Api, typename Tag, typename Signature>
auto egl_api_traits::link_function(
  Api& api,
  const Tag,
  const string_view name,
  const std::type_identity<Signature>) -> std::add_pointer_t<Signature> {
    if(api.GetProcAddress and api.GetError) {
        _full_name.clear();
        _full_name.reserve(3 + name.size() + 1);
        _full_name.append("egl");
        _full_name.append(name.data(), std::size_t(name.size()));
        auto func = api.GetProcAddress(_full_name.c_str());
        if(egl_types::error_code_no_error(api.GetError())) {
            return reinterpret_cast<std::remove_pointer_t<Signature>*>(func);
        }
    }
    return nullptr;
}
//------------------------------------------------------------------------------
} // namespace eagine::eglplus

