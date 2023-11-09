cmake_minimum_required(VERSION 3.19)

# --- Fetch FTXUI --------------------------------------------------------------
include(FetchContent)
 
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v5.0.0
)
 
FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
 
# ------------------------------------------------------------------------------

project(fall2023-csc3380-project)

set(CMAKE_CXX_STANDARD 20)

enable_testing()
include(CTest)

add_executable(project code/main.cpp)
add_executable(runtests code/runtests.cpp)

target_include_directories(project PRIVATE code)

target_link_libraries(project
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)

target_compile_definitions(runtests PRIVATE CATCH_CONFIG_MAIN)
add_test(NAME runtests COMMAND runtests WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})