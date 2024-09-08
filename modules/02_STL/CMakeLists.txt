# CMakeLists for Module2

file(GLOB SOURCES
        01_custom_and_extended_containers/*.cpp
        02_Iterator_mastery/*.cpp
        03_algorithmic_techniques/*/*.cpp
        04_advanced_container_usage/*/*.cpp
)

foreach(SOURCE IN LISTS SOURCES)
    get_filename_component(SOURCE_NAME ${SOURCE} NAME_WE)
    create_executable_from_source(${SOURCE_NAME} ${SOURCE})
endforeach()
