# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
if(${WITH_MODULES})
	add_subdirectory(modules)
else()
	add_subdirectory(lib)
endif()

if(TARGET eagine-eglplus)
	add_library(EAGine::EGLplus INTERFACE IMPORTED GLOBAL)
	target_link_libraries(EAGine::EGLplus INTERFACE eagine-eglplus-headers)

	target_link_libraries(
		EAGine::EGLplus
		INTERFACE
			eagine-eglplus
	)

	install(
		TARGETS
			eagine-eglplus-headers
			EXPORT EGLplus
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib
		RUNTIME DESTINATION bin
		INCLUDES DESTINATION include
		PUBLIC_HEADER DESTINATION include
	)

	install(
		EXPORT EGLplus
		NAMESPACE EAGine::
		FILE EGLplus.cmake
		DESTINATION lib/cmake/EAGine
	)
endif()
