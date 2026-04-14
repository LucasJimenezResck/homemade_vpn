# homemade_vpn
Original idea of this project was to create a vpn using a raspberry Pi as server. But after finding out about kernel drivers in Linux this is the new direction of the repo for now.
I am using a Rasperry Pi 4B with a server version of Ubuntu 24.04. It connects with my laptop through ssh via Wi-Fi, where I can control the Raspberry Pi's terminal.
## Set-up
My laptop uses Ubuntu 25.04.
I have a Kingston SSD which connects through a SATA-USB adapter to the board. It gets formatted using the Raspberry Pi Imager program, which can be installed with the command `sudo apt install rpi-imager`.
- After connecting the SSD to my laptop, I opened the imager to set up the environment for the board. There I specified my Wi-Fi network to connect to when booting and my username.
- The SSD was connected to the Raspi and a power supply through USB-C was provided.
- In my router App, I found the Board's IP-Address and set up the connection from my laptop by calling `ssh <username>@<IP-Address>`.
- Here is a list of the starting commands I used to set up my Board
```
sudo apt update && sudo apt upgrade -y
sudo apt install build-essential
sudo apt-get install linux-headers-$(uname -r)
```
- I also created an SSH-Key to clone this repo into a folder inside the board.
## Sources
The reference for this project is the Linux Driver YouTube playlist: https://www.youtube.com/playlist?list=PLCGpd0Do5-I3b5TtyqeF1UdyD4C-S-dMa
## Problems when compiling/loading
Since I tried inserting these modules using various programs, there are a few common problems that I had when trying to process that code, even though no syntax or logical errors were involved. Here is a comprehensive list.
### Compile error: PWD
On the _Makefile_, for some reason when trying to print the working directory it might make a difference whether you use `$(PWD)` or `$(shell pwd)` when typing the "modules" and "clean" commands. The second usually works best.
### Insert error: unavailability of vmlinux
When trying to insert the module into the kernel, much too often every file will be generated, except from the actual Kernel-object. A solution that worked every time for me is in this website of the Ubuntu Kernel forum: https://askubuntu.com/questions/1348250/skipping-btf-generation-xxx-due-to-unavailability-of-vmlinux-on-ubuntu-21-04.
### Insert error: key rejected by service
Similar to the previous error, every file including the kernel-object may generate, but the insertion will be rejected by a message like this:
```
insmod: ERROR: could not insert module hello.ko: Key was rejected by service
```
This is probably because the BIOS of the system was set up using secure boot, and it needs to be disabled in order to load modules into the kernel. You can check the state of your boot with `mokutil --sb-state`.
Source: https://askubuntu.com/questions/1455528/modprobe-key-was-rejected-by-service-ubuntu-22-04-1-desktop-iso.