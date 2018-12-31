# nanny-alert

This is the source code for an emergency alert system I built for Nan. It allows Nan to easily notify me if she needs assistance using a Particle Electron and a wireless remote for portability around the house.

## Features
The system has the following features:
- Alerts multiple people via email using SendGrid API webhook
- RGB for easy status indication
- Buzzer for audible feedback that alert has been sent
- 3G/4G mobile connection to avoid connection loss during blackout
- LiPo backup and charging so the system stays online during power outage
- Blackout detection that alerts if power outage is detected
- Ability to monitor battery status using Particle Cloud API
- Alert button built into box as well as remote for backup if remote fails
- Press and hole to test system without sending alerts to all users

## Video
You can watch a demonstation of the system features here:

## Compiling your project

When you're ready to compile your project, make sure you have the correct Particle device target selected and run `particle compile <platform>` in the CLI or click the Compile button in the Desktop IDE. The following files in your project folder will be sent to the compile service:

- Everything in the `/src` folder, including your `.ino` application file
- The `project.properties` file for your project
- Any libraries stored under `lib/<libraryname>/src`
