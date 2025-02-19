# ESP32S3/C3 extension board

[Go to part 1.0 - Setting Up Development Environment](Setting-up-Development-Enviroment/Setting-Up-Development-Environment.md)
 -  [part 1.0.1 Installing Multiple Versions of ESP‐IDF](Setting-up-Development-Enviroment/InstallingMultipleVersionsofESP‐IDF.md)

[Go to part 1.1 - Hello_world (write & compile & flash)](Setting-up-Development-Enviroment/Hello_world.md)
 - [part 1.1.1 Understanding Basic Project Structure](Setting-up-Development-Enviroment/BasicProjectStructure.md)



### **4️⃣ How Does `gpio_evt_queue` Work?**
1. **Interrupt occurs** when the BOOT button (GPIO0) is pressed.
2. The ISR **sends the GPIO number** (`0`) to the queue:
   ```c
   xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
   ```
3. The **FreeRTOS task (`gpio_task_example`) continuously checks the queue**:
   ```c
   if (xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY)) {
   ```
   - **If the queue has data**, it reads the **GPIO number** (`0`).
   - **If the queue is empty, it waits** (`portMAX_DELAY`).

4. The task then **prints the message**:
   ```c
   printf("GPIO[%"PRIu32"] intr, val: %d\n", io_num, gpio_get_level(io_num));
   ```

