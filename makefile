all:stft.pgm

stft.pgm: build/stft_test test.txt
	build/stft_test < test.txt >stft.pgm
build/stft_test: $(wildcard *.cpp) $(wildcard *.hpp)
	mkdir -p build
	cmake -S . -B build -G Ninja
	ninja -C build

