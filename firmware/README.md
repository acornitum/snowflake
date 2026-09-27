# Snowflake Firmware

Welcome! Here's a basic way to upload custom code onto the macropad so that you could make it type whatever you want. 

For this, I'm using [https://github.com/DeqingSun/ch55xduino](https://github.com/DeqingSun/ch55xduino)! Follow the instructions on that GitHub Repo to start. There are other ways to do it, but this is probably the fastest for getting started.

Once you have that set up, the code is in firmware.ino. Edit it to put what you want on!

In order to flash things on, you need to put the board into bootloader mode. To do that:

1. Hold down the boot button
2. Plug it into the USB-C cable connected to your laptop
3. Press upload in the IDE!

It may take a few tries; I've found that after a few seconds, if you don't flash the new code on fast enough, the board leaves bootloader mode. 

Good luck + have fun!
