add_library(utils STATIC buitin_commands.cpp command_parser.cpp command_executor.cpp
 buitin_commands.cpp path_utils.cpp shell.cpp)

target_include_directories(utils PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(shell main.cpp)
target_link_libraries(shell PRIVATE utils)