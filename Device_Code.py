import RPi.GPIO as gpio
from time import sleep
gpio.setwarnings(False)
gpio.setmode(gpio.BOARD)

gpio.setup(12,gpio.OUT)
gpio.setup(18,gpio.OUT)
gpio.setup(22,gpio.OUT)
gpio.setup(24,gpio.OUT)
gpio.setup(26,gpio.OUT)
servo = gpio.PWM(12,50)

servo.start(0)

gpio.output(12,True)

servo.ChangeDutyCycle(90)
gpio.output(18,1)
sleep(1)
servo.ChangeDutyCycle(0)
gpio.output(12,False)

gpio.cleanup()