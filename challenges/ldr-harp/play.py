import time
from pygame import mixer
import sys
import serial

args = sys.argv
print args
if len(args) < 2:
	print "Please specify COM port"
	sys.exit(1)
strPort = args[1]

soundfile = "loop_amen_full.wav"

if len(args) > 2:
	soundfile = args[2]
	

mixer.pre_init(44100, -16, 12, 512)
mixer.init()

sound =  mixer.Sound(soundfile)

#strPort = '/dev/ttyACM0'
#strPort = 'COM19'
ser = serial.Serial(strPort, 9600)

#sound.play()
#time.sleep(3)
while 1:
    line = ser.readline().strip()
    print line 
    if line == 'ON': 
        sound.play(loops = -1)
    if line == 'OFF':
        sound.stop()
		

