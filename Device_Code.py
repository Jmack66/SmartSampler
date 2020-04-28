import RPi.GPIO as gpio
import time

gpio.setwarnings(False)
gpio.setmode(gpio.BOARD)

gpio.setup(12,gpio.OUT)
gpio.setup(16, gpio.IN)

stepperPin = [18,22,24,26]
gpio.setup(18,gpio.OUT)
gpio.setup(22,gpio.OUT)
gpio.setup(24,gpio.OUT)
gpio.setup(26,gpio.OUT)

servo = gpio.PWM(12,50)

servo.start(0)

gpio.output(12,True)


def servoController(angle):
	out = (angle / 18) + 2
	gpio.output(12,True)
	pwm.ChangeDutyCycle(out)
	gpio.output(12,False)

def infraredInput():
	ir = gpio.input(16)
	print(ir)

def stepperController(rotate):
	seq = [[1,0,0,0],[1,1,0,0],[0,1,0,0],[0,1,1,0],[0,0,1,0],[0,0,1,1],[0,0,0,1],[1,0,0,1]]
	if rotate:
		for i in range(128):
			for step in range(8):
					for pin in range(4):
						gpio.output(stepperPin[pin], seq[step][pin])
				time.sleep(0.002)	

def main():
	servoController(0)
	stepperController(True)
	for i in range(100):
		infraredInput()
	servoController(90)



main()
gpio.cleanup()
