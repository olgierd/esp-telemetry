# esp-telemetry
Send raw WiFi packets using ESP8266 and capture them with libpcap.

## ESP firmware
Open code using Arduino IDE and modify according to your needs (channel, delay between packets, some custom data from sensors you'd like to send - maybe deep sleep?).

## Python firmware
Requires your wlan card to be set to `monitor` mode.

* `ifconfig wlp3s0 down`
* `iwconfig wlp3s0 mode monitor`
* `ifconfig wlp3s0 down`
* `airodump-ng wlp3s0 --channel 3`
* `./capture.py`
