from inputs import get_gamepad
import serial
ser = serial.Serial('COM4')
ser.baudrate = 9600


speed1 = 0
speed2 = 0
speed3 = 0
speed4 = 0

while 1:
    events = get_gamepad()
    for event in events:
        # print(event.code, event.state)

        if ((event.code == "ABS_Y" or event.code == "ABS_X") and (event.state <= 50 or event.state >= -50)):
            speed1 = 0
            speed2 = 0
            speed3 = 0
            speed4 = 0
        
        if event.code == "ABS_Y":
            speed = event.state
            if (speed > 50):
                print("Move forward ")
                OldRange = (32512 - 0)  
                NewRange = (255 - 0)  
                NewValue = int((((speed - 0) * NewRange) / OldRange) + 0)
                speed1 = NewValue
                speed2 = NewValue
                speed3 = NewValue
                speed4 = NewValue
                print(NewValue)

            if (speed < -50):
                print("Move backward ")
                OldRange = (32768 - 0)  
                NewRange = (255 - 0)  
                NewValue = int((((speed - 0) * NewRange) / OldRange) + 0)
                speed1 = NewValue
                speed2 = NewValue
                speed3 = NewValue
                speed4 = NewValue
                print(NewValue)

        if event.code == "ABS_X":
            speed = event.state

            if (speed <= 50 and speed >= -50):
                ser.write(bytes('$1 0 0 0 0;', 'utf-8'))
            
            if (speed > 50):
                print("Move RIGHT")
                OldRange = (32512 - 0)  
                NewRange = (255 - 0)  
                NewValue = int((((speed - 0) * NewRange) / OldRange) + 0)
                speed1 = - NewValue
                speed2 = NewValue
                speed3 = NewValue
                speed4 = - NewValue
                print(NewValue)

            if (speed < -50):
                print("Move LEFT")
                OldRange = (32768 - 0)  
                NewRange = (255 - 0)  
                NewValue = int((((speed - 0) * NewRange) / OldRange) + 0)
                speed1 = abs(NewValue)
                speed2 = NewValue
                speed3 = NewValue
                speed4 = abs(NewValue)
                print(NewValue)

        ser.write(bytes('$1 ' + str(speed1) + ' ' + str(speed2) + ' ' + str(speed3) + ' ' + str(speed4) + ';', 'utf-8'))
            
        if event.code == "ABS_HAT0Y" and event.state == -1:
            ser.write(bytes('$1 100 100 100 100;', 'utf-8'))
            print("Move forward");

        if event.code == "ABS_HAT0Y" and event.state == 0:
            ser.write(bytes('$1 0 0 0 0;', 'utf-8'))
