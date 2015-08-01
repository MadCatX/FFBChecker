FFBChecker
===

Description
---
This tool of a very unimaginative name is mainly intended to test implementation of [Force Feedback](https://en.wikipedia.org/wiki/Haptic_technology) on Linux systems. It has a Qt5-based GUI that allows the user to set up parameters of the effects and play them back on their devices. Only Linux Force Feedback API and SDL2 is supported at the moment. Support for other interfaces such as [DirectInput](https://msdn.microsoft.com/en-us/library/windows/desktop/ee418273(v=vs.85).aspx) might be added in the future.


Usage
---
Choose the device on which you want to play the effects from the *Devices* combobox. If the desired device does not appear in the menu, try clicking *Refresh* to update the list of detected devices. Devices that you do not have access to due to insufficient privileges will **not** appear in the list. Once the device has been selected and successfully opened by FFBChecker you can set up effect parameters using the entry fields below.


Remarks
---

 * Effects of finite duration will still be listed as *Playing* by the GUI. Most Linux Force Feedback drivers do not report back when a finite effect has finished playing and FFBChecker does not currently check for respective event anyway.
 * Clicking the *Start* button will upload the effect automatically if the effect has not been uploded before. Similar thing applies for the *Remove* button which stops the effect before it tries to remove it from the device.
 * Clicking *Upload/Update* button on a playing effect will issue "live" update of the effect's parameters.
 * Clicking *Start* when the selected effect is listed as *Playing* has no effect even if the parameters of the effect have changed or if the effect has finished playing. Use the *Stop* button to stop the effect and then *Start* again to restart it.
 * Clicking *Start* when the selected effect is already listed as *Uploaded* does **not** update the parameters of the effect. If you adjusted the parameters after the effect had been uploaded, use the *Upload/Update* to pass the new parameters to your device.


Build/Installation
---

cd into the source directory and run:

	mkdir build
	cd build
	cmake ../ -DCMAKE_BUILD_TYPE=Release
	make

Note that at least CMake 2.8.13 is required. SDL2 header files and PkgConfig are required to enable SDL2 support.

To launch FFBChecker, run:

	./FFBChecker
