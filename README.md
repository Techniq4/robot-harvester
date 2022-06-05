import serial
import serial.tools.list_ports
import time
from colorama import *
from datetime import datetime
import pyfiglet
import random
####################
# init of fields   #
####################
PORT = 'COM8'
START_TIME = datetime.now()
work = True
loopme = True
####################
#       init      #
####################
init(convert=True)

# port - USB port
portlist = serial.tools.list_ports.comports()
def getDevices():
    devices=[]
    for x in range(len(portlist)):
        devices.append(str(portlist[x]))

    return devices

def progress_bar(progress, total, color=Fore.YELLOW):
    percent = 100*(progress/total)
    bar = '#'*int(percent) + '-'*(100-int(percent))
    print(color + f"\r|{bar}| {percent:2f}%", end="\r")
    if progress==total:
        print(Fore.GREEN + f"\r|{bar}| {percent:.2f}", end="\n")

def initArduino():
    global arduino
    arduino = serial.Serial(port=PORT, baudrate = 9600, timeout=0)
    print(Fore.MAGENTA+"Arduino initialized")

def sendTo(message):
    arduino.write(message.encode())

####################
#    COMMANDS      #
####################

def help():
    print(Fore.RED+"Commands: ")
    print(Fore.RED+"\thelp                    Show this message")
    print(Fore.RED+"\ts1 <angle>              set servo1 angle to <angle argument> (0-180) ex. s1 90")
    print(Fore.RED+"\ts2 <angle>              set servo2 angle to <angle argument> (0-180) ex. s2 90")
    print(Fore.RED+"\ts3 <angle>              set servo3 angle to <angle argument> (0-180) ex. s3 90")
    print(Fore.RED+"\ts4 <angle>              set servo4 angle to <angle argument> (0-180) ex. s4 90")
    print(Fore.RED+"\texit                    use to exit program")

def multi(command):
    print(command)
    code = command.split(" ", 1)
    print(code)
    del code[0]
    commands2=""
    commands2=' '.join(map(str,code))
    print(commands2)
    commands = commands2.split("; ")
    for x in range(len(commands)):
        print(commands[x])
    for x in range(len(commands)):
        if commands[x].startswith("s1"):
            angle = int(commands[x].replace("s1 ", ""))
            sendTo(f"s1,{angle}")
           # print(Fore.MAGENTA+"1 done")
        elif commands[x].startswith("s2"):
            angle = int(commands[x].replace("s2 ", ""))
            sendTo(f"s2,{angle}")
            #print(Fore.MAGENTA+"2 done")
        elif commands[x].startswith("s3"):
            angle = int(commands[x].replace("s3 ", ""))
            sendTo(f"s3,{angle}")
            #print(Fore.MAGENTA+"3 done")
        elif commands[x].startswith("s4"):
            angle = int(commands[x].replace("s4 ", ""))
            sendTo(f"s4,{angle}")
            #print(Fore.MAGENTA+"4 done")
            
        else:
            print(Fore.RED+"Invalid syntax! #multi "+command)
        
        time.sleep(2)

def example1():
    cmd = "s1 60; s2 60; s3 60; s4 180; s4 0; s1 180; s1 120; s2 120; s3 120; s4 180"
    multi(cmd)

def loop(command):
    loopme=True
    if command=="example1":
        while loopme:
            example1()
            
    elif command=="example2":
        while loopme:
            #example2()
            pass
    elif command=="example3":
        while loopme:
            #example3()
            pass
    elif ";" in command:
        while True:
            multi(command)

def editor():
    global work
    while work:
        print(Fore.CYAN)
        now = datetime.now()
        mtime= now.strftime("%H:%M:%S")
        command = input(mtime+" > ")
        if 0==0:
            if command=="help":
                help()

            elif command=="restart":
                print(Fore.RED)
                inp = input("Do you want to restart?")
                if inp == "y" or inp == "Y":
                    init()
                else:
                    pass
            elif command=="exit":
                print(Fore.LIGHTRED_EX)
                rus = input("Are you sure to exit? (Y/n)")
                if rus == "Y" or rus == "y":
                    work=False
                else:
                    pass

            elif command=="example1":
                example1()
            elif ";" in command:
                multi(command)
            elif command.startswith("loop"):
                bruh = command.replace("loop ","", 3)
                print(bruh)
                while True:
                    loop(bruh.replace("loop ","", 3))
            elif command=="stop":
                loopme=False
            elif command.startswith("s1"):
                angle = int(command.replace("s1 ", ""))
                sendTo(f"s1,{angle}")
            elif command.startswith("s2"):
                angle = int(command.replace("s2 ", ""))
                sendTo(f"s2,{angle}")
            elif command.startswith("s3"):
                angle = int(command.replace("s3 ", ""))
                sendTo(f"s3,{angle}")
            elif command.startswith("s4"):
                angle = int(command.replace("s4 ", ""))
                sendTo(f"s4,{angle}")
            
            else:
                print(Fore.RED+"Invalid syntax! #main")



def init():
    print(Fore.BLUE+"Initialization", end="")
    time.sleep(0.5)
    print(".", end="")
    time.sleep(0.7)
    print(".", end="")
    time.sleep(1)
    print(".")
    time.sleep(2)
    progress_bar(0, 100)
   ###    time.sleep(random.randint(0,5)/10)
    time.sleep(1)
    baner = pyfiglet.figlet_format("Robot Arm Controller")
    print(Fore.YELLOW+baner)
    time.sleep(1)
    print(Fore.RED + "Select Arduno port: ")
    for x in range(len(getDevices())):
        print(Fore.GREEN+getDevices()[x])
    PORT = input("Podaj port: ")
    initArduino()
    print(Fore.MAGENTA+str(START_TIME))
    editor()
    

if __name__ == "__main__":
    init()


