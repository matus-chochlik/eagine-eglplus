/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_EGLPLUS_BASIC_EGL_API_HPP
#define EAGINE_EGLPLUS_BASIC_EGL_API_HPP

#include "egl_api/api.hpp"
#include "egl_api/api_traits.hpp"
#include "egl_api/constants.hpp"

namespace eagine::eglplus {
//------------------------------------------------------------------------------
template <typename ApiTraits>
class basic_egl_api
  : protected ApiTraits
  , public basic_egl_operations<ApiTraits>
  , public basic_egl_constants<ApiTraits> {
public:
    basic_egl_api(ApiTraits traits)
      : ApiTraits{std::move(traits)}
      , basic_egl_operations<ApiTraits>{*static_cast<ApiTraits*>(this)}
      , basic_egl_constants<ApiTraits>{
          *static_cast<ApiTraits*>(this),
          *static_cast<basic_egl_operations<ApiTraits>*>(this)} {}

    basic_egl_api()
      : basic_egl_api{ApiTraits{}} {}

    auto operations() const noexcept -> const basic_egl_operations<ApiTraits>& {
        return *this;
    }

    auto constants() const noexcept -> const basic_egl_constants<ApiTraits>& {
        return *this;
    }
};

template <std::size_t I, typename ApiTraits>
auto get(const basic_egl_api<ApiTraits>& x) noexcept -> const
  typename std::tuple_element<I, basic_egl_api<ApiTraits>>::type& {
    return x;
}
//------------------------------------------------------------------------------
} // namespace eagine::eglplus

// NOLINTNEXTLINE(cert-dcl58-cpp)
namespace std {
//------------------------------------------------------------------------------
template <typename ApiTraits>
struct tuple_size<eagine::eglplus::basic_egl_api<ApiTraits>>
  : public std::integral_constant<std::size_t, 2> {};

template <typename ApiTraits>
struct tuple_element<0, eagine::eglplus::basic_egl_api<ApiTraits>> {
    using type = eagine::eglplus::basic_egl_operations<ApiTraits>;
};

template <typename ApiTraits>
struct tuple_element<1, eagine::eglplus::basic_egl_api<ApiTraits>> {
    using type = eagine::eglplus::basic_egl_constants<ApiTraits>;
};
//------------------------------------------------------------------------------
} // namespace std

#endif // EAGINE_EGLPLUS_BASIC_EGL_API_HPP
