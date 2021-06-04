build:
    pio run

upload:
    @read -p "Enter closet name: " closet_name

    PLATFORMIO_BUILD_FLAGS='-D P2O_BUILD -D P2O_CLOSET_NAME="\"$closet_name\""' pio run -t upload
    pio device monitor

clean:
    pio run -t clean

decode_stack:
    java -jar EspStackTraceDecoder.jar "C:\Users\eokovacs\AppData\Local\Arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\bin\xtensa-lx106-elf-addr2line.exe" .pio\build\esp01_1m\firmware.elf ./dump.txt
