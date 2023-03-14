# Filename appender
This little renaming tool was created for Pokemon Infinite Fusion in order to help with renaming alternate sprites in bulk.
The program checks all regular files in its assigned working directory, comparing their names to all other files in said directory *and its subdirectories*.
Any duplicates get a letter added to the end of their filenames in alphabetical order.
The program is built to work specifically in a file structure like Pokemon Infinite Fusion's `CustomBattlers`.

## How to use:
1. Move `Filename_appender.exe` to a handy location, like Pokemon Infinite Fusion's game folder.
1. Start `Filename_appender.exe`.
1. When prompted to enter a directory, type a path to `Graphics\CustomBattlers\` and press Enter.
    - Alternatively, you can move `Filename_appender.exe` directly to `Graphics\CustomBattlers\`, start it from there and just press Enter when prompted for a directory to use the one the program was launched from.
1. The program will now scan the working directory for incoming custom sprites and if any are found, it will append a character to the end of the incoming file's name.

Any changes the program makes will be shown on the console afterwards.
