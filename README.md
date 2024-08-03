<br/>
<div align="center">
  <a href="https://github.com/BeforeTheBloat/bds-btb/releases">
    <img src="https://github.com/user-attachments/assets/0b813057-82a4-432a-8247-6ed6ef176b51" alt="bds-btb" width="160" height="160">
  </a>
  <h3 align="center">BDS-BTB</h3>
  <p align="center">
    Bedrock Dedicated Server for 1.1 with Lua Plugin Support.
  </p>
</div>
<br/>

## ⚒️ Get Started
To get started, you need to have these system requirements:
 - Windows 10 version and above
 - Ubuntu or Debian
 - ...or really, most operating systems with a working C++ compiler :D

If you just want to get started immediately you can grab an executable from our [releases tab](https://github.com/BeforeTheBloat/bds-btb/releases), and run it from there.

**However if you want to build this project, you will need to compile the code from the native branch, for Windows 10/11 or Linux using CMake.**

### Instructions building on Windows (MSVC)
We use CMake for our projects, but to compile on Windows, MSVC is required to be installed. Mostly MSVC, comes with C++ on Visual Studio, but there are other ways to get MSVC on your device.
```bat
cmake . -Bbin && cmake --build bin && "./bin/bds_btb.exe"
```

### Instructions building on Linux
Similar to Linux, you need to check for a compiler, such as Clang and GCC (the two most recommended compilers for this project on Linux).
```sh
cmake . -Bbin && cmake --build bin && "./bin/bds_btb"
```

### Tested Compilers
- [x] MSVC
- [x] GCC
- [x] Clang

## 🌟 Features
- **Native cross-platform support:** We make it our top priority for Windows and Linux to run well without need of an emulator.
- **High-level Performance:** Fast performance on our app (it's a console program), and is built on C++ which is one of the fastest languages used today.
- **Full of Features:** Every vanilla feature that you would normally be provided with in vanilla Minecraft Bedrock Edition v1.1.x.
- **Super-easy Lua API:** Easy-to-learn Lua API for you to use to make custom plugins and scripts.

## 🎉 Contributing
We openly welcome contributions to this project. If you'd like to contribute, you can do this in a few ways:

### Issue Tracker
If you encounter any issues while using this software, please open an [issue](https://github.com/BeforeTheBloat/bds-btb/issues). Please make sure you have an amazing description and exactly how to recreate this bug.

### Submitting a Pull Request
We :heart: code contributions, and if you have in any way improved our codebase or added a new feature feel free to open a pull request at any time :D

## ⚖️ License
bds-btb is licensed with the [Apache License 2.0](https://github.com/BeforeTheBloat/bds-btb/blob/native/LICENSE).
