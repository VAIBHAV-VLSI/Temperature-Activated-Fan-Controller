# Temperature Activated Fan Controller


# Overview

Temperature controlling is required in many places such as server rooms, houses, industries, etc. Here the Temperature controlled fan will act to the temperature changes.

We are going to do this with a DHT11 temperature and humidity sensor as DHT11 is a efficient & cost-effective sensor.

Temperature-controlled fan will use RISCV. With this, we will be able to change the fan speed in our home or any place according to the room temperature. 


# Requirements 

The components required for the project are listed below:

```
RISCV  
Temperature Sensor(DHT11 sensor)
DC Fan
9 volt battery
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
        " %1, [%0]\n\t" // Store fan_reg value to FAN_CTRL register
        :
        : "r"(FAN_CTRL), "r"(fan_reg)
    );
}


```

# Assembly Code

```
input:     file format elf32-littleriscv


Disassembly of section .text:

00000000 <main>:
   0:	ff010113          	add	sp,sp,-16
   4:	00112623          	sw	ra,12(sp)
   8:	00812423          	sw	s0,8(sp)
   c:	01010413          	add	s0,sp,16

00000010 <.L2>:
  10:	00000097          	auipc	ra,0x0
  14:	000080e7          	jalr	ra # 10 <.L2>
  18:	ff9ff06f          	j	10 <.L2>

0000001c <temp_monitor>:
  1c:	fe010113          	add	sp,sp,-32
  20:	00812e23          	sw	s0,28(sp)
  24:	02010413          	add	s0,sp,32
  28:	fe042623          	sw	zero,-20(s0)
  2c:	fec42783          	lw	a5,-20(s0)
  30:	00179793          	sll	a5,a5,0x1
  34:	fef42423          	sw	a5,-24(s0)
  38:	00ff6f33          	or	t5,t5,a5
  3c:	fef42423          	sw	a5,-24(s0)
  40:	001f7793          	and	a5,t5,1
  44:	fef42223          	sw	a5,-28(s0)

00000048 <.L6>:
  48:	fe442783          	lw	a5,-28(s0)
  4c:	02078263          	beqz	a5,70 <.L4>
  50:	00100793          	li	a5,1
  54:	fef42623          	sw	a5,-20(s0)
  58:	fec42783          	lw	a5,-20(s0)
  5c:	00179793          	sll	a5,a5,0x1
  60:	fef42423          	sw	a5,-24(s0)
  64:	00ff6f33          	or	t5,t5,a5
  68:	fef42423          	sw	a5,-24(s0)
  6c:	fddff06f          	j	48 <.L6>

00000070 <.L4>:
  70:	fe042623          	sw	zero,-20(s0)
  74:	fec42783          	lw	a5,-20(s0)
  78:	00179793          	sll	a5,a5,0x1
  7c:	fef42423          	sw	a5,-24(s0)
  80:	00ff6f33          	or	t5,t5,a5
  84:	fef42423          	sw	a5,-24(s0)
  88:	fc1ff06f          	j	48 <.L6>

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



