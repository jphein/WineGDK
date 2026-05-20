# jphein/WineGDK Fork

Fork of [Weather-OS/WineGDK](https://github.com/Weather-OS/WineGDK) for running Minecraft Bedrock Edition on Linux.

## Status: WORKING

Minecraft Bedrock 1.26.21 renders and runs correctly on this fork. The previous black screen issue was caused by using the wrong game binary (1.26.3 instead of 1.26.21), not a Wine/WineGDK problem.

## Purpose

Testing and developing Wine patches for Minecraft Bedrock 1.26.21+ on NVIDIA GPUs under Wayland/XWayland. Part of the [minecraft-bedrock-linux](https://github.com/jphein/minecraft-bedrock-linux) project.

## Changes from upstream

### D3D11 patches (dlls/d3d11/device.c)

These patches are harmless but were not the fix for the black screen. The root cause was using the wrong game binary.

- **FORMAT_SUPPORT2 stub** -- `CheckFeatureSupport(D3D11_FEATURE_FORMAT_SUPPORT2)` returns `S_OK` with `OutFormatSupport2=0` instead of `E_NOTIMPL`. bgfx queries this during initialization. This stub avoids an `E_NOTIMPL` return but was not required for the game to render.

- **CreateBuffer bind flags trace** -- Added TRACE logging of `D3D11_BUFFER_DESC` fields (ByteWidth, Usage, BindFlags, CPUAccessFlags, MiscFlags) to `d3d11_device_CreateBuffer`. Diagnostic only.

### clang-23 build fix (dlls/windows.storage.dll)

The clang-23 build fixed a windows.storage.dll linkage bug caused by a C/C++ extern mismatch. This DLL was missing from clang-20 builds. However, the game works on both clang-20 and clang-23 builds regardless, so this DLL is not required for Minecraft Bedrock to run.

### Build

Both clang-20 and clang-23 produce working builds on Ubuntu 24.04:

```bash
# clang-20
./configure --prefix=$PWD/install --enable-archs=x86_64 CC=clang-20 CXX=clang++-20
make -j$(nproc) && make install

# clang-23
./configure --prefix=$PWD/install --enable-archs=x86_64 CC=clang-23 CXX=clang++-23
make -j$(nproc) && make install
```

## Root cause of the black screen

The black screen (bgfx issuing zero D3D11 draw calls) was caused by running the wrong game binary -- Minecraft Bedrock 1.26.3 instead of 1.26.21. With the correct 1.26.21 binary, the game renders on both clang-20 and clang-23 WineGDK builds without any additional patches. See [minecraft-bedrock-linux#5](https://github.com/jphein/minecraft-bedrock-linux/issues/5) for the full investigation history.

## Related repos

- [jphein/minecraft-bedrock-linux](https://github.com/jphein/minecraft-bedrock-linux) -- Main project: scripts, stubs, documentation
- [jphein/GDK-Proton](https://github.com/jphein/GDK-Proton) -- Our GDK-Proton fork (Proton + WineGDK)
- [Weather-OS/WineGDK](https://github.com/Weather-OS/WineGDK) -- Upstream
- [Weather-OS/WineGDK#54](https://github.com/Weather-OS/WineGDK/issues/54) -- Upstream issue (works on Intel UHD 620)

## System tested on

- Ubuntu 24.04, kernel 6.8.0-111
- NVIDIA GTX 1650 (TU117), driver 595.58.03
- Wayland (GNOME) + XWayland

---

*See upstream README below for Wine/WineGDK general documentation.*
