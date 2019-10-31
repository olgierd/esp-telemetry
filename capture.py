#!/usr/bin/env python3

import datetime
import pcap
import sys

if len(sys.argv) != 2:
    print(f"Usage: {sys.argv[0]} iface")
    sys.exit(1)

dev = sys.argv[1]

sniffer = pcap.pcap(dev, promisc=True, immediate=True, timeout_ms=50)

for x in sniffer:
    payload = x[1]
    power = payload[14]
    if payload[18] == 0x88:
        try:
            bssid = payload[28:32].decode("UTF-8")
            if bssid == 'XDXD':
                print(str(datetime.datetime.utcnow()), "PWR:", power, '*'*(power-150))
                data = payload[56:62] # six bytes of data
                print("Data:", data, int(data[0])*256+int(data[1]))
        except:
            print("wow - is somebody using 0x88 frames too?")


