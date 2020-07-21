project(bindUsePybind11)
set(LIB_NAME python_example)

add_library(${LIB_NAME} SHARED
        src/example.cpp
)
set_target_properties(${LIB_NAME} PROPERTIES PREFIX "")

target_include_directories(${LIB_NAME}
    PRIVATE
        ${PYBIND11_INCLUDE_DIR}
        ${PYTHON_INCLUDE_DIRS}
)

target_link_libraries(${LIB_NAME}
    PRIVATE
        ${PYTHON_LIBRARIES}
)

set_target_properties(${LIB_NAME} PROPERTIES PREFIX "")
if(WIN32)
    if (MSVC)
        set_target_properties(${LIB_NAME} PROPERTIES COMPILE_FLAGS "/MP /bigobj ")

        if (NOT ${U_CMAKE_BUILD_TYPE} MATCHES DEBUG)
            set_target_properties(${LIB_NAME} APPEND_STRING PROPERTY COMPILE_FLAGS "/Os /GL ")
            set_target_properties(${LIB_NAME} APPEND_STRING PROPERTY LINK_FLAGS "/LTCG ")
        endif()
    endif()

    # .PYD file extension on Windows
    set_target_properties(${LIB_NAME} PROPERTIES SUFFIX ".pyd")

elseif(UNIX)

    # .SO file extension on Linux/Mac OS
    set_target_properties(${LIB_NAME} PROPERTIES SUFFIX ".so")

    # Strip unnecessary sections of the binary on Linux/Mac OS
    if(APPLE)
        set_target_properties(${LIB_NAME} PROPERTIES MACOSX_RPATH ".")
        set_target_properties(${LIB_NAME} PROPERTIES LINK_FLAGS "-undefined dynamic_lookup ")
        if (NOT ${U_CMAKE_BUILD_TYPE} MATCHES DEBUG)
            add_custom_command(TARGET ${LIB_NAME} POST_BUILD COMMAND strip -u -r ${PROJECT_BINARY_DIR}/${LIB_NAME}.so)
        endif()
    else()
        if(NOT ${U_CMAKE_BUILD_TYPE} MATCHES DEBUG)
            add_custom_command(TARGET ${LIB_NAME} POST_BUILD COMMAND strip ${PROJECT_BINARY_DIR}/${LIB_NAME}.so)
        endif()
    endif()
endif()