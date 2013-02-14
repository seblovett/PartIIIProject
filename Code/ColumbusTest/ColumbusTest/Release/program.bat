batchisp -device at32uc3c0512c -hardware usb -operation erase f memory flash blankcheck loadbuffer ColumbusTest.elf program verify start reset 0
pause