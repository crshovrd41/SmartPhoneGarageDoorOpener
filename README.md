# SmartPhoneGarageDoorOpener
An Arduino Sketch for the Adafruit Feather Huzzah board that uses the Blynk Framework to open a garage door.

I've updated the code to be compatible with blynk.cloud, as the blynk app is no longer available for new users.

# Updates:
- Moved doorStatePin from 2 to pin 13. If the door was closed and the unit reset, it would not boot because pin 2 would be pulled down
- Updated the formatting and deleted unused code
- Changed the pinMode of the new doorStatePin to INPUT_PULLUP

# Setting up datastreams in Blynk.cloud
You only need 3, please see the screen shot

<img width="1122" alt="Screen Shot 2021-10-13 at 12 47 43 AM" src="https://user-images.githubusercontent.com/35728378/137089891-938a7116-5dc0-4dfa-abd8-6abab1331e13.png">

## **Note that you can only disable the warnings if the door is open

### If I get around to adding more error checking, I will, but the original is pretty good. I'd like to try and log the actions if possible but that may require some separate fanciness that I just don't care about.
