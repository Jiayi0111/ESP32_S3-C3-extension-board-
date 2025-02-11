## Setting Up Development Environment

The ESP-IDF development environment can be installed on Windows, Linux, and macOS. The official ESP-IDF Programming Guide by Espressif provides detailed installation instructions for each operating system. If you're interested in the step-by-step guide, you can check out the official documentation. However, if you prefer a quicker setup, continue reading below.

The ESP-IDF Programming Guide is an online document available at:
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html#ide

For most embedded engineers, Windows is the primary operating system used. If you wish to develop on Linux while using a Windows machine, you will need to install a virtual machine (VM), set up a Linux system within it, and then install ESP-IDF in the Linux environment. This process often introduces various unexpected issues, which may discourage many users.

Therefore, we recommend developing directly on Windows.

There are two free software options available for development: Eclipse and Visual Studio Code (VSCode). This tutorial will use VSCode, covering the entire workflow including code editing, compiling, flashing, and debugging.

To develop using VSCode, you only need to install the ESP-IDF plugin within VSCode. Once installed, you can seamlessly edit, compile, flash, and debug your ESP32 projects directly within the VSCode environment.


### install VSCode 
VSCode (Visual Studio Code) is a powerful development tool, and many developers may have already used it for other microcontroller projects. If you haven’t used it before, simply visit the official VSCode download page https://code.visualstudio.com/, locate the download button, and click to start downloading.
![image](https://github.com/user-attachments/assets/2e732534-ed6d-4efd-aba3-3c0cfe7417dc)
Once the download is complete, double-click the installer and follow the instructions to complete the installation.

### Install & configure the Espressif IDF Plugin
Search for ESP-IDF in the VSCode extensions marketplace, find the Espressif IDF plugin, and click Install.
![image](https://github.com/user-attachments/assets/d07893e1-377b-4596-8cb6-0001de6d5717)

During the installation of the ESP-IDF plugin, the C/C++ extension will be installed automatically. Once the installation is complete, you can check the list of installed extensions by clearing the search bar in the Extensions tab, as shown in the image below.

![image](https://github.com/user-attachments/assets/18971115-db82-4295-adcc-a3b363491e89)

If the C/C++ extension is not installed automatically, you can manually search for C/C++ in the extensions marketplace and install it separately.

After installing the ESP-IDF plugin, you need to configure it before use. Click on the ESP-IDF plugin icon in the VSCode sidebar, then select Configure ESP-IDF Extension.
Next, click on "EXPRESS", which means a quick installation process.
![image](https://github.com/user-attachments/assets/c1c5903c-e6c2-476c-a18b-e8d37c38b955)

After selecting **"EXPRESS"** for the quick installation, you need to complete four configuration options:  

1. **Select Download Server**  
   - Choose **GitHub** as the download source.  
   - If you are in China, select **Espressif** for better download speed.  

2. **Select the ESP-IDF Version**  
   - It is recommended to install **ESP-IDF v5.1.5**, as it is fully compatible with our demo projects.  

3. **Select the Installation Directory for ESP-IDF**  
   - Choose a folder where ESP-IDF will be installed.  

4. **Select the Installation Directory for IDF_TOOLS**  
   - Choose a separate folder for IDF_TOOLS.  
   - **Important:** The **ESP-IDF** and **IDF_TOOLS** folders **must be different**, or the installation will fail.  
   - For example, in the image below, **ESP-IDF** is installed in the **esp** folder, while **IDF_TOOLS** is installed in **esp\515_tools**.
![image](https://github.com/user-attachments/assets/332144f0-5235-46e9-9e19-d3d8a65bcbe7)

The installation process typically takes **10 to 30 minutes**, so please be patient.  
If the installation fails, you can seek help by posting your issue on our **forum** for support.
![image](https://github.com/user-attachments/assets/3e494344-c951-4267-9f91-28e3cc04de38)


## Next

- [2.1 Installing Multiple Versions of ESP‐IDF](https://github.com/Jiayi0111/ESP32_S3-C3-extension-board-/wiki/2.1-Installing-Multiple-Versions-of-ESP%E2%80%90IDF)
- [3. Hello_world](https://github.com/Jiayi0111/ESP32_S3-C3-extension-board-/wiki/3.-Hello_world)
