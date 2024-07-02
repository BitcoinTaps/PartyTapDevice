import shutil
import configparser
import re
import json

project_config = configparser.ConfigParser()
project_config.read("platformio.ini")


firmware_version = project_config.get("common", "firmware_version")
pioenv = 'ESP32_3248S035C'
build_dir = f".pio/build/{pioenv}"
lnbits_dir = "lnbits"
firmware_dir = f"{lnbits_dir}/static/firmware/{pioenv}"
template_dir = f"{lnbits_dir}/templates/partytap"

for filename in ['partitions.bin','bootloader.bin']:
    shutil.copyfile(f"{build_dir}/{filename}",f"{firmware_dir}/{filename}")

shutil.copyfile(f"{build_dir}/firmware.bin",f"{firmware_dir}/firmware.bin")
shutil.copyfile(f"{build_dir}/firmware.bin",f"{firmware_dir}/firmware_BITCOINTAPS.bin")
shutil.copyfile(f"{build_dir}_NONE/firmware.bin",f"{firmware_dir}/firmware_NONE.bin")
shutil.copyfile(f"{build_dir}_BEER/firmware.bin",f"{firmware_dir}/firmware_BEER.bin")
         
# update tasks.py
with open(f"{lnbits_dir}/tasks.py") as file:
    content = file.read()

content = re.sub("\"version\"\: \".*\"",f"\"version\": \"{firmware_version}\"",content)

with open(f"{lnbits_dir}/tasks.py","w") as file:
    file.write(content)


# update manifest
with open(f"{firmware_dir}/manifest.json","r") as file:
        data = json.load(file)
data['version'] = firmware_version
with open(f"{firmware_dir}/manifest.json","w") as file:
    json.dump(data,file,indent=4)

# update version in index.html
with open(f"{template_dir}/index.html","r") as file:
    content = file.read()

content = re.sub("version\: \'.*\',",f"version: \'{firmware_version}\',",content)

with open(f"{template_dir}/index.html","w") as file:
    file.write(content)

    
