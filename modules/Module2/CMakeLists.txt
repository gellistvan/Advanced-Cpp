# CMakeLists for Module2
set(SOURCES
        hello_world_3.cpp
        hello_world_4.cpp
)

foreach(SOURCE IN LISTS SOURCES)
    get_filename_component(SOURCE_NAME ${SOURCE} NAME_WE)
    create_executable_from_source(${SOURCE_NAME} ${SOURCE})
endforeach()
