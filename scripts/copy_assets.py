import argparse as ap
import os
import platform
import sys
import shutil

from typing import List

DIRS: List[str] = [
    "models",
    "shaders",
    "textures"
]

SYS:str = platform.system()
CWD:str = os.getcwd()
last_token:str = CWD.split('\\')[-1]

if __name__ == "__main__":
    if last_token == "scripts":
        os.chdir("..")
    
    parser = ap.ArgumentParser(
        prog="Asset Copy",
        description="Copies assets in the correct place for the built application to use."
    )
    parser.add_argument('-b', '--build', help="The build configuration in relation to the project!")
    args = parser.parse_args()
    
    mode:str = ""
    
    if (len(sys.argv) > 1):
        mode = args.build
    else:
        mode = str(input("Choose build config (Debug, Release, Shipping): ")).lower().capitalize()
    
    BUILD_DIR:str = ""
    if mode == "Shipping":
        BUILD_DIR = f"./build/{mode}-{SYS.lower()}-x86_64/"
    else:
        BUILD_DIR = f"./build/"
        
    print("Copying assets!")
    for dir in DIRS:
        shutil.copytree(f"./{dir}", BUILD_DIR + dir)

    print("Assets copied!")
        
    
    exit(0)