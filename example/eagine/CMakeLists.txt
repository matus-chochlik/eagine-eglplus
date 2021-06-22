# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt

add_custom_target(eagine-eglplus-examples ALL)
set_target_properties(
	eagine-eglplus-examples
	PROPERTIES FOLDER "Example/EGLplus"
)

function(eagine_install_example TARGET_NAME)
	install(
		TARGETS ${TARGET_NAME}
		DESTINATION share/eagine/example/eglplus
	)
endfunction()

function(eagine_example_common EXAMPLE_NAME)
	add_executable(
		eglplus-${EXAMPLE_NAME}
		EXCLUDE_FROM_ALL
		"${EXAMPLE_NAME}.cpp"
		${ARGN}
	)
	eagine_add_exe_analysis(eglplus-${EXAMPLE_NAME})
	add_dependencies(eagine-eglplus-examples eglplus-${EXAMPLE_NAME})
	target_link_libraries(
		eglplus-${EXAMPLE_NAME}
		PUBLIC EAGine::EGLplus
		PRIVATE ${ARGN}
	)

	set_target_properties(
		eglplus-${EXAMPLE_NAME}
		PROPERTIES FOLDER "Example/EGLplus"
	)
	eagine_install_example(eglplus-${EXAMPLE_NAME})
endfunction()

add_subdirectory(eglplus)
