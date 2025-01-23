# Windows Arduino Leonardo Deadman's Switch

This project was tested with an **Arduino Leonardo** to create a PowerShell script that locks a Windows workstation when the Arduino is disconnected. The Powershell (ps1) script is generated by the Arduino.
This project should work with any Arduino HID that can run the [Keyboard.h library](https://docs.arduino.cc/libraries/keyboard/#Compatibility), but you must modify the line in the code that looks for names like "**Leonardo**".  
This Arduino script will create and save a PowerShell script to detect the Arduino's disconnection. The script is saved into `C:/Users/Public`, and when the PowerShell script is triggered (by the Arduino Leonardo's disconnection), it will:
- Lock the computer.
- Self-destruct (delete the `.ps1` script from the system).

## Features

- Automatically generates a PowerShell script on the target machine.
- Monitors the connection status of the Arduino Leonardo in the background.
- Locks the workstation when the Arduino Leonardo is disconnected.
- Runs the PowerShell script in hidden mode, leaving no visible window or terminal.

## How It Works

1. The Arduino Leonardo emulates a keyboard and types commands to:
   - Create a PowerShell script (`arduino_temp.ps1`) in the `C:\Users\Public` directory.
   - Write the logic to monitor the Arduino Leonardo's connection status.
   - Execute the PowerShell script in hidden mode.

2. The PowerShell script:
   - Detects the Arduino Leonardo by its `FriendlyName` and `Status` (`OK`), to then grab its `InstanceId`.
   - Continuously monitors the device's connection status in the background.
   - Locks the workstation when the device is disconnected.

## Prerequisites

- **Arduino Leonardo** (or any Arduino with keyboard emulation capabilities).
- Windows PC.
- Arduino IDE with the `Keyboard.h` library pre-installed (included by default).

## Setup Instructions

1. Clone this repository or copy the script to your local environment.

2. Open the Arduino IDE and paste the `sketch.ino` file.

3. Upload the sketch to your Arduino Leonardo:
   - Connect the Arduino Leonardo to your PC.
   - Select the correct **board** and **port** in the Arduino IDE.
   - Click the **Upload** button.

4. Once uploaded, the Arduino will:
   - Create the PowerShell script (`arduino_temp.ps1`) on the target machine.
   - Execute it silently in the background.

## PowerShell Script Details

Below is the generated PowerShell script (`arduino_temp.ps1`):

```powershell
$ArduinoDevice = Get-PnpDevice | Where-Object { $_.FriendlyName -like '*Leonardo*' -and $_.Status -eq 'OK' }
if ($ArduinoDevice -ne $null) {
    $DeviceID = $ArduinoDevice.InstanceId;
    while ($true) {
        $USBDevices = Get-PnpDevice | Where-Object { $_.InstanceId -eq $DeviceID }
        if ($USBDevices -eq $null -or $USBDevices.Present -eq $false) {
            rundll32.exe user32.dll, LockWorkStation;
            Remove-Item -Path C:\Users\Public\arduino_temp.ps1 -Force;
            break;
        }
        Start-Sleep -Seconds 1;
    }
} else {
    Write-Output "Arduino Leonardo with Status 'OK' not found. Exiting script.";
}
