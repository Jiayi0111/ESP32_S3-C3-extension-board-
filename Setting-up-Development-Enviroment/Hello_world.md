### Getting Started with ESP32 Development in VSCode  

To familiarize ourselves with the **ESP32 development workflow** in VSCode, we will go through the **Hello World** example provided by ESP-IDF.  

🚀 **Beginners must read this section**—it covers:  
- How to **write** code  
- How to **compile** code  
- How to **flash** code to the ESP32  

This guide will also introduce **the ESP-IDF plugin interface** in VSCode and explain the functions of its various icons.

---

## 3.1 Preparing the `hello_world` Example  

### 📁 **Creating a Workspace Folder**  
First, create a new folder on your hard drive for this experiment. **Ensure that:**  
✅ The folder path contains **only English characters**  
✅ The folder name **does not contain spaces**  

**Example:**  
I created a folder named **esp32s3** on my **D: drive**, so my workspace path is:  
```plaintext
D:\esp32s3
```

### 📂 **Copying the `hello_world` Example**  
ESP-IDF provides many **example projects**, located in:  
```plaintext
<IDF folder>\examples
```  
The **Hello World** example is under:  
```plaintext
<IDF folder>\examples\get-started\hello_world
```  
Copy the entire `hello_world` folder to your **workspace folder**. After copying, the new path should be:  
```plaintext
D:\esp32s3\hello_world
```

---

## 3.2 **Opening the Project in VSCode**  

### ✅ **Method 1: Manually Copying the Folder**  
If you copied the `hello_world` folder manually, open **VSCode**, then:  
1. Click on **File** → **Open Folder**  
2. Navigate to **...\esp32s3\hello_world**  
3. Click **Select Folder** to open the project  

---

### ✅ **Method 2: Using VSCode to Open the Example**  
Alternatively, you can directly **open the example in VSCode**:  
1. Open **VSCode**  
2. Click on **File** → **Open Folder**  
3. Navigate to **...\esp32s3\hello_world**  
4. Click **Select Folder**  

---

### 🔍 **Exploring the Project Structure**  

Once the project is opened, **expand the folder structure** in VSCode:  
- In the **left panel** (Explorer view), click the `>` symbol next to **main** to expand the folder.  
- You will see the file **hello_world_main.c**.  

📝 Click on **hello_world_main.c** to open it in the **editor window (right side)**.  

This file contains the **ESP32's main program**.  
- The **`app_main`** function inside this file is the **entry point** of the program.  

Before running the project, let’s first **understand the project structure**. 🚀

## 3.3 **Compiling and Flashing the Program**  
In the bottom of VSCode, several configuration options need to be set, as shown in the image below.
![image](https://github.com/user-attachments/assets/c9db1592-5804-45f4-bc4c-0b4ff5ad984c)

### **1️⃣ Selecting the Target Chip**
Click the chip icon to choose the target ESP chip.

![image](https://github.com/user-attachments/assets/4b355a70-cb33-4e91-aaf8-d270b9675fa7)

Then, a list of available ESP chips will appear—select **esp32s3**.
（if you are using ESP32-WROOM-32E 4MB, select **esp32**）
（if you are using ESP32C3 4MB, select **esp32c3**）

### **2️⃣ Selecting the Flashing Method**
choose **ESP-PROG-2**

![image](https://github.com/user-attachments/assets/84131b1f-127f-4af4-8221-10bc36c6050d)

  - This is **USB-to-Serial**, as indicated by the configuration file:  
    ```plaintext
    board/esp32s3-bridge.cfg
    ```
**After selecting the target chip and flashing method**, **wait** for the **progress bar** in the **bottom-right corner** to complete before proceeding.

### **3️⃣ Selecting the Serial Port**  
- Click the **COM icon** to choose the **serial port**.  

![image](https://github.com/user-attachments/assets/dd20ad7c-6e79-47f8-bece-6df1af38d8de)

- **Before selecting the port**, ensure that the **ESP32 development board is connected** to your computer.  
- After clicking, a **list of available serial ports** will appear.  
- Select the one labeled with **ESP32**, for example, **COM6**.  
- **After selection, the microcontroller will restart once** automatically.

### **4️⃣ Understanding the Project Structure**  

After configuration, new **folders and files** will appear in the project directory:

📂 **`.vscode`** → Stores **configuration files** (e.g., `settings.json`).  
📂 **`build`** → Stores **compiled binaries** (this folder takes up the most space after compilation).  
📄 **`sdkconfig`** → Stores **ESP-IDF build settings**.  
📄 **`sdkconfig.old`** → A **backup** of the previous `sdkconfig`.

Inside **`.vscode/settings.json`**, you’ll find key configurations, you may check them before building:

```json
{
    "idf.portWin": "COM19",  // Selected serial port
    "idf.adapterTargetName": "esp32s3",  // Selected ESP chip
    "idf.openOcdConfigs": ["board/esp32s3-bridge.cfg"]  // Flashing method (USB-to-Serial)
}
```

### **5️⃣ One-Click Compilation, Flashing, and Terminal Output**  
🔥 **Click the fire icon**—this is the **"One-Click Build & Flash"** button.  
![image](https://github.com/user-attachments/assets/73863202-b319-4c83-ac6e-f20e8f59177f)

- This **automatically performs** the following actions:  
  ✅ **Compile the code**  
  ✅ **Flash it to the ESP32**  
  ✅ **Open the serial terminal for debugging**  


### **📌 Running the Program and Viewing the Output**  
After flashing, the **terminal will open automatically**, displaying messages like:

```plaintext
Hello world!
This is esp32s3 chip with 2 CPU core(s), WiFi/BLE, silicon revision v0.2, 16MB external flash
Minimum free heap size: 390648 bytes
Restarting in 10 seconds...
Restarting in 9 seconds...
Restarting in 8 seconds...
Restarting in 7 seconds...
Restarting in 6 seconds...
Restarting in 5 seconds...
```

🎯 The **ESP32 will restart every 10 seconds** and print the message again.

---

### **📌 How to Exit the Serial Terminal**  
To **close the terminal**, use the shortcut:  
```plaintext
Ctrl + ]
```



## Next
[Understanding Project Structure](BasicProjectStructure.md)
[Using Flash Download Tool to Flash](UsingFlashDownloadTooltoFlash.md)