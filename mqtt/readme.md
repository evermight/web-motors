# Passwords
To password protect your mqtt create a file `passwd` like this: 

```
username1:password1
username2:password2
```
Add more usernames and passwords as needed.

Then run this command to encrypt the passwords:

```
mosquitto_passwd -U passwd
```
Then provide the full path to your `passwd` file in your `mosquitto.conf`.  For example

```
... other lines in your mosquitto.conf ...

password_file /etc/mosquitto/passwd

... other lines in your mosquitto.conf ...

```


# Disable SSL
If you do not  wish to use SSL (eg. for testing or just to test thigns out), you can comment out the `certfile, cafile keyfile` in `mosquitto.conf`.
