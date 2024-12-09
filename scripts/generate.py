import platform
import os

def generate_project():
    SYS = platform.system()
    
    if SYS == "Windows":
        os.system("premake5.exe vs2022")
        
    elif SYS == "Linux":
        os.system("premake5 gmake2")
    
    return
    

if __name__ == "__main__":
    CWD:str = os.getcwd()
    last_token = CWD.split('\\')[-1]

    if last_token == "Scripts":
        os.chdir("..")
    generate_project()
    