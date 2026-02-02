# Blood Gala

Blood Gala is TurboCity Games' submission to Global Game Jam Vancouver 2026.

# Download

Pre-built binaries for Windows are available for download on the game's [itch.io page](https://turbocitygames.itch.io/blood-gala).

# Build from Source

Blood Gala can be built using CMake.

## *nix

This process has been tested successfully on both MacOS and Linux.

1. Clone the repository, then pull the LeoEngine submodule with `git submodule init` and `git submodule update`.
2. Change directory to `GlobalGameJamVancouver2026/lib/LeoEngine/tools/unix/` and run `bash pre_first_build.sh`. This will pull the LeoEngine submodules including SDL, and the vendored libraries they themselves use.
3. Return to the repository's root directory and run `cmake . -Bbuild`.
4. Finally, change directory to `GlobalGameJamVancouver2026/build/` and run `make`. This will generate an executable.

This does not copy any of the asset files to where they need to be. 

On Linux:

6. Copy each folder from `GlobalGameJamVancouver2026/resources/` to `GlobalGameJamVancouver/build/`

On MacOS:

6. Copy each folder from `GlobalGameJamVancouver2026/resources/` to `GlobalGameJamVancouver/build/GlobalGameJamVancouver2026.app/Content/Resources/`.

Now you should be able to run the executable (or app bundle, on MacOS) without any errors.

## Windows

1. Clone the repository, then pull the LeoEngine submodule with `git submodule init` and `git submodule update`.
2. Change directory to `GlobalGameJamVancouver2026/lib/LeoEngine/tools/windows/` and run `pre_first_build.bat`. This will pull the LeoEngine submodules including SDL, and the vendored libraries they themselves use.
3. Open Visual Studio and choose 'Open Folder'. Select the repository's root directory.
4. Visual Studio should detect that you're working with CMake and start configuring your project automatically. If not, click on 'Project' -> 'Configure' from the function menu.
5. Now, build the project as you would anything else in Visual Studio.

This does not copy any of the asset files to where they need to be.

6. Copy each folder from `GlobalGameJamVancouver2026/resources/` to `GlobalGameJamVancouver/out/x64/<Debug/Release>/`.

Now you should be able to run the executable without any errors.
