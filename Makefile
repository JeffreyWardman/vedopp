depends:
	vcpkg integrate install
	vcpkg install

build_debug:
	cmake -S . -B build \
		-D CMAKE_BUILD_TYPE=Debug \
		-D BUILD_MCSS_DOCS=ON \
		-D BUILD_TESTING=ON \
		-D ENABLE_COVERAGE=ON \
		-D VEDO_DEVELOPER_MODE=ON
	cmake --build build

install_debug:
	cmake --install build

build_and_install_debug:
	make build_debug
	make install_debug

build_release:
	cmake -S . -B release -D CMAKE_BUILD_TYPE=Release
	cmake --build release

install_release:
	cmake --install release

run_example:
	./build/example/example/empty_example

run_test:
	./build/test/test/vedo_test

run_docs:
	doxygen build/docs/Doxyfile
	python3 -m http.server 8000 --directory build/docs/html
