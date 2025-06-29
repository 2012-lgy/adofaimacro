# Disclaimers
**For entertainment purposes only, please do not use it for forge achievements (including but not limited to competitions, breaking levels). If a video using it is published, please indicate it in the video, title, or introduction.**
# Download
Because it requires the use of the **"Windows. h"** header library in **C++** for key clicking, so **Windows Defender** will consider it a malware as a normal phenomenon. Please manually add it to the whitelist.
# File path form
Please use **single** backslash to separate file path.  
The file name **must** include a suffix.  
The file name can include quotes.

For example:  
  `C:\Users\Administrator\Documents\main.adofai` is **legal**.  
  `"C:\Users\Administrator\Documents\main.adofai"` is **legal**.  
  `C:\\Users\\Administrator\\Documents\\main.adofai` is **illegal**.  
  `C:\Users\Administrator\Documents\main` is **illegal**.
# Update log
Ver 1.0.1  
* Fixed the issue where twirl delay 2 tiles after the mid-spin.

Ver 1.0.2
* Fixed the issue of detecting the Enter key.

Ver 1.1.0
* Changed the form of the file path.

Ver 1.1.1  
* Fixed the  issue where event "setBPM" delaying 2 tiles after the mid-spin.

Ver 1.2.0  
* Added event "Multiplanets" of DLC in it.

Ver 1.2.1  
* Fixed event "Hold".

Ver 1.2.2  
* Fixed the issue where event "multiplanet" would be disabled after mid-spin rotation.

Ver 1.2.3  
* Fixed the issue where reading failed when the file path includes spaces.

Ver 1.3.0  
* Changed preparation mechanism.

Ver 1.4.0  
* Added specific information, including BPM, delta etc.

Ver 1.5.0  
* Fixed the issue of Multiplanet.
* **(Fixed at Ver 1.6.0)** Known issue: Will not press the button at the wrong time (caused by a hold event after midspin)

Ver 1.6.0
* Fixed the **known issue** with **Ver 1.5.0**

Ver 1.6.1
* Fixed issues caused by optimization.
