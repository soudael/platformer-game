all:
	cmake --build build
run:
	./build/game.exe
set:
	cmake -S . -B build \
		-DSDL3_DIR="dependencies/lib/cmake/SDL3" \
		-DSDL3_image_DIR="dependencies/lib/cmake/SDL3_image"
zip:
	cmake --build build --config Release
	cd build && cpack -C Release