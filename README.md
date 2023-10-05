# Temperature Activated Fan Controller


# Overview

Temperature controlling is required in many places such as server rooms, houses, industries, etc. Here the Temperature controlled fan will act to the temperature changes.

We are going to do this with a DHT11 temperature and humidity sensor as DHT11 is a efficient & cost-effective sensor.

Temperature-controlled fan will use RISCV. With this, we will be able to change the fan speed in our home or any place according to the room temperature and also display the temperature and fan speed changes on a 16x2 LCD display. 


# Requirements 

The components required for the project are listed below:

```
RISCV  
Temperature Sensor(DHT11 sensor)
DC Fan
9 volt battery
16x2 LCD
Connecting wires
```

# Block Diagram

<img width="652" alt="Screenshot 2023-10-06 at 12 06 46 AM" src="https://github.com/VaibhavTiwari-IIITB/temp_activated_fan_controller/assets/140998525/81e29efd-3b6d-4499-a3b1-07e18deb62f2">


# Code

```
#include <stdio.h>

void readTemperature();
void controlFan(int temperature);

int main() {
    while (1) {
        readTemperature();
    }
    return 0;
}

void readTemperature() {
    int temperature;

    asm (
    "and %0, x30, 1" // Load temperature data into x30
    : "=r"(temperature)
);


    // Print temperature for testing
    printf("Current Temperature: %d°C\n", temperature);

    controlFan(temperature);
}

// Function to control the fan based on the temperature
void controlFan(int temperature) {

    int* FAN_CTRL; 
    int fan_reg;

    // Threshold temperature for fan activation 
    int thresholdTemperature = 30;

    if (temperature > thresholdTemperature) {
        // If temperature is above the threshold, set the fan control register to 1 (fan on)
        fan_reg = 1;
    } else {
        // If temperature is below or equal to the threshold, set the fan control register to 0 (fan off)
        fan_reg = 0;
    }

    asm (
        "str %1, [%0]\n\t" // Store fan_reg value to FAN_CTRL register
        :
        : "r"(FAN_CTRL), "r"(fan_reg)
    );
}


```

# Assembly Code

```

Disassembly of section .text:
temp_activated_fan_controller.o:     file format elf32-littleriscv


Disassembly of section .text:

00000000 <main>:
   0:	fe010113          	add	sp,sp,-32
   4:	00812e23          	sw	s0,28(sp)
   8:	02010413          	add	s0,sp,32
   c:	1f400793          	li	a5,500
  10:	fef42623          	sw	a5,-20(s0)
  14:	001f7793          	and	a5,t5,1
  18:	fef42423          	sw	a5,-24(s0)
  1c:	fe842703          	lw	a4,-24(s0)
  20:	00100793          	li	a5,1
  24:	02f71063          	bne	a4,a5,44 <.L2>
  28:	ffd00793          	li	a5,-3
  2c:	fef42223          	sw	a5,-28(s0)
  30:	fe042783          	lw	a5,-32(s0)
  34:	00ff7f33          	and	t5,t5,a5
  38:	002f6793          	or	a5,t5,2
  3c:	fef42223          	sw	a5,-28(s0)
  40:	01c0006f          	j	5c <.L3>

00000044 <.L2>:
  44:	ffd00793          	li	a5,-3
  48:	fef42223          	sw	a5,-28(s0)
  4c:	fe042783          	lw	a5,-32(s0)
  50:	00ff7f33          	and	t5,t5,a5
  54:	000f6793          	or	a5,t5,0
  58:	fef42223          	sw	a5,-28(s0)

0000005c <.L3>:
  5c:	00000793          	li	a5,0
  60:	00078513          	mv	a0,a5
  64:	01c12403          	lw	s0,28(sp)
  68:	02010113          	add	sp,sp,32
  6c:	00008067          	ret



```

Number of different instructions: 10
List of unique instructions:
```
bne
and
ret
mv
li
lw
j
or
sw
add
```



## Reference
* https://github.com/kunalg123
* https://github.com/The-OpenROAD-Project/OpenSTA.git
* https://github.com/kunalg123
* https://www.vsdiat.com
* https://github.com/SakethGajawada/RISCV-GNU



