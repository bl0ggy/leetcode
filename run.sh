#!/bin/bash

reset

# Specify the directory containing the build.ninja file
build_dir="build"
# Specify the directory containing the binaries
tests_binary_dir="$build_dir/tests"

# Flag to determine if compilation is needed
compile_flag=false
# Flag to determine if we must not run the tests
dry_run=false

# Function to run an executable
run() {
    local executable_name="$1"
    local executable_path="$tests_binary_dir/$executable_name"

    if [ -x "$executable_path" ] && [ -f "$executable_path" ]; then
        echo "Executing: $executable_path"
        "$executable_path"
        result=$?
        echo "------------------------"
        if [ $result -ne 0 ]; then
            exit 1
        fi
    else
        echo "Error: '$executable_name' is not an executable file in $tests_binary_dir"
        exit 1
    fi
}

# Parse command line arguments
executables=()
while [[ $# -gt 0 ]]; do
    case $1 in
    -h | --help)
        echo "Usage: $0 [-c] <executable_name1> [executable_name2] ..."
        echo "  -c, --compile    Compile executables before running"
        exit 1
        ;;
    -c | --compile)
        compile_flag=true
        shift
        ;;
    -d | --dry-run)
        dry_run=true
        shift
        ;;
    *)
        executables+=("$1")
        shift
        ;;
    esac
done

if ! [ -d "$tests_binary_dir" ]; then
    mkdir -p "$tests_binary_dir"
fi
if ! [ -f "$build_dir/CMakeCache.txt" ]; then
    # echo "pushd $build_dir"
    pushd "$build_dir"
    cmake .. -GNinja
    popd
fi

# Compile executables first
if $compile_flag; then
    ninja -C "$build_dir" ${executables[*]}
    if [ $? -ne 0 ]; then
        exit 1
    fi
fi

if [ "$dry_run" = true ]; then
    exit 0
fi

# If not executables proved, take all executable names from the build dir
if [ ${#executables[@]} -eq 0 ]; then
    pushd "$tests_binary_dir" >/dev/null
    pwd
    for file in *; do
        # Check if the file is executable
        if [ -x "$file" ] && [ -f "$file" ]; then
            executables+=("$file")
        fi
    done
    popd >/dev/null
fi

if [ ${#executables[@]} -eq 0 ]; then
    echo "No tests to run"
    exit 1
fi

# Then run the executables
for executable_name in "${executables[@]}"; do
    run "$executable_name"
done
