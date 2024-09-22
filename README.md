# sillyTimer
My own timer on Qt for Linux!

### Arch Linux install...
1. Copy the files to the bin directory:
```sudo cp /<absolutePathTo>/sillyTimer/build/Desktop-Release/sillyTimer /usr/local/bin```
2. Move ```stopwatch-solid.svg``` to a convenient directory and remember the path.
3. Create a sillyTimer.desktop file in ```~/.local/share/applications```
4. Add this to the file:
   ```
   [Desktop Entry]
   Type=Application
   Name=sillyTimer
   Exec=/usr/local/bin/
   Icon=/path/to/stopwatch-solid.svg
   ```
