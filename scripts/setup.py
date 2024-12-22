import os
import requests
import platform
import zipfile
import tarfile
from io import BytesIO

WIN_URL:str = "https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-windows.zip"
LNX_URL:str = "https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-linux.tar.gz"
PREMAKE_EXE:str = ""

SYS = platform.system()
CWD:str = os.getcwd()

def downloadZIP():
    global WIN_URL
    global PREMAKE_EXE
    
    response = requests.get(WIN_URL)
    if response.status_code == 200:
        print("\033[92mDownload complete!\033[37m")
    else:
        raise Exception("Link is invalid, or unreachable")
    
    zip = zipfile.ZipFile(BytesIO(response.content))
    if PREMAKE_EXE in zip.namelist():
        print("\033[36mExtracting...\033[37m")
        zip.extract(PREMAKE_EXE, path=".")
    else:
        zip.close()
        raise Exception("File not found in archive!")
    
    zip.close()
    print("\033[92mExtraction completed succesfully!\033[37m")
    return

def downloadTARGZ():
    global LNX_URL
    global PREMAKE_EXE
    
    response = requests.get(LNX_URL)
    if response.status_code == 200:
        print("\033[92mDownload complete!\033[37m")
    else:
        raise Exception("Link is invalid, or unreachable")
    
    tar_file = tarfile.open(fileobj=BytesIO(response.content), mode="r:gz")
    if PREMAKE_EXE in tar_file.getnames():
        print("\033[36mExtracting...\033[37m")
        tar_file.extract(PREMAKE_EXE, path=".")
    else:
        tar_file.close()
        raise Exception("File not found in archive!")
    
    tar_file.close()
    print("\033[92mExtraction completed succesfully!\033[37m")
    return

if __name__ == "__main__":

    last_token = CWD.split('\\')[-1]

    if last_token == "scripts":
        os.chdir("..")
        
    if SYS == "Windows":
        PREMAKE_EXE = "premake5.exe"
    elif SYS == "Linux":
        PREMAKE_EXE = "premake5"
    else:
        print("\033[91mYou picked the wrong OS fool!\033[37m")

    if not os.path.isfile(PREMAKE_EXE):
        print("\033[36mStarting to download archive\033[37m")

        if SYS == "Windows":
            print(f"\033[35mDownloading archive from:\n\t {WIN_URL} \033[37m")
            downloadZIP()
        elif SYS == "Linux":
            print(f"\033[35mDownloading archive from:\n\t {LNX_URL}  \033[37m")
            downloadTARGZ()
    else:
        print("\033[33mExecutable seems to already exist! Skipping download.\033[37m")
       
    exit(0)