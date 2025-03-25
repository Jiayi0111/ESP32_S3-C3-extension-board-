### **BOOT-KEY Button and GPIO Interrupts on ESP32-S3**  

The ESP32-S3 has **45 GPIO pins**, but many are used for **FLASH and PSRAM**, leaving only **33 available GPIOs** for user applications. This tutorial focuses on **using the BOOT button (connected to GPIO0) to trigger an interrupt** and log the keypress event in the terminal.

---

## **4.1 Running the Example**
To test this feature, follow these steps:

1. **Copy the example project (`01-boot_key`) into your workspace folder** and open it in **VSCode**.
2. **Ignore red underlines in `main.c`** indicating missing headers—these files are in the ESP-IDF directory and won't affect compilation.
3. **Connect the ESP32-S3 development board** to your PC.
4. In **VSCode**, select:
   - **Serial port** (e.g., COM19)
   - **Target chip:** `ESP32-S3`
   - **Flash method:** `UART`
5. **Click the "One-Click Build & Flash" button** to compile, flash, and open the serial terminal.
6. **Press the BOOT button** to see log output:

```
I (305) main_task: Calling app_main()
I (305) gpio: GPIO[0]| InputEn: 1| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:2
I (315) main_task: Returned from app_main()
GPIO[0] intr, val: 0
GPIO[0] intr, val: 0
GPIO[0] intr, val: 0
GPIO[0] intr, val: 0
```

This confirms that **GPIO0 detects button presses** and correctly triggers an interrupt.

---

## **4.2 Code Explanation**
This example is simple, consisting of just **one `main.c` file** with about **40 lines of code**.

### **📌 `app_main()` Function**
This is the **entry point** of the ESP32 program.

```c
void app_main(void)
{
    gpio_config_t io0_conf = {
        .intr_type = GPIO_INTR_NEGEDGE, // Interrupt on falling edge
        .mode = GPIO_MODE_INPUT, // Set as input mode
        .pin_bit_mask = 1<<GPIO_NUM_0, // Select GPIO0
        .pull_down_en = 0, // Disable internal pull-down
        .pull_up_en = 1 // Enable internal pull-up
    };
    gpio_config(&io0_conf); // Configure GPIO0

    // Create a queue to handle GPIO events
    gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));
    // Start GPIO task
    xTaskCreate(gpio_task_example, "gpio_task_example", 2048, NULL, 10, NULL);
    // Install GPIO ISR service
    gpio_install_isr_service(0);
    // Attach interrupt handler to GPIO0
    gpio_isr_handler_add(GPIO_NUM_0, gpio_isr_handler, (void*) GPIO_NUM_0);
}
```
### **📌 Code Breakdown**
- **Lines 3-9:** Configure GPIO0 with:
  - **Interrupt on falling edge** (`GPIO_INTR_NEGEDGE`).
  - **Input mode** (`GPIO_MODE_INPUT`).
  - **Internal pull-up enabled** (`pull_up_en = 1`).
- **Line 11:** Apply the GPIO settings.
- **Line 14:** Create a [*queue*](#-queue-handle-gpio_evt_queue) to store GPIO events.
- **Line 16:** Start the [*GPIO task*](#-gpio-task-gpio_task_example).
- **Line 18:** Install a [*GPIO interrupt service*](#-interrupt-service-routine-isr).
- **Line 20:** Attach the **interrupt handler** to GPIO0. 

### 📌 Queue handle (`gpio_evt_queue`)
`gpio_evt_queue` is a queue handle (a pointer to a queue) used to store GPIO interrupt events in FreeRTOS.
- A queue in FreeRTOS is a **data structure** that allows **tasks and ISRs (interrupts) to communicate** asynchronously.0
    - **ISRs (interrupt service routines)** cannot directly interact with tasks because they run in a separate execution context.
    - Instead, **ISRs send data to queues**, and tasks read data from queues.

`gpio_evt_queue`  is declared as a **global variable** in `main.c`:
```c
static QueueHandle_t gpio_evt_queue = NULL;
```
- `QueueHandle_t` is a **pointer** to a queue.
- **Initially set to NULL**, meaning the queue **is not created yet**.

Inside `app_main()`, the queue is **initialized** using `xQueueCreate()`:
```c
gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));
```
- **First argument (`10`)** → Queue can hold **up to 10 messages**.
- **Second argument (`sizeof(uint32_t)`)** → Each message is **a 32-bit integer** (the GPIO number that triggered the interrupt).



### 📌 GPIO Task (`gpio_task_example`)
The main function `(app_main)` creates a FreeRTOS task `(gpio_task_example)`.
```c
static void gpio_task_example(void* arg)
{
    uint32_t io_num;
    for(;;) {
        if(xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY)) {  // Wait for an event
            printf("GPIO[%"PRIu32"] intr, val: %d\n", io_num, gpio_get_level(io_num));
        }
    }
}
```
- The task enters a `for(;;)` loop, making it run **indefinitely**
- Waits for **an event in the queue** (`xQueueReceive`)
    - **If the queue has data**, it reads the **GPIO number** (`0`).
    - **If the queue is empty**, it remains in a waiting state (`portMAX_DELAY` makes it wait forever).
- **Prints GPIO status** when the button is pressed.
    - It prints the GPIO number and its current level. 
    - The function gpio_get_level(io_num) reads the GPIO0 state (high or low)
    - 

### 📌 Interrupt Service Routine (`ISR`)
```c
static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    uint32_t gpio_num = (uint32_t) arg;  // Get the GPIO number
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL); // Send event to queue
}
```
- **This function runs when GPIO0 detects a button press**.
- **Sends an event to the queue** (`gpio_evt_queue`).
- Runs in **IRAM (Interrupt RAM)** for **low latency**.



### 📌 gpio_isr_handler_add
```c
gpio_isr_handler_add(GPIO_NUM_0, gpio_isr_handler, (void*) GPIO_NUM_0);
```
- First Parameter (`GPIO_NUM_0`) tells the ESP32 which pin should trigger the interrupt. `GPIO0` will generate an interrupt when triggered.
- Second Parameter (`gpio_isr_handler`) tells which function handles the interrupt. `gpio_isr_handler` is the function name that will execute when an interrupt occurs.
- Third Parameter `((void*) GPIO_NUM_0)` pass parameter for ISR handler. Here, we pass `GPIO_NUM_0` as a parameter so the ISR knows which GPIO triggered the interrupt.
You may find definition in \esp\v5.1.5\esp-idf\components\driver\gpio\include\driver\gpio.h
```c
/**
  * @brief Add ISR handler for the corresponding GPIO pin.
  *
  * Call this function after using gpio_install_isr_service() to
  * install the driver's GPIO ISR handler service.
  *
  * The pin ISR handlers no longer need to be declared with IRAM_ATTR,
  * unless you pass the ESP_INTR_FLAG_IRAM flag when allocating the
  * ISR in gpio_install_isr_service().
  *
  * This ISR handler will be called from an ISR. So there is a stack
  * size limit (configurable as "ISR stack size" in menuconfig). This
  * limit is smaller compared to a global GPIO interrupt handler due
  * to the additional level of indirection.
  *
  * @param gpio_num GPIO number
  * @param isr_handler ISR handler function for the corresponding GPIO number.
  * @param args parameter for ISR handler.
  *
  * @return
  *     - ESP_OK Success
  *     - ESP_ERR_INVALID_STATE Wrong state, the ISR service has not been initialized.
  *     - ESP_ERR_INVALID_ARG Parameter error
  */
esp_err_t gpio_isr_handler_add(gpio_num_t gpio_num, gpio_isr_t isr_handler, void *args);
```
### **📌 Required Header Files**
```c
#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
```
- `stdio.h` → Required for `printf()`
- `inttypes.h` → Defines `"PRIu32"` (formatting for `uint32_t` values).
- `FreeRTOS.h`, `task.h`, `queue.h` → FreeRTOS components.
- `gpio.h` → ESP32 GPIO driver.

---

## **4.3 How the Example Was Created**
This example was based on **ESP-IDF's sample_project**.

📂 **Steps to Create the Project:**
1. **Copy** ESP-IDF’s `examples/get-started/sample_project/`.
2. Rename it to `01-boot_key/`.
3. Open it in **VSCode**.
4. Modify **CMakeLists.txt**:
```cmake
project(boot_key)
```
5. Open **`main.c`** and start writing the GPIO interrupt code.

---

## **4.4 Creating a Custom SDK Configuration (`sdkconfig.defaults`)**
After modifying the project, save the **menuconfig settings** so future builds will auto-load them.

1. Open a **Command Terminal** (not the Serial Monitor).
2. Run:
   ```sh
   idf.py save-defconfig
   ```
3. This generates `sdkconfig.defaults`.

Next time you open the project, **menuconfig will automatically load your settings**, making it easier to maintain.

---

### **🚀 Summary**
- **GPIO0 is configured as an interrupt pin**.
- **A queue and FreeRTOS task handle GPIO events**.
- **When BOOT is pressed**, the interrupt logs the keypress.
- **Created using ESP-IDF sample_project & generic_gpio**.
- **`sdkconfig.defaults` saves menuconfig settings**.

Now, you can expand this by **adding more GPIO inputs or outputs**! Let me know if you have questions! 🚀