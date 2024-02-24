# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
# https://www.boost.org/LICENSE_1_0.txt
add_subdirectory(modules)
add_subdirectory(app)

set(EAGINE_EGLPLUS_EXPORT_TARGETS)

if(TARGET eagine-eglplus)
	add_library(EAGine::EGLplus INTERFACE IMPORTED GLOBAL)
	target_link_libraries(
		EAGine::EGLplus
		INTERFACE
			eagine-eglplus
			eagine-eglplus-headers
	)
	list(
		APPEND EAGINE_EGLPLUS_EXPORT_TARGETS
			eagine-eglplus-headers
	)

	install(
		EXPORT EGLplus
		NAMESPACE EAGine::
		FILE EGLplus.cmake
		DESTINATION lib/cmake/EAGine
	)
endif()

install(
	TARGETS ${EAGINE_EGLPLUS_EXPORT_TARGETS}
	EXPORT EGLplus
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include
	PUBLIC_HEADER DESTINATION include
)

