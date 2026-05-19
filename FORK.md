# jphein/WineGDK Fork

Fork of [Weather-OS/WineGDK](https://github.com/Weather-OS/WineGDK) for running Minecraft Bedrock Edition on Linux.

## Purpose

Testing and developing Wine patches needed for Minecraft Bedrock 1.26.21+ on NVIDIA GPUs under Wayland/XWayland. Part of the [minecraft-bedrock-linux](https://github.com/jphein/minecraft-bedrock-linux) project.

## Changes from upstream

### D3D11 patches (dlls/d3d11/device.c)

- **FORMAT_SUPPORT2 stub** — `CheckFeatureSupport(D3D11_FEATURE_FORMAT_SUPPORT2)` returns `S_OK` with `OutFormatSupport2=0` instead of `E_NOTIMPL`. bgfx queries this during initialization; the `E_NOTIMPL` may affect code paths downstream.

- **CreateBuffer bind flags trace** — Added TRACE logging of `D3D11_BUFFER_DESC` fields (ByteWidth, Usage, BindFlags, CPUAccessFlags, MiscFlags) to `d3d11_device_CreateBuffer` for debugging vertex/index/constant buffer creation.

### Build

Built with clang-20 on Ubuntu 24.04:
```bash
./configure --prefix=$PWD/install --enable-archs=x86_64 CC=clang-20 CXX=clang++-20
make -j$(nproc) && make install
```

## Current investigation

Minecraft Bedrock shows a black screen because bgfx (the game's rendering layer) issues zero D3D11 draw calls. Vertex buffers are created successfully but never bound to render items. See [minecraft-bedrock-linux#5](https://github.com/jphein/minecraft-bedrock-linux/issues/5) for detailed analysis.

## Related repos

- [jphein/minecraft-bedrock-linux](https://github.com/jphein/minecraft-bedrock-linux) — Main project: scripts, stubs, documentation
- [jphein/GDK-Proton](https://github.com/jphein/GDK-Proton) — Our GDK-Proton fork (Proton + WineGDK)
- [Weather-OS/WineGDK](https://github.com/Weather-OS/WineGDK) — Upstream
- [Weather-OS/WineGDK#54](https://github.com/Weather-OS/WineGDK/issues/54) — Upstream issue (works on Intel UHD 620)

## System tested on

- Ubuntu 24.04, kernel 6.8.0-111
- NVIDIA GTX 1650 (TU117), driver 595.58.03
- Wayland (GNOME) + XWayland

---

*See upstream README below for Wine/WineGDK general documentation.*
