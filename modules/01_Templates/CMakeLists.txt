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
)

foreach(SOURCE IN LISTS SOURCES)
    get_filename_component(SOURCE_NAME ${SOURCE} NAME_WE)
    create_executable_from_source(${SOURCE_NAME} ${SOURCE})
endforeach()
