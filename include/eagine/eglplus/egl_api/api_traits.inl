/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

namespace eagine::eglplus {
//------------------------------------------------------------------------------
template <typename Api, typename Tag, typename Signature>
auto egl_api_traits::link_function(
  Api& api,
  const Tag,
  const string_view name,
  const std::type_identity<Signature>) -> std::add_pointer_t<Signature> {
    if(api.GetProcAddress && api.GetError) {
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
