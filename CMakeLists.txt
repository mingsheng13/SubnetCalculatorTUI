cmake_minimum_required(VERSION 3.25)
project(SubnetCalculatorUI)

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

# fetch ip component
FetchContent_Declare(ftxui-ip-input
        GIT_REPOSITORY https://github.com/mingsheng13/ip-input-ftxui
        GIT_TAG main
)
FetchContent_MakeAvailable(ftxui-ip-input)
#

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp
        IPV4.cpp
        IPV4.hpp)

target_link_libraries(${PROJECT_NAME}
        PRIVATE ftxui::screen
        PRIVATE ftxui::dom
        PRIVATE ftxui::component
        PRIVATE ftxui-ip-input
)

target_include_directories(${PROJECT_NAME} PRIVATE src)