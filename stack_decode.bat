@echo off

java -jar EspStackTraceDecoder.jar "C:\Users\eokovacs\AppData\Local\Arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\bin\xtensa-lx106-elf-addr2line.exe" .pio\build\esp01_1m\firmware.elf ./dump.txt