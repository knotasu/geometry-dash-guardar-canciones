# Template Mod

# Guardar Canciones

A simple and efficient Geometry Dash mod that adds a one-click button to automatically save a level's custom song to a dedicated folder on your device. No more digging through system folders to find your favorite tracks!

## Features

- One-Click Save: A blue download button appears on every LevelInfoLayer page.
- Automatic Folder Creation: The mod automatically creates a folder named "MUSICA KNOTASU MOD" in the appropriate directory for your platform.
- Smart File Detection: It intelligently locates the downloaded song file (.mp3 or .ogg) from the game's cache.
- Original Naming: Songs are saved using their original Song ID (e.g., 1105696.mp3), making them easy to identify.
- Zero Configuration: Just install the mod and its dependency, and it works out of the box.

## Where Are My Songs Saved?

The mod saves the files in a folder called "MUSICA KNOTASU MOD" located in a platform-specific directory:

Windows:
C:\Users\[YourUsername]\Documents\MUSICA KNOTASU MOD\
(If you use OneDrive, it might be in OneDrive\Documents\MUSICA KNOTASU MOD)

Linux:
/home/[YourUsername]/Música/MUSICA KNOTASU MOD/
(If "Música" doesn't exist, it will use ~/Music/MUSICA KNOTASU MOD/)

Android (Work in Progress - Help wanted!):
/storage/emulated/0/Android/data/com.robtop.geometryjazz/files/MUSICA KNOTASU MOD/

## Dependencies

This mod requires the Node IDs mod to function correctly. It will not work without it.

## Planned Features / Help Wanted

- Android Support: The build for Android is currently facing a technical issue with the NDK. If you have experience with NDK r23+ and Geode mods, your help would be incredibly valuable!
- iOS Support: Not yet planned, but contributions are welcome.

## How to Use

1. Ensure you have the Node IDs mod installed and enabled.
2. Open any level in Geometry Dash that uses a custom song.
3. Look for the blue download button located on the right side of the screen.
4. Click the button. If the song is found, a success message will appear, and the file will be copied to your MUSICA KNOTASU MOD folder.

## Credits

Developed by knotasu.

Special thanks to the Geode Team for creating an incredible modding ecosystem, and to the Geometry Dash community for the constant inspiration.

Happy listening!
