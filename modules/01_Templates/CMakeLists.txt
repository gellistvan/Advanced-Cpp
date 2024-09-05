# CMakeLists for Module1
set(SOURCES
        01_Template_metaprogramming_basics/01_factorial.cpp
        01_Template_metaprogramming_basics/02_fibonacci.cpp
        01_Template_metaprogramming_basics/03_power_of_N.cpp
        01_Template_metaprogramming_basics/04_power_of_N_optimized.cpp
        01_Template_metaprogramming_basics/05_compile_time_prime_check.cpp

        02_SPFINAE/06_basic_SPFINAE.cpp
        02_SPFINAE/07_SPFINAE_function_overloading.cpp
        02_SPFINAE/08_SPFINAE_member_functions.cpp
        02_SPFINAE/09_SPFINAE_with_concepts.cpp

        03_Variadic_templates/10_basic_variadic_template.cpp
        03_Variadic_templates/11_variadic_class_template.cpp
        03_Variadic_templates/12_variadic_template_fold_expression.cpp
        03_Variadic_templates/13_forwarding_template.cpp
        03_Variadic_templates/14_variadic_compile_type_computations.cpp

        04_template_specialization/15_template_specialization.cpp
        04_template_specialization/16_partial_speciaalization.cpp
        04_template_specialization/17_custom_allocator.cpp
        04_template_specialization/18_specialization_with_SPFINAE.cpp
        05_compile_time_data_structure/19_compile_time_linked_list.cpp
        05_compile_time_data_structure/20_compile_time_binary_tree.cpp
        05_compile_time_data_structure/21_compile_time_map.cpp
        05_compile_time_data_structure/22_compile_time_vector.cpp
        06_compile_type_algorithms/23_compile_time_string_manipulation.cpp
        06_compile_type_algorithms/24_compile_time_sorting.cpp
        06_compile_type_algorithms/25_compile_time_matrix_multiplication.cpp
        07_metafunctions_type_traits/27_basic_metafunctions.cpp
        07_metafunctions_type_traits/28_chaining_metafunction_classes.cpp
        07_metafunctions_type_traits/29_enable_if.cpp
        07_metafunctions_type_traits/30_conditional_type_selection.cpp
        07_metafunctions_type_traits/31_standard_type_traits.cpp
        07_metafunctions_type_traits/32_is_smart_ptr.cpp
        07_metafunctions_type_traits/33_combining_traits.cpp
        07_metafunctions_type_traits/34_type_traits_with_SPFINAE.cpp


)

foreach(SOURCE IN LISTS SOURCES)
    get_filename_component(SOURCE_NAME ${SOURCE} NAME_WE)
    create_executable_from_source(${SOURCE_NAME} ${SOURCE})
endforeach()
