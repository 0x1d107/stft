#!/bin/bash
ninja -C build
build/stft_data < test.txt > test.data
build/stft_pgm  < test.txt > stft.pgm
