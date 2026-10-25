## Name

Hello I'm rottango!

## Description

This project tackles the _Master Thesis_ topic: **"Relative localization system for moving UGVs"**.

_NOTE: UGV = Unmanned Ground Vehicle_

The project has the following tasks I have to fulfill in order to consider the project a success:

1. The analysis of existing relative localization systems for UGVs.
2. Development of a concept for a relative localization sysfer for UGVs.
3. Implementation of the system's operation algorithm in the selected programming language **(C++)**.
4. The analysis of potential cyberthreats to the relative localization system.
5. The test of the system's performance using measurment data from sensors.
6. Create a summary and final conclusions

## Badges

## Visuals

## Instalation

## Android Studio, Device Manager, Bumble (not the dating app)

In order to use MDEK1001 (DWM1001C) with the DRTLS_Manager, you **need** to have an Android Device. The app was made for Android 6.0 / 7.0 (around api 24). I do not have such a device, therefore I am using Android Studio Device Manager to use that app. BUT ROTTANGO I HEAR YOU ASK, does Android studio (by default) use your laptops/computer/SBC "hardware" bluetooth? **NO**. It ?simulates? its own virutal bluetooth?. Anyways, the solution is [bumble](https://google.github.io/bumble/platforms/android.html). Using it, we can create, how I understand, a bridge between the emulator and the physcial hardware. MOREOVER, Android studio doesn't support bluetooth on emulated devices bellow API 31. ask me how I know. It seems to me right now - 20.10.2026 - that The DRTLS works on API 34, certainly i has been downloaded and installed and run by me, however i have not yet connected it to UWBs, so i will update this later. Anyways, running older software on new APIs seem to work to some extend, of course, security is an issue, but lets just quietly and knowingly skip that, becase i am NOT developing an andorid app to work with uwb, thats hella to much work.

This are the commands that - after downloading neccesary packages - run the emulated device with bluetooth on.

```
sudo systemctl stop bluetooth.service
sudo hciconfig hci0 down
pgrep -af '[b]umble-hci-bridge'

sudo env BUMBLE_LOGLEVEL=DEBUG \
  ~/bumble-test/venv/bin/bumble-hci-bridge \
  android-netsim:_:8877,mode=controller \
  hci-socket:0
```

Open another terminal and type this command:

```
~/Android/Sdk/emulator/emulator -avd Medium_Phone_API_37.0 -packet-streamer-endpoint localhost:8877 -no-snapshot-load
```

Phone's bluetooth address should change if it worked

## Usage

## Support

## Roadmap

- Doxygen comments on develop. - Anticipate a lot of modification on other branches - they are not worth documenting
- Physical Hardware Configuration and basic tests. - Not yet relevant to the Master Thesis, but just a check if the hardware works at its core.
  - **PRIORITY**: The current objective is to:
    - Create a c++ program that interacts with the API of the UWB, as described by: DWM1001-API-Guide.pdf form Decawave Ltd, it has to:
      - **Send commands**
      - **Recieve measurements**
      - Recieve the status of the device
      - **Stores that information in containers of adequate type for all the information**
      - Gives the ability to access all measuerements that the user wants, so he can later calculate his own formulas
      - Provides and ok UI
- Code for getting the data off the UWB Device for processing.
- Configuration of the devices for the communication between two nodes such so they satisfy the tasks. (They localize each other).
- Code for processing of the raw data, such so i calculate the atan2 (the relative bearing between nodes).
- Scripts for automating the configuration of the devices to shorten the time between non-operational to operational.

## Contributing

## Authors and acknowledgment

## License

## Project status
