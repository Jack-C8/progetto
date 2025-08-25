cmake_minimum_required(VERSION 3.28)
project(progettopf VERSION 0.1.0)

# abilita il supporto per i test
include(CTest)

# esporta il compilation database (utile per clangd, clang-tidy, ecc.)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# richiedi C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# warning utili
# meglio su target specifici invece che globali
set(PROGETTO_WARNINGS
    -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion
    -Wshadow -Wimplicit-fallthrough -Wextra-semi -Wold-style-cast
    -fno-omit-frame-pointer
)

# asserzioni della standard library
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  list(APPEND PROGETTO_WARNINGS -D_GLIBCXX_ASSERTIONS)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  list(APPEND PROGETTO_WARNINGS -D_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE)
endif()

# sanitizers in Debug
set(PROGETTO_SANITIZERS "")
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  list(APPEND PROGETTO_SANITIZERS -fsanitize=address,undefined)
  if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    list(APPEND PROGETTO_WARNINGS -D_GLIBCXX_SANITIZE_STD_ALLOCATOR)
  endif()
endif()

# trova SFML
find_package(SFML 2.6 COMPONENTS graphics REQUIRED)

# eseguibile principale
add_executable(progetto
    main.cpp
    card.cpp
    basegraphics.cpp
    CardRenderer.cpp
    hand.cpp
    methods.cpp
    static_table.cpp
)

# includi la cartella corrente (header e cpp stanno qui)
target_include_directories(progetto PRIVATE ${CMAKE_SOURCE_DIR})

# aggiungi flag di compilazione e sanitizers
target_compile_options(progetto PRIVATE ${PROGETTO_WARNINGS} ${PROGETTO_SANITIZERS})
target_link_options(progetto PRIVATE ${PROGETTO_SANITIZERS})

# linka SFML
target_link_libraries(progetto PRIVATE sfml-graphics)

# test (opzionale)
if (BUILD_TESTING)
  add_executable(progetto.t card.test.cpp card.cpp hand.cpp  basegraphics.cpp static_table.cpp methods.cpp CardRenderer.cpp)
  target_include_directories(progetto.t PRIVATE ${CMAKE_SOURCE_DIR})
  target_compile_options(progetto.t PRIVATE ${PROGETTO_WARNINGS} ${PROGETTO_SANITIZERS})
  target_link_options(progetto.t PRIVATE ${PROGETTO_SANITIZERS})
  target_link_libraries(progetto.t PRIVATE sfml-graphics)
  add_test(NAME progetto.t COMMAND progetto.t)
endif()