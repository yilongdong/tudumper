# shellcheck disable=SC2046
# shellcheck disable=SC2215
cmake -B build/debug -S . -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=$(dirname $(which vcpkg))/scripts/buildsystems/vcpkg.cmake -DCMAKE_INSTALL_PREFIX=$(pwd)/install
cmake --build build/debug --parallel
#cmake --build build/debug
cd build/debug
ninja install
cd -
ctest --test-dir build/debug/tests
echo './install/bin/tudumper --output_dir ./result.json --compdb /Users/dongyilong/projects/Clion/TUDumper/build/debug/compile_commands.json --files all --verbose'
