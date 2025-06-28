**Bug Report:** `caosh2022@shanghaitech.edu.cn`. Songhui Cao is responsible for maintaining this guide and Longan development kit for CA1 until 20 June, 2025.

**Revision History:**

20240329 First created by Songhui Cao

20250403 Added FAQ.

## Installation Guide

1. Install platformio.

2. Open platformio root directory. Typically, it will reside in `C:\Users\<your user name>\.platformio` and contain **at least** the following files:

   ```
   Mode                 LastWriteTime         Length Name
   ----                 -------------         ------ ----
   d----           2024/3/29    10:28                packages
   d----           2024/3/29    10:26                platforms
   -a---           2024/3/28    18:48            177 appstate.json
   -a---            2023/8/5     0:15            293 homestate.json
   ```

   We will use `<pio root>` to represent platformio root directory from now on.

   If any of the files or folders in `windows-version` already exists in `<pio root>`, first try not to replace the file in `<pio root>` and see if it works. If it does not work, before replacing files in `<pio root>`, remember to create a backup for those files in `<pio root>`.

3. Open `packages` folder in both `windows-version` and `<pio root>`. In `windows-version\packages`, you will see **exactly** the following 5 files:

   ```
   Mode                 LastWriteTime         Length Name
   ----                 -------------         ------ ----
   d----           2024/3/29    10:33                framework-arduino-gd32v
   d----           2024/3/29    10:33                framework-gd32vf103-sdk
   d----           2024/3/29    10:33                tool-gd32vflash
   d----           2024/3/29    10:33                tool-openocd-gd32v
   d----           2024/3/29    10:33                toolchain-gd32v
   ```

   Copy all 5 of them and paste in `<pio root>\packages`. After pasting, you will see **at least** the following files in `<pio root>\packages`:

   ```
   Mode                 LastWriteTime         Length Name
   ----                 -------------         ------ ----
   d----            2023/8/5     0:15                contrib-piohome
   d----           2024/3/29     8:47                framework-arduino-gd32v
   d----           2024/3/29     8:47                framework-gd32vf103-sdk
   d----           2024/3/29     8:47                tool-gd32vflash
   d----           2024/3/29     8:47                tool-openocd-gd32v
   d----           2024/3/29     8:47                toolchain-gd32v
   ```

4. Open `platforms` folder in both `windows-version` and `<pio root>`. In `windows-version\platforms`, you will see **exactly** the following 1 file:

   ```
   Mode                 LastWriteTime         Length Name
   ----                 -------------         ------ ----
   d----           2024/3/29    10:32                gd32v
   ```

   Copy it and paste in `<pio root>\platforms`. After pasting, you will see **at least** the following 1 file in `<pio root>\platforms`:

   ```
   Mode                 LastWriteTime         Length Name
   ----                 -------------         ------ ----
   d----           2024/3/29     9:02                gd32v
   ```

5. Open `windows-version\GD32 MCU Dfu Drivers_v1.0.1.2316`. Install the appropriate driver for your system architecture. If you are using 64-bit operation system, use `x64`. If you are using 32-bit operation system, use `x86`. It is very unlikely that you use `x86`.

6. The folder `windows-version\GD32 MCU Dfu Tool_v3.8.1.5784` contains DFU tool for downloading firmware into your Longan Nano. This folder, as a whole, can be moved anywhere and the DFU tool should work. 

For more on how to use the DFU tool, and platformio, please refer to their documentation and lab instruction. The usage of specific software is out of the scope of this installation guide.

## FAQ

(Revised 20240516) (Windows user only) After installing the DFU driver, the system might crash into a bluescreen when plugging in a Longan Nano. Why does this happen? Is it harmful to my PC? What can I do?

- Why does this happen? Because there is a bug in the DFU driver.
- Is it harmful to my PC? Very unlikely, but possible. All unsaved files may be lost, and Windows cannot guarantee the filesystem's integrity. Though Windows can repair NTFS even if disrupted, we suggest backing up your files (to external block devices) periodically to address this issue.
- What can I do?
  - If you feel uncomfortable with the bluescreen, it is possible to switch back to Linux. We also have confirmed that virtual machine will do for Longan Nano part of CS110/CS110P.
  - If you stick to Windows, I suggest you back up your files (to external block devices) periodically. 
  - My effort to update the driver fails, as all Windows drivers must be signed, so I cannot fix the driver myself. Meanwhile, the update page for the DFU tool appears to be 404, so the official updating procedure also fails. Feel free to email me if anyone can offer help (caosh2022).

