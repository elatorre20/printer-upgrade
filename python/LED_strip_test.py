import machine
import time

pot = machine.ADC(machine.Pin(28))
R = machine.PWM(machine.Pin(17))
G = machine.PWM(machine.Pin(16))
B = machine.PWM(machine.Pin(18))

def debug_adc(n = 100):
    for i in range(n):
        print(pot.read_u16())
        time.sleep_ms(200)
        
def debug_LED():
    for i in range(10,0,-1):
        R.duty_u16(65535//i)
        for j in range(10,0,-1):
            G.duty_u16(65535//j)
            for k in range(10,0,-1):
                B.duty_u16(65535//k)
                time.sleep_ms(100)

