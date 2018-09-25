# esp8266-keypad-mqtt
Connect a Keypad to an MQTT server with an ESP8266

I used a Wingoneer keypad that came in a pack of 5 and just wired from left to right to D1 - D7 and the last pin to D0 on a WeMos D1 Mini.

I don't really plan on doing much more with it and don't plan on offering support if you can't get it to work, as I'm definitely a n00b when it comes to this stuff.

I did it in PlatformIO but it didn't seem to put the libraries in the folder like I've seen on other projects so you'll probably have to install them.

By default it will send whatever number you punch in to /keypad/KEY on your MQTT broker when you press * on the keypad.

I tried to make everything easy to customize but got a little stuck on making the topic easy to customize so if you want to fix that and submit a pull that'd be great.

Enjoy.
