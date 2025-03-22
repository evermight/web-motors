# Setup

As of current release, we only need HTML JS to connect to MQTT server.

PHP API isn't being used right now.


Install apache server like this:

```
apt-get install -y apache2
```

Fill in the details to configure your esp32. Example of details:

```
MQTT_SERVER: ip address or tld, protocol prefix not necessary (eg. acmecorp.com)
MQTT_PORT: 9102
MQTT_TOPIC: use the same topic as your esp32
MQTT_USER: specified in your /etc/mosquitto/passwd
MQTT_PASS: specified in your /etc/mosquitto/passwd
```


