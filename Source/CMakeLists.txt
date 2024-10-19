add_subdirectory (AppBase)
add_subdirectory (Core)
add_subdirectory (Gui)
add_subdirectory (IO)
add_subdirectory (Synth)
add_subdirectory (System)

target_include_directories (${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})