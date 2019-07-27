# PacificConnect
Usage:
./PacificConnect <endpoint>

eg:
./PacificConnect /dev/ttyS0

For testing with a serial simulator:
socat -d -d pty,raw,echo=0 pty,raw,echo=0

Use the resulting endpoint for reading and writing.

Assumption:
Total size of one block is assumed as less than 256 bytes.

ToDo:
Handle any size input.

