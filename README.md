# 3DRadSpace

3DRadSpace is a free, simple to use, rapid application development game engine. Still in very early development. 

![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?logo=cmake&logoColor=white)
[![Github all releases](https://img.shields.io/github/downloads/3DRadSpace/3D_Rad_Space/total.svg)](https://GitHub.com/3DRadSpace/3D_Rad_Space/releases/)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/fb1763ca6663456f934c96ad109aefd8)](https://www.codacy.com/gh/3DRadSpace/3D_Rad_Space/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=3DRadSpace/3D_Rad_Space&amp;utm_campaign=Badge_Grade)
[![Discord](https://img.shields.io/discord/319515587263070209.svg?label=&logo=discord&logoColor=ffffff&color=7389D8&labelColor=6A7EC2)](https://discord.gg/9BcQQyu)
[![Website shields.io](https://img.shields.io/website-up-down-green-red/http/3dradspace.github.io.svg)](http://3dradspace.github.io/)
[![GitHub issues](https://img.shields.io/github/issues/3DRadSpace/3D_Rad_Space.svg)](https://GitHub.com/3DRadSpace/3D_Rad_Space/issues/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

# Downloading releases

Old releases can be found [here](https://github.com/3DRadSpace/3D_Rad_Space/releases) (Lastest release: 0.0.6a, currently working on 0.1.0a)

# Current build status

<table>
    <tr>
        <td>Platform</td>
        <td>Name</td>
        <td>Status</td>
    </tr>
    <tr>
        <td rowspan="4">Windows-x64</td>
        <td>C++ Build (CMake)</td>
        <td align="center"><img src="https://github.com/3DRadSpace/3D_Rad_Space/actions/workflows/cmake-windows-x64.yml/badge.svg" alt="Windows-x64"></td>
    </tr>
    <tr>
        <td>C++ Tests (GTest)</td>
        <td align="center"><img src="https://github.com/3DRadSpace/3D_Rad_Space/actions/workflows/cpp-test-windows-x64.yml/badge.svg" alt="C++-Tests"></td>
    </tr>
    <tr>
     <td>C# (MSBuild)</td>
     <td align="center"><img src="https://github.com/3DRadSpace/3D_Rad_Space/actions/workflows/msbuild.yml/badge.svg" alt="CSharp-Windows-x64"></td>
    </tr>
    <tr>
     <td>Visual Studio plugin</td>
     <td align="center"><img src="https://github.com/3DRadSpace/3D_Rad_Space/actions/workflows/vsplugin.yml/badge.svg" alt="Visual-Studio-Plugin"></td>
    </tr>
</table>

# Building 3DRadSpace

1.) Download the source using Git
`git clone https://github.com/3DRadSpace/3D_Rad_Space`

2.) Install the dependencies

- **Windows API** : Included in Windows SDK, install from VS Installer, use latest version.
- **DirectX11 Toolkit** (directxtk_desktop_2019) `.\vcpkg install directxtk:x64-Windows`
- **Assimp** `.\vcpkg install assimp:x64-Windows`
- **nlohmann JSON** `.\vcpkg install nlohmann-json:x64-windows`
- **Freetype** `.\vcpkg install freetype:x64-windows`
- **OpenAL-Soft** `.\vcpkg install openal-soft:x64-windows`
- **NVidia PhysX 5.30** `.\vcpkg install physx:x64-windows` 
- **Vorbis** `.\vcpkg install libvorbis:x64-windows`
- *AngelScript* (Optional, for the AngelScript plugin) `.\vcpkg install angelscript:x64-windows`
- *Google test* (Optional, for test units.) `vcpkg install gtest:x64-windows`
- *nethost* (Optional, for C# plugin) `vcpkg install nethost:x64-windows`

2.) Open the folder as a CMake project (preferably using Visual Studio 2022 / other IDEs were not tested yet).

3.) Set the starting project to `3DRadSpace-editor.exe`.

4.) Compile the solution (Ctrl+Shift+B or F5) with any desired configuration (`x64-Debug`/`x64-Release`).

Notices: 

- Only x64-Windows is supported. No support for x86 is planned. 
- Native Linux support is eventually planned, but will be implemented much later.

# License 
 This project uses a MIT license.
