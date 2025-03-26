/*
3 variations of the running light effect
Uncomment part by part to try 
*/


/*
 1. Standard Running Light (One-way ON → OFF)
Each LED turns on one by one from left to right, then turns off in the same order.
*/

int pin_list[4] = {13, 12, 14, 27};
int size = sizeof(pin_list) / sizeof(pin_list[0]);

void setup() {
  for (int i = 0; i < size; i++) {
    pinMode(pin_list[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < size; i++) {
    digitalWrite(pin_list[i], HIGH);
    delay(50);
  }

  for (int i = 0; i < size; i++) {
    digitalWrite(pin_list[i], LOW);
    delay(50);
  }
}

/*
2. Back-and-Forth Running Light (ON → ← OFF)

Now we make the LEDs light up from left to right and then back from right to left, like a wave.
*/

// int pin_list[4] = {13, 12, 14, 27};
// int size = sizeof(pin_list) / sizeof(pin_list[0]);

// void setup() {
//   for (int i = 0; i < size; i++) {
//     pinMode(pin_list[i], OUTPUT);  // Initialize all LEDs as OUTPUT
//   }
// }

// void loop() {
//   // Turn on LEDs from left to right
//   for (int i = 0; i < size; i++) {
//     digitalWrite(pin_list[i], HIGH);
//     delay(100);
//   }

//   // Then turn them off from right to left (reverse)
//   for (int i = size - 1; i >= 0; i--) {
//     digitalWrite(pin_list[i], LOW);
//     delay(100);
//   }
// }

/*
3. Shifting Light (Single LED “Moving”)

This version creates a **“moving dot”** effect. Only one LED is on at any time, giving a clean shifting illusion.
*/


// int pin_list[4] = {13, 12, 14, 27};
// int size = sizeof(pin_list) / sizeof(pin_list[0]);

// void setup() {
//   // Set all pins as OUTPUT
//   for (int i = 0; i < size; i++) {
//     pinMode(pin_list[i], OUTPUT);
//   }
// }

// void loop() {
//   for (int i = 0; i < size; i++) {
//     // Turn on the current LED
//     digitalWrite(pin_list[i], HIGH);

//     // Turn off the previous LED
//     if (i > 0) {
//       digitalWrite(pin_list[i - 1], LOW);
//     } else {
//       // If it's the first LED, turn off the last one to complete the loop
//       digitalWrite(pin_list[size - 1], LOW);
//     }

//     delay(250);  // Slower speed to visualize movement
//   }
// }