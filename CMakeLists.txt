cmake_minimum_required(VERSION 3.30...3.30.1)
cmake_policy(VERSION 3.30...3.30.1)

# EDIT: Not required anymore, but need some ENV configuration
# See https://github.com/bl0ggy/dotfiles/blob/3e94728a6ccbf033d4f7b6baa1c68c4fac5cf6db/zsh/.zshrc#L38-L56
# -----
# Very tricky one, MacOS has /usr/opt/clang++ which is made by Apple, named "AppleClang"
# This MacOS version is not compatible with the clangd provided by Mason's clangd LSP
# So we must change the compiler path to a most recent one
# set(CMAKE_CXX_COMPILER /opt/homebrew/Cellar/llvm/18.1.8/bin/clang++)
# set(CMAKE_C_COMPILER /opt/homebrew/Cellar/llvm/18.1.8/bin/clang)

project(leetcode VERSION 0.1)

set(CXX clang)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wunused-variable" )

set(BUILD_SHARED_LIBS ON) # Required for glm to build as shared library

set(DEBUG_RPATH "")
if(DEBUG)
    add_definitions(
        -DDEBUG
        # -DVULKAN_HPP_NO_EXCEPTIONS
    )
endif()

include_directories(AFTER .)

set(tests
    1
    2
    3
    4
    44
    84
    89
    407
    682
    796
    802
    951
    1026
    1233
    1267
    1277
    1368
    1462
    1560
    1671
    1763
    1765
    1829
    1957
    2017
    2070
    2127
    2275
    2458
    2463
    2490
    2501
    2563
    2583
    2601
    2641
    2658
    2661
    2683
    2684
    2914
    2948
    2996
    3011
    3036
    3097
    3133
    3163
    3264
    3266
    3276
    3303
    3330
    3333
)
foreach(x IN LISTS tests)
    add_executable(${x}
        src/${x}.cpp
    )
    set_target_properties(${x} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
    )
endforeach()
