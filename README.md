# PacificConnect
This is a sample application to read from serial interface and print to standard output.

Functions:
1. Read from serial (specified as an argument) port.
2. Parse and construct JSON data from data block read. Add VALID field to the JSON result.
3. Print latest data on every 10 seconds system time boundary, eg 2:00:00pm, 2:00:10pm, 2:00:20pm.

Usage:
./PacificConnect <endpoint>

eg:
./PacificConnect /dev/ttyS0

Sample serial output:
/
A    :   5000 Kg
B    :  17000 Kg
C    :  22000 Kg
D    :  15000 Kg
TOTAL:  59000 Kg
\

Sample application output:
{
    "A": "5900 Kg",
    "B": "17900 Kg",
    "C": "22900 Kg",
    "D": "15900 Kg",
    "TOTAL": "62600 Kg",
    "VALID": "TRUE"
}

For testing with a serial simulator:
socat -d -d pty,raw,echo=0 pty,raw,echo=0

Use the resulting endpoint for reading (in PacificConnect argument) and writing (simulator config).

Assumption:
Total size of one block is assumed as less than 256 bytes.


