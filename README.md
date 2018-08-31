# ArduinoCore-blackfin

This is an Arduino core for BF70x Blackfin+ DSP chips.

![Alt text](dsp_feather.JPG)

## Installation
* If you do not already have a `hardware` folder in your Arduino directory, create one. On windows this is usually `C:\Users\{username}\Documents\Arduino\hardware`

* inside this `hardware` folder, create a `deanm1278` folder and clone this repo inside that folder. Rename the cloned repo from `ArduinoCore-blackfin` to `bfin`. You should now have this repo located at `C:\Users\{username}\Documents\Arduino\hardware\deanm1278\bfin`

* in the root of the repo, run `git submodule init` and then `git submodule update` to get the processor header files.

* download and extract the latest toolchain for your operating system from [here](https://github.com/deanm1278/blackfin-plus-gnu/releases) and extract to the root of this repository. Rename the extracted folder to `toolchain`. You should now have a folder `C:\Users\{username}\Documents\Arduino\hardware\deanm1278\bfin\toolchain` that contains a bunch of directories including `bfin-elf\`, `bin\`, `include\`, and so on.
