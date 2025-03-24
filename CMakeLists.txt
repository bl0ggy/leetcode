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
    684
    796
    802
    827
    873
    889
    951
    1026
    1028
    1079
    1092
    1233
    1261
    1267
    1277
    1352
    1358
    1368
    1415
    1462
    1524
    1560
    1671
    1718
    1726
    1749
    1752
    1763
    1765
    1780
    1790
    1800
    1829
    1910
    1957
    1976
    1980
    2017
    2070
    2115
    2127
    2161
    2206
    2226
    2275
    2342
    2349
    2364
    2375
    2379
    2401
    2458
    2460
    2463
    2467
    2490
    2493
    2501
    2523
    2529
    2560
    2563
    2570
    2579
    2583
    2594
    2601
    2641
    2658
    2661
    2683
    2684
    2685
    2698
    2914
    2948
    2965
    2996
    3011
    3036
    3066
    3097
    3105
    3108
    3133
    3151
    3160
    3163
    3169
    3174
    3191
    3208
    3264
    3266
    3276
    3303
    3306
    3330
    3333
    3356
)
foreach(x IN LISTS tests)
    add_executable(${x}
        src/${x}.cpp
    )
    set_target_properties(${x} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
    )
endforeach()
