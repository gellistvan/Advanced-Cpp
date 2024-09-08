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

        02_Iterator_mastery/92_iterator_basics.cpp
        02_Iterator_mastery/93_iterator_traits.cpp
        02_Iterator_mastery/94_custom_iterator.cpp
        02_Iterator_mastery/95_bidirectional_linked_list_iterator.cpp
        02_Iterator_mastery/96_custom_reverse_iterator.cpp
        02_Iterator_mastery/97_insert_iterator.cpp
        02_Iterator_mastery/98_std_inserter.cpp
        02_Iterator_mastery/99_stream_iterator.cpp
        02_Iterator_mastery/100_custom_iterator_adapter.cpp
        02_Iterator_mastery/101_file_io_with_iterator.cpp
        02_Iterator_mastery/102_filtering_stream_copy_if.cpp
        02_Iterator_mastery/103_transforming_stream.cpp
        02_Iterator_mastery/104_custom_transforming_iterator.cpp
        02_Iterator_mastery/105_stream_manipulation.cpp
        02_Iterator_mastery/106_custom_stream_manipulator.cpp

        03_algorithmic_techniques/01_basic_algorithms/107_in_place_sort.cpp
        03_algorithmic_techniques/01_basic_algorithms/108_in_place_reverse.cpp
        03_algorithmic_techniques/01_basic_algorithms/109_std_copy.cpp
        03_algorithmic_techniques/01_basic_algorithms/110_std_transform.cpp
        03_algorithmic_techniques/01_basic_algorithms/111_in_and_out_of_place_combined.cpp
        03_algorithmic_techniques/01_basic_algorithms/112_std_for_each.cpp
        03_algorithmic_techniques/01_basic_algorithms/113_std_find.cpp
        03_algorithmic_techniques/01_basic_algorithms/114_std_count.cpp
        03_algorithmic_techniques/01_basic_algorithms/115_std_replace.cpp
        03_algorithmic_techniques/01_basic_algorithms/116_std_fill.cpp
        03_algorithmic_techniques/01_basic_algorithms/117_std_remove_if.cpp
        03_algorithmic_techniques/01_basic_algorithms/118_find_and_replace.cpp
        03_algorithmic_techniques/01_basic_algorithms/119_count_and_remove.cpp

        03_algorithmic_techniques/02_sorted_range_algorithms/120_std_binary_search.cpp
        03_algorithmic_techniques/02_sorted_range_algorithms/121_std_lower_and_upper_bound.cpp
        03_algorithmic_techniques/02_sorted_range_algorithms/122_std_equal_range.cpp
        03_algorithmic_techniques/02_sorted_range_algorithms/123_std_merge.cpp
        03_algorithmic_techniques/02_sorted_range_algorithms/124_std_includes.cpp
        03_algorithmic_techniques/02_sorted_range_algorithms/125_std_set_union.cpp
        03_algorithmic_techniques/02_sorted_range_algorithms/126_std_set_intersection.cpp
        03_algorithmic_techniques/02_sorted_range_algorithms/127_std_set_difference.cpp
        03_algorithmic_techniques/02_sorted_range_algorithms/128_std_symmetric_difference.cpp

        03_algorithmic_techniques/03_partitioning_and_permutation/129_std_partition.cpp
        03_algorithmic_techniques/03_partitioning_and_permutation/130_std_stable_partition.cpp
        03_algorithmic_techniques/03_partitioning_and_permutation/131_std_partition_point.cpp
        03_algorithmic_techniques/03_partitioning_and_permutation/132_std_next_and_prev_permutation.cpp
        03_algorithmic_techniques/03_partitioning_and_permutation/133_std_rotate.cpp
        03_algorithmic_techniques/03_partitioning_and_permutation/134_partitioning_and_permutation.cpp




)

foreach(SOURCE IN LISTS SOURCES)
    get_filename_component(SOURCE_NAME ${SOURCE} NAME_WE)
    create_executable_from_source(${SOURCE_NAME} ${SOURCE})
endforeach()
