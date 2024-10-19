cmake_minimum_required (VERSION 3.22)

project (AdditiveLab VERSION 0.0.1 LANGUAGES C CXX)

set (CMAKE_CXX_STANDARD 17)

add_subdirectory (3dPartyLibs)

juce_add_gui_app (AdditiveLab PRODUCT_NAME ${PROJECT_NAME})

juce_generate_juce_header (AdditiveLab)

function (add_sources arg_list)
    set (arg_list ${ARGV})
    list (GET arg_list 0 dir)
    list (REMOVE_AT arg_list 0)
    foreach (item IN LISTS arg_list)
        set_property (GLOBAL APPEND PROPERTY SOURCE_ACCUMULATION_PROPERTY "${dir}/${item}")
    endforeach ()
endfunction ()

add_subdirectory (Source)

get_property (SOURCES GLOBAL PROPERTY SOURCE_ACCUMULATION_PROPERTY)

target_sources (AdditiveLab PRIVATE ${SOURCES})

target_compile_definitions (AdditiveLab
    PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:${PROJECT_NAME},JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:${PROJECT_NAME},JUCE_VERSION>")

target_link_libraries(AdditiveLab
    PRIVATE
        juce::juce_audio_utils
        juce::juce_dsp
        juce::juce_gui_extra
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags )
