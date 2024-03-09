# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
# https://www.boost.org/LICENSE_1_0.txt
eagine_add_module(
	eagine.eglplus PARTITION config
	IMPORTS
		std
		eagine.core.types
)

eagine_add_module(
	eagine.eglplus PARTITION enum_types
	IMPORTS
		std config
		eagine.core.types
		eagine.core.identifier
		eagine.core.c_api
)

eagine_add_module(
	eagine.eglplus PARTITION attributes
	IMPORTS
		std config enum_types
		eagine.core.types
		eagine.core.identifier
		eagine.core.c_api
)

eagine_add_module(
	eagine.eglplus PARTITION objects
	IMPORTS
		std config
		eagine.core.types
		eagine.core.identifier
		eagine.core.c_api
)

eagine_add_module(
	eagine.eglplus PARTITION result
	IMPORTS
		std config
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.eglplus PARTITION api_traits
	IMPORTS
		std config result
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.eglplus PARTITION c_api
	IMPORTS
		std config result
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.eglplus PARTITION extensions
	IMPORTS
		std config objects
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.eglplus PARTITION constants
	IMPORTS
		std config
		enum_types c_api
		eagine.core.types
		eagine.core.memory
		eagine.core.valid_if
		eagine.core.c_api
)

eagine_add_module(
	eagine.eglplus PARTITION from_string
	IMPORTS
		std enum_types constants
		eagine.core.types
		eagine.core.memory
		eagine.core.string
		eagine.core.valid_if
)

eagine_add_module(
	eagine.eglplus PARTITION api
	IMPORTS
		std config
		enum_types api_traits
		attributes constants
		extensions c_api
		eagine.core.types
		eagine.core.memory
		eagine.core.string
		eagine.core.c_api
		eagine.core.main_ctx
)

eagine_add_module(
	eagine.eglplus
	SOURCES
		constants
	IMPORTS
		std
		eagine.core.types
		eagine.core.memory
		eagine.core.container
		eagine.core.valid_if
)
target_link_libraries(
	eagine.eglplus
	PUBLIC
	EGL
)

eagine_add_module_tests(
	eagine.eglplus
	UNITS
		constants
	IMPORTS
		eagine.core
)
