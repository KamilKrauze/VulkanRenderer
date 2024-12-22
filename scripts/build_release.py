import os
import platform

SYS = platform.system()
CWD = os.getcwd()
last_token = CWD.split('\\')[-1]

MODE:str = "Release"
slnFile:str = ""

if last_token == "scripts":
    os.chdir("..")
    
for file in os.listdir("."):
    if file.endswith(".sln"):
        slnFile = file

if SYS == "Windows":
    os.system(f"msbuild .\{slnFile} /p:Configuration={MODE}")
elif SYS =="Linux":
    os.system(f"make config={MODE}")