## **Code Breakdown and Explanation**
### **1. Header Files**
```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
```
- Includes standard C libraries (`stdio.h`, `string.h`, `stdlib.h`, `inttypes.h`).
- Includes **FreeRTOS** headers for **task scheduling** and **queue handling**.
- Includes **ESP-IDF GPIO driver** for GPIO control.

---

### **2. GPIO Pin Configuration**
#### **Output Pins**
```c
#define GPIO_OUTPUT_IO_0    CONFIG_GPIO_OUTPUT_0
#define GPIO_OUTPUT_IO_1    CONFIG_GPIO_OUTPUT_1
#define GPIO_OUTPUT_PIN_SEL  ((1ULL<<GPIO_OUTPUT_IO_0) | (1ULL<<GPIO_OUTPUT_IO_1))
```
- Defines **two output GPIO pins** (e.g., `GPIO18` and `GPIO19`).
- Uses a **bitmask** to define the output pins.

#### **Input Pins**
```c
#define GPIO_INPUT_IO_0     CONFIG_GPIO_INPUT_0
#define GPIO_INPUT_IO_1     CONFIG_GPIO_INPUT_1
#define GPIO_INPUT_PIN_SEL  ((1ULL<<GPIO_INPUT_IO_0) | (1ULL<<GPIO_INPUT_IO_1))
```
- Defines **two input GPIO pins** (e.g., `GPIO4` and `GPIO5`).
- Uses a **bitmask** to define input pins.

#### **Interrupt Flag**
```c
#define ESP_INTR_FLAG_DEFAULT 0
```
- Sets the **interrupt flag** to **0** (default settings).

---

### **3. GPIO Interrupt Handling**
#### **Interrupt Service Routine (ISR)**
```c
static QueueHandle_t gpio_evt_queue = NULL;

static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    uint32_t gpio_num = (uint32_t) arg;
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}
```
- `gpio_evt_queue` is a **queue** for handling GPIO events.
- `gpio_isr_handler()` is an **Interrupt Service Routine (ISR)** that is executed when an interrupt occurs on a GPIO pin.
- It **sends the GPIO number** to a queue (`xQueueSendFromISR`) so the main program can process the event **outside of the ISR**.

#### **Task to Handle GPIO Events**
```c
static void gpio_task_example(void* arg)
{
    uint32_t io_num;
    for(;;) {
        if(xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY)) {
            printf("GPIO[%"PRIu32"] intr, val: %d\n", io_num, gpio_get_level(io_num));
        }
    }
}
```
- A FreeRTOS **task** (`gpio_task_example`) is continuously checking (`xQueueReceive`) for new GPIO events.
- When an event is received, it prints the **GPIO number** and **its current state** (`gpio_get_level(io_num)`).

---

### **4. `app_main()` - Main Function**
#### **Configure GPIOs**
```c
void app_main(void)
{
    gpio_config_t io_conf = {};
```
- Creates a **zero-initialized** GPIO configuration structure.

#### **Configure Output Pins**
```c
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
```
- Disables **interrupts** on output pins.
- Configures **GPIO18 & GPIO19** as **output**.

#### **Configure Input Pins with Interrupts**
```c
    io_conf.intr_type = GPIO_INTR_POSEDGE;
    io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);
```
- Configures **GPIO4 & GPIO5** as **input**.
- Enables **pull-up resistors** (useful when connecting buttons).
- Sets **interrupt on the rising edge** (`GPIO_INTR_POSEDGE`).

```c
    gpio_set_intr_type(GPIO_INPUT_IO_0, GPIO_INTR_ANYEDGE);
```
- Changes **GPIO4** to trigger interrupts on **both rising and falling edges** (`GPIO_INTR_ANYEDGE`).

#### **Create Queue for GPIO Events**
```c
    gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));
    xTaskCreate(gpio_task_example, "gpio_task_example", 2048, NULL, 10, NULL);
```
- Creates a queue (`gpio_evt_queue`) to store GPIO events.
- Creates a **FreeRTOS task** (`gpio_task_example`) to process GPIO events.

#### **Install Interrupt Service & Attach ISR**
```c
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
    gpio_isr_handler_add(GPIO_INPUT_IO_0, gpio_isr_handler, (void*) GPIO_INPUT_IO_0);
    gpio_isr_handler_add(GPIO_INPUT_IO_1, gpio_isr_handler, (void*) GPIO_INPUT_IO_1);
```
- Installs the GPIO **interrupt service**.
- Attaches the ISR (`gpio_isr_handler()`) to `GPIO4` and `GPIO5`.

#### **Remove & Re-add ISR Handler**
```c
    gpio_isr_handler_remove(GPIO_INPUT_IO_0);
    gpio_isr_handler_add(GPIO_INPUT_IO_0, gpio_isr_handler, (void*) GPIO_INPUT_IO_0);
```
- Removes and **re-adds** the ISR for **GPIO4**.

#### **Print Minimum Free Heap Size**
```c
    printf("Minimum free heap size: %"PRIu32" bytes\n", esp_get_minimum_free_heap_size());
```
- Prints **minimum available heap memory**.

#### **Toggle Output GPIOs in a Loop**
```c
    int cnt = 0;
    while(1) {
        printf("cnt: %d\n", cnt++);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(GPIO_OUTPUT_IO_0, cnt % 2);
        gpio_set_level(GPIO_OUTPUT_IO_1, cnt % 2);
    }
```
- A **loop** that:
  - Prints a counter.
  - **Waits for 1 second** (`vTaskDelay(1000 / portTICK_PERIOD_MS)`).
  - Toggles **GPIO18 & GPIO19**.

---

## **Summary of Key Features**
✅ **Configures GPIO18 & GPIO19 as output** (to generate signals).  
✅ **Configures GPIO4 & GPIO5 as input with interrupts** (to detect changes).  
✅ **Uses an interrupt handler (`gpio_isr_handler()`)** to process GPIO changes.  
✅ **Uses a queue (`gpio_evt_queue`)** to communicate between ISR and task.  
✅ **Creates a FreeRTOS task (`gpio_task_example()`)** to handle GPIO events.  
✅ **Toggles GPIO18 & GPIO19 in a loop**, generating a **test signal**.  

---

## **How to Use This Code**
1. **Wire connections:**
   - Connect `GPIO18` to `GPIO4`
   - Connect `GPIO19` to `GPIO5`
   - This allows generated pulses on GPIO18/19 to trigger GPIO4/5 interrupts.

2. **Run the Code:**
   - The program will print:
     ```
     cnt: 0
     GPIO[4] intr, val: 1
     cnt: 1
     GPIO[4] intr, val: 0
     ```
   - This shows **GPIO interrupts** are being triggered as expected.

---

### **Possible Applications**
- Button press detection
- Sensor event monitoring
- Low-power event handling using interrupts

This is a great **starter template** for handling **GPIOs with interrupts** on ESP32! 🚀