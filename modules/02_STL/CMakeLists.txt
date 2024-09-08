# CMakeLists for Module2
set(SOURCES
        01_custom_and_extended_containers/83_basic_allocator.cpp
        01_custom_and_extended_containers/84_pool_allocator.cpp
        01_custom_and_extended_containers/85_subclassing_vector.cpp
        01_custom_and_extended_containers/86_custom_type_traits.cpp
        01_custom_and_extended_containers/87_custom_iterators.cpp
        01_custom_and_extended_containers/88_policy_based_design.cpp
        01_custom_and_extended_containers/89_combining_interfaces.cpp
        01_custom_and_extended_containers/90_custom_containers.cpp
        01_custom_and_extended_containers/91_custom_hash_table.cpp
        "02_Iterator Mastery/92_iterator_basics.cpp"
        "02_Iterator Mastery/93_iterator_traits.cpp"
        "02_Iterator Mastery/94_custom_iterator.cpp"
        "02_Iterator Mastery/95_bidirectional_linked_list_iterator.cpp"
        "02_Iterator Mastery/96_custom_reverse_iterator.cpp"
        "02_Iterator Mastery/97_insert_iterator.cpp"
        "02_Iterator Mastery/98_std_inserter.cpp"
        "02_Iterator Mastery/99_stream_iterator.cpp"
        "02_Iterator Mastery/100_custom_iterator_adapter.cpp"
        "02_Iterator Mastery/101_file_io_with_iterator.cpp"
        "02_Iterator Mastery/102_filtering_stream_copy_if.cpp"
        "02_Iterator Mastery/103_transforming_stream.cpp"
        "02_Iterator Mastery/104_custom_transforming_iterator.cpp"
        "02_Iterator Mastery/105_stream_manipulation.cpp"
        "02_Iterator Mastery/106_custom_stream_manipulator.cpp"


)

foreach(SOURCE IN LISTS SOURCES)
    get_filename_component(SOURCE_NAME ${SOURCE} NAME_WE)
    create_executable_from_source(${SOURCE_NAME} ${SOURCE})
endforeach()
