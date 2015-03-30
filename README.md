/dev/clipboard
==============

`/dev/clipboard` is a device that works like a clipboard.

You can copy and paste data between tty by redirecting output and inputs. Right now it does use a shared clipboard between users and MUST not be used as a way to store secure data.

When the module is unloaded the data is lost.

Building
========

For Debian:

	# apt-get install module assistant

To build the module just `make` it:

	$ make

Setup
=====

As `root` copy `clipboard.rules` to the `/etc/udev/rules.d/` folder and enable the module:

	# cp ./clipboard.rules /etc/udev/rules.d/10-clipboard.rules
	# insmod clipboard.ko

To disable the module:

	# rmmod clipboard

Usage
=====

To copy data into the clipboard just write it by redirecting to `/dev/clipboard`, to paste from the clipboard you just need to read from it.

Here is an example of the usage of the `clipboard` device:

	$ echo 'Hello World !' > /dev/clipboard
	$ cat /dev/clipboard
	Hello World !

Right now it's not a secure device since all the users can use the clipboard.
