#Busybox-linux

##Hello, today I make some experiment about Linux with Busybox and Musl-libc. I only upload the rootfs with Busybox and Musl-libc on it.
Here's what i've do with this experiment:

###Busybox:
- Use static build.
- Remove tc on networking.

###Musl-libx:
- I use configuration "./configure --prefix=/usr --syslibdir=/lib --enable-static --disable-shared" before compile it with Make.

###Linux-kernel:
- I use LTS kernel version, I use on version 6.12.85 .
- Every kernel config based on my machine (HP Notebook 14 AC150TU) and ext4 for filesystem.
