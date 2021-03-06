# pico-utils
Utilities for analyzing / debugging Raspberry Pi Pico projects

__uf2usage:__ Reads a given .uf2 file and spits out the amount of memory that will be used on the target hardware. Requires the [libzed](https://github.com/ZacharyWesterman/libzed) library.

__picoterm:__ Attempt to connect to a Pico that is connected via a USB cable. Requires `minicom` to be installed if using in interactive mode (run with `-i` or `--interactive` flag).

__uf2topico:__ Copy a uf2 file to the Pico. Assumes the Pico is mounted under `/run/media/{your user}/RPI-RP2`
