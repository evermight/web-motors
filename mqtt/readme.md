# Setup

Install with

```
# for the server
sudo apt-get install -y mosquitto
# for the linux client
sudo apt-get install -y mosquitto-clients
```

Make a backup of `/etc/mosquitto.conf`.

Copy the `mosquitto.conf` in this project to `/etc/mosquitto.conf`.

Create a password to protect your server by make a `/etc/mosquitto/passwd` file like this:

```
username1:password1
username2:password2
```
Add more usernames and passwords as needed.

Run this command to encrypt the passwords:

```
mosquitto_passwd -U /etc/mosquitto/passwd
```

If you change the location of your `passwd`, update the path in `mosquitto.conf`.  For example:

```
... other lines in your mosquitto.conf ...

password_file /etc/mosquitto/passwd

... other lines in your mosquitto.conf ...

```

If you do not wish to use SSL (eg. for testing or just to test thigns out), you can comment out the `certfile, cafile keyfile` in `mosquitto.conf`.

Test connection with these commands from two different sessions:

```
mosquitto_pub -t hello -h localhost -p 9100 -u [username] -P [password] -m "hi"
mosquitto_sub -t hello -h localhost -p 9100 -u [username] -P [password]
```

You can also use port 9101 as mentioned in the `mosquitto.conf` file for the TLS.

For web clients, it must connect on port 9102.
