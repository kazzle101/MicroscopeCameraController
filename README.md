# Microscope Camera Controller
For Controlling an AmScope AF102 Auto-Focusing Microscope camera via USB to replace the Mouse.

The AmScope AF102 is an auto-focusing camera that mounts onto the camera port of their binocular microscope, it outputs 1080p video over HDMI and provides on-screen controls for settings like focus, exposure and cross-hairs by way of a USB mouse. I found using the mouse to be quite clumsy, what with the lack of desk space and everything.

I built this device to attach to the side of the camera for providing a convienient method of control. It uses I2C to run a small Adafruit OLED screen as well as an MCP23017 GPIO chip for the rotary switch, four buttons and assorted LED's. I have written this software in the Arduino IDE for use with a Teensy3, but it should work with any Arduino board that provides USB 
HID control (Leonardo?).

It is mainly used for setting the focus - Click Focus and switching between Auto-Focus and Manual Focus. The rotary switch
allows scrolling through various options, and when in manual focus mode to set where you want to focus. The buttons act 
as shortcuts while the small OLED screen is used to show where you are at.

A diagram showing the connections for the MCP23017: 
<img src="https://github.com/kazzle101/MicroscopeCameraController/blob/master/microscope_controller_s.png">
https://github.com/kazzle101/MicroscopeCameraController/blob/master/microscope_controller_s.png

I have made a video showing its use: https://www.youtube.com/watch?v=tAYUrnRACeo



