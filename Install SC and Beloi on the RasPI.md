#Installing SC and Beloi on the Raspberry Pi

1. Install SuperCollider following the tutorial from: ```http://supercollider.github.io/development/building-raspberrypi.html```
2. Locate the user application folder:
	1. Start sclang ```sclang```
	2. Execute the following line to get the userAppSupportDir path```sc3>> Platform.userAppSupportDir```
	3. This will return the path ```/home/pi/.local/share/SuperCollider```

3. In the userAppSupportDirr we will have to put the extension that we need tiny-sc and the beloi library. To be easyer to mantain the librarys we will clone them in ```/home/pi/Dev``` and in  ```/home/pi/.local/share/SuperCollider/Extensions``` we will just make simbolic links.
	1. ```mkdir Dev && cd Dev```
	2. ```git clone https://github.com/iani/tiny-sc```
	3. ```git clone https://github.com/iani/weaving-voices-engine```
	4. ```cd /home/pi/.local/share/SuperCollider && mkdir Extensions
	5. ```sudo ln -s ~/Dev/tiny-sc ~/.local/share/SuperCollider/Extensions/```
	6. ```sudo ln -s ~/Dev/weaving-voices-engine/scWeavingVoices/ ~/.local/share/SuperCollider/Extensions/```	
	