
# 3DRadSpace

3DRadSpace is a free, simple to use, rapid application development game engine. Still in very early development. 

[![Visual Studio](https://img.shields.io/badge/--6C33AF?logo=visual%20studio)](https://visualstudio.microsoft.com/)
[![Github all releases](https://img.shields.io/github/downloads/3DRadSpace/3D_Rad_Space/total.svg)](https://GitHub.com/3DRadSpace/3D_Rad_Space/releases/)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/fb1763ca6663456f934c96ad109aefd8)](https://www.codacy.com/gh/NicusorN5/3D_Rad_Space/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=NicusorN5/3D_Rad_Space&amp;utm_campaign=Badge_Grade)
[![Discord](https://img.shields.io/discord/319515587263070209.svg?label=&logo=discord&logoColor=ffffff&color=7389D8&labelColor=6A7EC2)](https://discord.gg/9BcQQyu)
[![Website shields.io](https://img.shields.io/website-up-down-green-red/http/3dradspace.com.svg)](http://3dradspace.com/)
[![GitHub issues](https://img.shields.io/github/issues/3DRadSpace/3D_Rad_Space.svg)](https://GitHub.com/3DRadSpace/3D_Rad_Space/issues/)
[![CC-0 license](https://img.shields.io/badge/License-CC--0-blue.svg)](https://creativecommons.org/licenses/by-nd/4.0)

# Downloading releases

Old releases can be found [here](https://github.com/3DRadSpace/3D_Rad_Space/releases) (Lastest release: 0.0.6a, currently working on 0.1.0a)

# Building 3DRadSpace

1.) Download the source using Git
`git clone https://github.com/3DRadSpace/3D_Rad_Space`

2.) Install the dependencies:

- Discord RPC
> Link: https://github.com/discord/discord-rpc
>
> Already included in `<root>\3DRadSpace\ExtLibs\discord-rpc`
>
> Binaries for are needed for `x64-Debug` and `Win32-Debug` configurations. 
- Google test
> Install using vcpkg:
>
> `vcpkg install gtest:x86-Windows`  
>
> `vcpkg install gtest:x64-Windows`
- Windows API 
> Included in Windows SDK
>
> ⚠️ Source won't compile if using versions < 10.0.20348.0
- DirectX11 Toolkit (directxtk_desktop_2019)
> Can be easily installed by using NuGet.
- Assimp
> Can be easily installed using NuGet.

2.) Open the .sln file ( `\3DRadSpace\3DRadSpace.sln` ) using Visual Studio 2022

3.) Upgrade the Windows SDK version to atleast 10.0.20348.0 in `3DRadSpace_Editor_WINDX11` project properties.

4.) Set the starting project to `3DRadSpace_Editor_WINDX11`

5.) Compile the solution (Ctrl+Shift+B) with any desired configuration (`Debug`/`Release`, `x86`/`x64`)
