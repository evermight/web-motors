# Setup

This project requires setting up 3 different platforms:


1. mqtt server
2. web server (for html, js and css)
3. esp32

*Note: At one time, the project can be modified to not need an mqtt server.  You can have the web motor esp32 communicate with the `api.com/motions.txt` file.  The web server would then use php files to write the latest actions to `motions.txt`.  This feature is currently commented out of the code.*

**Important:** If you use TLS, then both the web server and the mqtt server must use them.  Either you use TLS on both or none at all.

Set up your mqtt server and web server first.  The readme instructions in each folder will explain.

Set up the esp32 last.  The readme instructions in the foldeder will explain.

