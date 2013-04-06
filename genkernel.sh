#! /bin/bash

# time genkernel --menuconfig --no-clean --kerneldir=/usr/src/linux-tcel all
# all
time genkernel --kernel-config=/usr/src/linux-tcel/.config --no-clean --kerneldir=/usr/src/linux-tcel all
# only kernel
# time genkernel --kernel-config=/usr/src/linux-tcel/.config --no-clean --kerneldir=/usr/src/linux-tcel bzImage
# kernel and modules
# time genkernel --kernel-config=/usr/src/linux-tcel/.config --no-clean --kerneldir=/usr/src/linux-tcel kernel
# install initramfs
# genkernel --kernel-config=/usr/src/linux-tcel --install initramfs
