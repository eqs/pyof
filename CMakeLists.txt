cmake_minimum_required(VERSION 3.15)
project(cpyoflib)

include_external_msproject(pyoflib ${CMAKE_SOURCE_DIR}/pyoflib/pyoflib.vcxproj)
include_external_msproject(oflib ${CMAKE_SOURCE_DIR}/of_v0.11.0_vs2017_release/libs/openFrameworksCompiled/project/vs/openframeworksLib.vcxproj)
add_dependencies(pyoflib oflib)
add_custom_target(cpyoflib pyoflib)

add_custom_command(
    TARGET cpyoflib
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/pyoflib/bin/pyoflib.pyd
        ${CMAKE_SOURCE_DIR}/pyof/lib/pyoflib.pyd
)

# configure_file(
#     ${CMAKE_SOURCE_DIR}/pyoflib/bin/pyoflib.pyd
#     ${CMAKE_SOURCE_DIR}/pyof/lib/pyoflib.pyd
#     COPYONLY
# )
