# SDHD Gunplay Tweaks

Tweaks to make guns more accurate and satisfying in Sleeping Dogs: Definitive Edition

https://github.com/gaycoderprincess/SDHDGunplayTweaks/assets/163012979/8ec2f93e-6126-47f5-8827-5791d89a5cd2

## Installation

- Make sure you have the latest Steam version of the game, as this is the only version this plugin is compatible with. (exe size of 37490688 bytes)
- Plop the files into your game folder, edit `SDHDGunplayTweaks_gcp.toml` to change the options to your liking.
- Enjoy, nya~ :3

## Feature List

- Disables auto-aim entirely, regardless of the in-game setting
- Removes random spread from weapons, making them a lot more accurate
- Extra option to remove the car steering deadzone as I didn't want to have a separate project just for that >w<
- Simple configuration file to enable or disable any of these options at any time

## Building

Building is done on an Arch Linux system with CLion and vcpkg being used for the build process. 

Before you begin, clone [nya-common](https://github.com/gaycoderprincess/nya-common) to a folder next to this one, so it can be found.

Required packages: `mingw-w64-gcc vcpkg`

To install all dependencies, use:
```console
vcpkg install tomlplusplus:x86-mingw-static
```

Once installed, copy files from `~/.vcpkg/vcpkg/installed/x64-mingw-static/`:

- `include` dir to `nya-common/3rdparty`
- `lib` dir to `nya-common/lib64`

You should be able to build the project now in CLion.
