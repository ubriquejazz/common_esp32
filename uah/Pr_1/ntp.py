#https://github.com/lettier/ntpclient/blob/master/source/python/ntpclient.py
#(C) 2014 David Lettier.

import socket
import struct
import time

host = "pool.ntp.org"
port = 123
# The NTP epoch starts in 1900; Unix epoch starts in 1970. 
# 2208988800 is the difference in seconds.
NTP_DELTA = 2208988800 

# Create UDP socket
client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Prepare the 48-byte NTP request packet
# \x1b = 0b00011011 (LI=0, VN=3, Mode=3)
data = b'\x1b' + 47 * b'\0'

try:
    # Set a timeout so the script doesn't hang if the server is down
    client.settimeout(5.0)
    
    client.sendto(data, (host, port))
    data, address = client.recvfrom(1024)
    
    # NTP timestamp is in the 10th 'long' (4-byte integer) of the 12-long packet
    # '!12I' means: big-endian (!), 12 elements (12), unsigned integers (I)
    seconds = struct.unpack("!12I", data)[10]
    seconds -= NTP_DELTA
    
    print(f"Server: {host}")
    print(f"Time: {time.ctime(seconds)}")

except socket.timeout:
    print("The request timed out. The server might be busy.")
finally:
    client.close()