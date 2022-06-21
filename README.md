Qt Serial Port Protocol over Bluez 5 example
============================================

Small example application on how to open a socket to speak the RS232 protocl to
a remote device over bluetooth (as is used by the OBD ELM327 car diagnostic
reader for example).

This combines a few separate things to end up with a client, that just writes
the same string over and over to the socket:

- It uses [BluezQt](https://api.kde.org/frameworks/bluez-qt/html/index.html) to
		register the bluetooth profile.
- The profile is SPP1.2 as seen here:
		https://www.bluetooth.com/specifications/specs/synchronization-profile-1-2-1/

The profile is set to autoconnect, so as soon as you connect to a supported
device, this application will start writing to it. This is done in the
`newConnection` function, which gets passed a file descriptor, that can be
converted to a LocalSocket. The LocalSocket can then be used for reading and
writing. The profile needs to be registered with the right UUID and port.

This is loosely based on https://github.com/tonyespy/bluez5-spp-example
