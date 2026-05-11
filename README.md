## Busybox-linux

Hello, today I make some experiment about Linux with Busybox and Musl-libc. I only upload the rootfs with Busybox and Musl-libc on it.
Here's what i've do with this experiment:

#### Busybox:
- Use static build.
- Remove tc, dhcpc and dhcpcd on networking.

#### Musl-libc:
I use configuration "./configure --prefix=/usr --syslibdir=/lib --enable-static --disable-shared" before compile it with Make.

#### Linux-kernel:
I use LTS kernel version, I use on version 6.12.85 .
Every kernel config based on my machine (HP Notebook 14 AC150TU) and ext4 for filesystem.

#### Init:
This is simple configuration for init I make:

```sh
#!/bin/sh
echo "init start"

echo "mounting"
mount -t proc proc /proc
mount -t sysfs sys /sys
mount -t devtmpfs devtmpfs /dev

echo "Finally, i guess"

exec setsid cttyhack /bin/sh
```
#### Note:
The init configuration I've been make it executable, if not executable use "chmod +x rootfs/init"


Oh, I forgot my line. Have a nice day, nyan
