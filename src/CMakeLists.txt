
set(PACC_SOURCES compiler.cpp lexer.cpp parser.cpp)
add_library(libpacc ${PACC_SOURCES})
target_include_directories(libpacc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(paccal paccal.cpp)
target_link_libraries(paccal PRIVATE libpacc)