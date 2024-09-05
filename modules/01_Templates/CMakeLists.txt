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
        08_TMP_with_cpp11_and_more/35_constexpr_factorial.cpp
        08_TMP_with_cpp11_and_more/36_decltype_auto.cpp
        08_TMP_with_cpp11_and_more/37_basic_consepts.cpp
        08_TMP_with_cpp11_and_more/38_constexpr_fibonacci.cpp
        08_TMP_with_cpp11_and_more/39_consteval_basics.cpp
        08_TMP_with_cpp11_and_more/40_constexpr_compile_time_vector.cpp
        08_TMP_with_cpp11_and_more/41_compile_time_validation.cpp
        09_consepts_and_rangees/42_basic_consepts.cpp
        09_consepts_and_rangees/43_combining_consepts.cpp
        09_consepts_and_rangees/44_basics_of_ranges.cpp
        09_consepts_and_rangees/45_range_adaptors.cpp
        09_consepts_and_rangees/46_range_algorithms.cpp
        09_consepts_and_rangees/47_consepts_with_ranges.cpp
        09_consepts_and_rangees/48_filtering_and_transforming_data.cpp
        10_TMP_with_Cpp23/49_constexpr_with_dynamic_memory.cpp
        10_TMP_with_Cpp23/50_enhanced_type_traits.cpp
        10_TMP_with_Cpp23/51_enhanced_template_syntax.cpp
        10_TMP_with_Cpp23/52_constexpr_matrix_multiplication.cpp
        10_TMP_with_Cpp23/53_advanced_type_manip_with_consepts.cpp
        11_CRTP/60_basic_CRTP.cpp
        11_CRTP/61_static_polymorphism_with_CRTP.cpp
        11_CRTP/62_mixins_with_CRTP.cpp
        11_CRTP/63_enforcing_interfaces_with_CRTP.cpp
        11_CRTP/64_compile_time_computations_with_CRTP.cpp
        11_CRTP/65_logging_mixin_with_CRTP.cpp
        12_static_polymorphism/66_basic_policy_based_design.cpp
        12_static_polymorphism/67_optimizing_compile_time_computations.cpp
        12_static_polymorphism/68_comparing_static_and_dynamic_polymorphism.cpp
        12_static_polymorphism/69_static_polymorphism_with_multiple_inheritance.cpp
        12_static_polymorphism/70_polymorphic_container.cpp
        13_type_erasure_basics/71_std_function.cpp
        13_type_erasure_basics/72_custom_type_erasure.cpp
        14_type_erasure_std_any_and_variant/73_heterogeneous_collections.cpp
        14_type_erasure_std_any_and_variant/74_std_any_check_stored_type.cpp
        14_type_erasure_std_any_and_variant/75_std_variant.cpp
        14_type_erasure_std_any_and_variant/76_visiting_variant.cpp
        14_type_erasure_std_any_and_variant/77_practical_std_any.cpp
        14_type_erasure_std_any_and_variant/78_event_system_with_variant.cpp
        15_type_erasure_with_std_function/79_event_handling_system.cpp
        15_type_erasure_with_std_function/80_generic_algorithm.cpp
        15_type_erasure_with_std_function/81_std_function_with_member_functions.cpp
        15_type_erasure_with_std_function/82_chaining_callables.cpp




)

foreach(SOURCE IN LISTS SOURCES)
    get_filename_component(SOURCE_NAME ${SOURCE} NAME_WE)
    create_executable_from_source(${SOURCE_NAME} ${SOURCE})
endforeach()
