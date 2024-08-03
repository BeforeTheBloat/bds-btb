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

## ⚒️ Build
To build this project, on the **native branch**, for Windows 10/11 or Linux, you will need to compile this project using CMake.

Or you can grab an executable from our [releases tab](https://github.com/BeforeTheBloat/bds-btb/releases), and run it from there.

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
