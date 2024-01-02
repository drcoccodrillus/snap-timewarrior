# Timewarrior

CLI tool for time tracking.

Timewarrior is a time tracking utility that offers simple stopwatch features as well as sophisticated calendar-base backfill, along with flexible reporting. It is a portable, well supported and very active, Open Source project.
The git repository of this project is available at https://github.com/GothenburgBitFactory/timewarrior

***

## Snap building
The snap can be built using snapcraft. The snapcraft.yaml file is located in the snap directory. To build the snap, use the following command:

`snapcraft`

Run the command from the `snap-timewarrior` directory.

## Snap installation
The installation process is quite simple and you can install the snap in two different ways:
- From the snap store
- From a local file

### Install from the snap store

The easiest way is to install the snap from the snap store. To do so, use the following command:

`snap install timewarrior`

[![Get it from the Snap Store](https://snapcraft.io/static/images/badges/en/snap-store-white.svg)](https://snapcraft.io/timewarrior)


If you prefer to install the snap from a local file, follow the instructions below.

### Install from a local file

#### Download the snap

First select the [release](https://github.com/drcoccodrillus/snap-timewarrior/releases/) you want to install and download the corresponding snap file.

#### Install the snap

For amd64:

`snap install timewarrior_1.4.2_amd64.snap --dangerous`

For arm64:

`snap install timewarrior_1.4.2_arm64.snap --dangerous`

For armhf:

`snap install timewarrior_1.4.2_armhf.snap --dangerous`

For ppc64el:

`snap install timewarrior_1.4.2_ppc64el.snap --dangerous`

For s390x:

`snap install timewarrior_1.4.2_s390x.snap --dangerous`

### Before using it

You can avoid this step and go directly to the [usage](#usage) section. The snap will work without any further configuration.

However, if you want to use this tool with the `timew` shortcut, you need to create a snap alias. To do this, execute the following command:

`snap alias timewarrior timew`

## Usage

To start a new time tracking session, run:

`timewarrior start` or `timew start` (alias)

To stop the session, run:

`timewarrior stop` or `timew stop` (alias)

To see the tracked time, run:

`timewarrior summary` or `timew summary` (alias)

For more information about the usage, please refer to the [official documentation](https://timewarrior.net/docs/).