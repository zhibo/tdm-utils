#! /bin/bash

# time genkernel --menuconfig --no-clean --kerneldir=/usr/src/linux-tcel all
time genkernel --kernel-config=/usr/src/linux-tcel/.config --no-clean --kerneldir=/usr/src/linux-tcel all
# genkernel --kernel-config=/usr/src/linux-tcel --install initramfs
