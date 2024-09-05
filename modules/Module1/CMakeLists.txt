# CMakeLists for Module1
set(SOURCES
    hello_world_1.cpp
    hello_world_2.cpp
)

foreach(SOURCE IN LISTS SOURCES)
    get_filename_component(SOURCE_NAME ${SOURCE} NAME_WE)
    create_executable_from_source(${SOURCE_NAME} ${SOURCE})
endforeach()
