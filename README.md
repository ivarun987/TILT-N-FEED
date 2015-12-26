# TILT-N-FEED

Ever realize you forgot to feed your fish and are nowhere near it to feed it? Well now you don't have to worry!

Inspiration -
This project was inspired by being in class all day (the engineering life), unable to take care of a pet and how we could fix that. Most of us out there have wanted a pet fish or have had one, but were always scared you wouldn’t be around to feed it and end up killing it. Many of us who do have fish and go through all the trouble of taking care of it have many difficulties and time conflicts. Going on vacation, weekend trips, daily commute, or going to engineering class on the other side of campus are just hassles that sometimes you wish you could just feed your fish from wherever you were.

What it does -
This product allows you to intimately feed your fish wirelessly in case you forgot to or do not have enough time at home to feed it and want to use the commute to work to feed it or are on vacation.

How it works -
The product is split into three parts that contribute to a total of but not limited to 3 functions/features. The code for all these functions can be found below. The first part is the controller.

The Controller -
The controller is comprised of an arduino microcontroller, a 3 axis accelerometer, a master bluetooth transmitter and a push button. The controller is programmed so that when you want to feed your fish, you have to push the button and shake the controller at the same time.

But what makes this product so different from an ordinary robotic, monotonous fish feeder? Well, first ask yourselves, why do you have a fish, a pet in the first place? You want a friend to take care of and love. Well feeding is one of the most loving actions you could do.

We use hard-coded threshold values for deviations from the baseline acceleration values from when you turn it on to check whether or not you are shaking the controller while the button is pressed. Once the arduino recognizes that you are indeed pressing the button and shaking the controller, it sends a signal over Bluetooth to the receiver on the fish feeder. The next part is the receiver which is connected to the actual fish feeder itself.

The Receiver/Fish Feeder -
The receiver comprises of an arduino, ethernet shield, and bluetooth receiver. The receiver is programmed to continually wait for a signal from the transmitter and when it receives the signal, it sends another signal through wire to the fish feeder.

The actual fish feeder itself is composed of a continuous rotation servo motor, 3D printed water wheel, hopper, and frame. Once the receiver receivers and sends the signal to the feeder, the motor turns for half a second, turning the wheel and dispensing a certain amount of fish food. The hopper is designed to make certain that all fish food put into it, ends up in the wheel and gets dispensed. The last part is thingspeak, the online interface.

Thingspeak -
Thingspeak is used as when the receiver receives the signal, the arduino fetches the current epoch time through the internet and uploads it to Thingspeak.com using the ethernet cable and shield. On Thingspeak, using MATLAB visualization and analysis, statistics about your feeding habits and times are displayed. You check how consistently you feed your fish and you can check how many times you have fed your fish including the last time you have to make sure you feed it every day.

There are many more adaptations available with more and more resources.

Pomotional video can be found here: https://www.youtube.com/watch?v=_lGi-aSByAE

Technical video can be found here: https://www.youtube.com/watch?v=V-xSGFIBDLY
