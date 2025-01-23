#include <Keyboard.h>

// Function to type a string
void typeText(const char *text) {
  while (*text) {
    Keyboard.print(*text++);
    delay(50); // Add a small delay to avoid missing characters
  }
}

void setup() {
  // Start the Keyboard library
  Keyboard.begin();
  delay(3000); // Wait for the system to recognize the Arduino

  // Open Command Prompt
  Keyboard.press(KEY_LEFT_GUI); // Press Windows key
  Keyboard.press('r');          // Press R
  delay(200);
  Keyboard.releaseAll();
  delay(500);

  typeText("cmd");
  Keyboard.press(KEY_RETURN); // Press Enter
  Keyboard.releaseAll();
  delay(1000);

  // Overwrite the .ps1 file (or create it if it doesn't exist)
  typeText("echo. > C:\\Users\\Public\\arduino_temp.ps1");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(300);

  // Close the Command Prompt
  typeText("exit");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(300);

  // Open Notepad via Win+R to write the PowerShell script
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  delay(200);
  Keyboard.releaseAll();
  delay(300);

  typeText("notepad C:\\Users\\Public\\arduino_temp.ps1");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(700);

  // Write the updated PowerShell script
  typeText("$ArduinoDevice = Get-PnpDevice | Where-Object { $_.FriendlyName -like '*Leonardo*' -and $_.Status -eq 'OK' }");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(200);

  typeText("if ($ArduinoDevice -ne $null) {");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(200);

  typeText("    $DeviceID = $ArduinoDevice.InstanceId;");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(200);

  typeText("    Write-Output \"Arduino Leonardo found with Status 'OK'. Monitoring connection status...\";");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(200);

  typeText("    while ($true) {");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(200);

  typeText("        $USBDevices = Get-PnpDevice | Where-Object { $_.InstanceId -eq $DeviceID }");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(200);

  typeText("        if ($USBDevices.Present -eq $false) {");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(200);

  typeText("            Write-Output \"Arduino Leonardo disconnected. Triggering lock...\";");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(200);

  typeText("            rundll32.exe user32.dll, LockWorkStation;");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(200);

  typeText("            Remove-Item -Path C:\\Users\\Public\\arduino_temp.ps1 -Force;");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(200);

  typeText("            break;");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(200);

  typeText("        }");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(200);

  typeText("        Start-Sleep -Seconds 1;");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(200);

  typeText("    }");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(200);

  typeText("} else {");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(200);

  typeText("    Write-Output \"Arduino Leonardo with Status 'OK' not found. Exiting script.\";");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(200);

  typeText("}");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(200);

  // Save the PowerShell script in Notepad
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('s');
  delay(200);
  Keyboard.releaseAll();
  delay(500);

  // Close Notepad
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_F4);
  delay(200);
  Keyboard.releaseAll();
  delay(500);

  // Run the PowerShell script in hidden mode via Start-Process
  Keyboard.press(KEY_LEFT_GUI); // Press Windows key
  Keyboard.press('r');          // Press R
  delay(200);
  Keyboard.releaseAll();
  delay(400);

  typeText("powershell -ExecutionPolicy Bypass -Command \"Start-Process -FilePath 'powershell.exe' -ArgumentList '-ExecutionPolicy Bypass -File C:\\Users\\Public\\arduino_temp.ps1' -WindowStyle Hidden\"");
  Keyboard.press(KEY_RETURN); // Press Enter
  Keyboard.releaseAll();

  // End keyboard emulation
  Keyboard.end();
}

void loop() {
  // Do nothing
}
