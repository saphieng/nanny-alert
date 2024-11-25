# nanny-alert

This is the source code for an emergency alert system I built for Nan. It allows Nan to easily notify me if she needs assistance using a Particle Electron and a wireless remote for portability around the house.

## Features
The system has the following features:
- Alerts multiple people via email using SendGrid API webhook
- RGB for easy status indication
- Buzzer for audible feedback that alert has been sent
- 3G mobile connection to avoid connection loss during blackout
- LiPo backup and charging so the system stays online during power outage
- Blackout detection that alerts if power outage is detected
- Ability to monitor battery status using Particle Cloud API
- Alert button built into box as well as remote for backup if remote fails
- Press and hole to test system without sending alerts to all users

## Hardware
It was built with the following hardware
- [Particle Electron](https://core-electronics.com.au/electron-3g-kit.html)
- [Photon Battery Shield](https://core-electronics.com.au/sparkfun-photon-battery-shield.html)
- [LiPo Rechargeable Battery](https://core-electronics.com.au/polymer-lithium-ion-battery-2000mah-38459.html)
- [RGB LED](https://core-electronics.com.au/freetronics-8mm-rgb-led-common-cathode-8-pack-suitable-for-4x4x4-rgb-led-cube.html)
- [Switch](https://core-electronics.com.au/spdt-mini-power-switch.html)
- [Jiffy Box](https://www.jaycar.com.au/jiffy-case-imac-blue-ub5/p/HB6004)
- [Buzzer](https://www.jaycar.com.au/mini-piezo-buzzer-3-16v/p/AB3462)
- [Momentary](https://www.jaycar.com.au/red-miniature-pushbutton-spst-momentary-action-125v-1a-rating/p/SP0710)
- [Wireless Relay Kit](https://au.element14.com/rf-solutions/hornet-s1m/remote-control-sys-fm-1-ch-230vac/dp/1753336) 
- [Power Supply](https://core-electronics.com.au/12v-dc-2a-fixed-2-1mm-tip-appliance-plugpack.html)
- [5V Regulator](https://core-electronics.com.au/pololu-5v-5a-step-down-voltage-regulator-d24v50f5.html?utm_source=google_shopping&gclid=CjwKCAiA9qHhBRB2EiwA7poaeCX29ZiiBZVHP_ZPJ9Gr2UQZnmFLVK69j8wON8hODQ4hBC6V8qIDIxoCTMsQAvD_BwE)

**NOTE** The wirless relay link I used was because I already owned it and is actually overkill. If I was building this again I would probably go with this [Long Range Link](https://core-electronics.com.au/2km-long-range-rf-link-kits-w-encoder-and-decoder-seeed-studio.html)

## Video
You can watch a demonstation of the system features here:
[Nanny Alert Video](https://saphi-my.sharepoint.com/personal/cameron_saphi_engineering/_layouts/15/stream.aspx?id=%2Fpersonal%2Fcameron%5Fsaphi%5Fengineering%2FDocuments%2FArchived%2FVideos%2FNanny%20Alert%2EMOV&ga=1&referrer=StreamWebApp%2EWeb&referrerScenario=AddressBarCopied%2Eview%2Ea87907aa%2D85bc%2D47a4%2Da2da%2D0f3a6857869e)
## Compiling your project

When you're ready to compile your project, make sure you have the correct Particle device target selected and run `particle compile <platform>` in the CLI or click the Compile button in the Desktop IDE. The following files in your project folder will be sent to the compile service:

- Everything in the `/src` folder, including your `.ino` application file
- The `project.properties` file for your project
- Any libraries stored under `lib/<libraryname>/src`
