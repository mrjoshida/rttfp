from threading import Timer
from omxplayer.player import OMXPlayer
from pathlib import Path
from pynput import keyboard
import psutil
import json

# Kill all running omxplayer instances
for proc in psutil.process_iter():
    if "omxplayer" in proc.name():
        proc.kill()

args_basic = ['--no-osd', '--no-keys']
# Window mode for testing
args_basic = args_basic + ['--win', '0 200 400 400']
args_static = args_basic + ['--layer', '3', '--alpha', '127', '--loop']
args = args_basic + ['--layer', '2', '--aspect-mode', 'fill']
args_loop = args_basic + ['--layer', '1', '--loop']
print(args_loop)

file = open('video.json', 'r')
data = json.load(file)
print(data)

def stop_static():
    static.pause()
    static.hide_video()

def static_transition(*args):
    static.show_video()
    static.set_alpha(127)
    static.play()
    t = Timer(1.0, stop_static)
    t.start()

static_path = Path("static.mp4")
background_path = Path("logo.mp4")
looper = OMXPlayer(background_path, args=args_loop, dbus_name="omxplayer.player0")
player = OMXPlayer(background_path, args=args, dbus_name="omxplayer.player1")
static = OMXPlayer(static_path, args=args_static, dbus_name="omxplayer.player2")
static.hide_video()
static.pause()
static.set_alpha(127)
player.hide_video()
player.pause()
#static.hide_video()
looper.exitEvent += static_transition
player.exitEvent += static_transition

def on_press(key):
    if key == keyboard.Key.esc:
        try:
            static.stop()
        except:
            print("static not running")
        try:
            player.stop()
        except:
            print("player not running")
        try:
            looper.stop()
        except:
            print("looper not running")
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
            #looper.load(background_path)
                
        print(video)


    
with keyboard.Listener(on_press=on_press) as listener:
    listener.join()




