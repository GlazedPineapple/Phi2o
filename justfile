build:
    pio run

upload:
    @read -p "Enter closet name: " closet_name

    PLATFORMIO_BUILD_FLAGS='-D P2O_BUILD -D P2O_CLOSET_NAME="\"$closet_name\""' pio run -t upload
    pio device monitor

clean:
    pio run -t clean