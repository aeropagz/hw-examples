import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)

GPIO.setup(17, GPIO.OUT)
toggle = False

while(True):
    GPIO.output(17, 1)
    GPIO.output(17, 0)
