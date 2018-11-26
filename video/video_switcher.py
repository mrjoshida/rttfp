import os
from omxplayer.player import OMXPlayer
from pathlib import Path
from pynput import keyboard
import json

# Kill all running omxplayer instances


args_static = ['--win', '0 250 720 480', '--no-osd', '--no-keys', '--layer', '3']
args = ['--win', '0 250 720 480', '--no-osd', '--no-keys', '--layer', '2']
args_loop = ['--win', '0 250 720 480', '--no-osd', '--no-keys', '--layer', '1', '--loop']

file = open('video.json', 'r')
data = json.load(file)
print(data)

looper = OMXPlayer(Path(data.get("Key.space")["url"]), args=args_loop, dbus_name="omxplayer.player0")
player = OMXPlayer(Path(data.get("Key.space")["url"]), args=args, dbus_name="omxplayer.player1",
                   play_event=static, stop_event=static)
static = OMXPlayer(Path("static.mp4"), args=args_static, dbus_name="omxplayer.player2")
player.hide_video()
static.hide_video()
static.set_alpha(127)


def on_press(key):
    if key == keyboard.Key.esc:
        player.stop()
        looper.stop()
        print("quitting")
        return
    try:
        key = key.char
    except AttributeError:
        key = str(key)
    video = data.get(key, False)
    if video:
        if video['loop'] == 1:
            print("looping")
            #if looper.is_playing(): looper.stop()
            looper.load(Path(video["url"]))
            player.hide_video()
            #if player.is_playing(): player.stop()
        else:
            #if player.is_playing(): player.stop()
            player.load(Path(video["url"]))
            player.show_video()
                
        print(video)


def static():
    static.show_video()
    static.play()
    
with keyboard.Listener(on_press=on_press) as listener:
    listener.join()


