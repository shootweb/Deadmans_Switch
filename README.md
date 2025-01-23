# Deadman's Switch

This project uses an Arduino Leonardo to dynamically identify itself as a USB device on a Windows host, set up a PowerShell script to monitor its connection, and lock the computer when the device is disconnected. The PowerShell script is created and executed automatically by the Arduino via its HID (Human Interface Device) keyboard emulation capabilities.

## Features

- **Dynamic Self-Identification**: The Arduino Leonardo identifies itself on the host using PowerShell, eliminating the need for hardcoded Device IDs.
- **Automatic Setup**: The Arduino creates and executes the PowerShell script without requiring manual configuration on the host.
- **Connection Monitoring**: The PowerShell script continuously monitors the Arduino's connection status.
- **Automatic Lock**: When the Arduino is disconnected, the computer locks itself.
- **Self-Cleanup**: The PowerShell script deletes itself after execution to ensure no residual files remain.

## How It Works

1. **Arduino Sends Keystrokes**:
   - The Arduino uses HID keyboard emulation to open PowerShell on the Windows host and type out commands to create a temporary monitoring script.

2. **Dynamic Device Identification**:
   - The PowerShell script identifies the Arduino Leonardo dynamically by querying its **friendly name** (`Arduino Leonardo`).

3. **Monitoring**:
   - The script continuously checks if the Arduino is still connected. If not, the system locks.

4. **Cleanup**:
   - After locking the computer, the PowerShell script deletes itself.

## Requirements

- **Hardware**:
  - Arduino Leonardo or compatible board with HID capabilities.

- **Software**:
  - Arduino IDE for uploading the sketch.
  - Windows host with PowerShell enabled (default on most modern Windows systems).

## Setup and Usage

### Step 1: Upload the Arduino Code

1. Open the provided Arduino sketch in the Arduino IDE.
2. Connect your Arduino Leonardo to the computer.
3. Select the correct port and board in the Arduino IDE.
4. Upload the sketch to the Arduino.

### Step 2: Connect the Arduino

1. Once the Arduino is connected, it will:
   - Open PowerShell on the Windows host.
   - Dynamically identify itself as a USB device.
   - Create and execute a PowerShell script to monitor its connection.

### Step 3: Disconnect the Arduino

1. When you disconnect the Arduino Leonardo, the PowerShell script will:
   - Detect the disconnection.
   - Lock the computer.
   - Delete itself.

### Step 4: Reconnect to Reset

1. To enable the functionality again, simply reconnect the Arduino Leonardo. The setup process will repeat automatically.

## How the PowerShell Script Works

The Arduino generates the following PowerShell script dynamically:

```powershell
$ArduinoDevice = Get-PnpDevice | Where-Object { $_.FriendlyName -like "*Leonardo*" }
if ($ArduinoDevice) {
    $DeviceID = $ArduinoDevice.InstanceId
    while ($true) {
        $USBDevices = Get-PnpDevice | Where-Object { $_.InstanceId -eq $DeviceID }
        if (-not $USBDevices) {
            rundll32.exe user32.dll, LockWorkStation
            Remove-Item -Path C:\Users\Public\arduino_temp.ps1 -Force
            break
