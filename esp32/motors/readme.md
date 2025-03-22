
# Setup

## Create config.h

Make a copy of `config.sample.h` to `config.h`.

Update the SSID information. The esp32 will broadcast a wifi hotspot.  You connect to this hotspot to configure details like the wifi network you want to use, mqtt server, etc.. etc..

Update chip pin information. 

## Upload code

Connect your esp32 to Arduino

Turn on the Serial Port Monitor

Press Upload

Look at the Serial Port Monitor for the IP address of the esp32 wifi hotspot.  Last time I saw **192.168.4.1** -- I am not sure if this is constant or if it is variable.

## Configure esp32

Go to a computer with wifi abilities.

Connect to the esp32 wifi hotspot using the credentials you specified in config.h

Open a web browser and visit `http://ip-address-mentioned-in-serial-monitor`

Fill in the details to configure your esp32. Example of details:

```
SSID: name of wifi network that will let you connect to MQTT
PASS: password of the SSID
MQTT_SERVER: ip address or tld, protocol prefix not necessary (eg. acmecorp.com)
MQTT_PORT: 9101
MQTT_TOPIC: use the same topic as your web controller, pick any topic name, letters and numbers only
MQTT_USER: specified in your /etc/mosquitto/passwd
MQTT_PASS: specified in your /etc/mosquitto/passwd
API_URL: I think this is currently deprecated and does nothing
```


## Reset esp32

There is a button on the esp32 chip that let's you reset and re-configure the esp32.  I am not clear if the esp32 ip address is variable or if it is constant.  If it variable, then resetting is not very useful.  You would have to use the Arduino Serial Monitor to get the wifi ip address again.


