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

int main() {

    int temp_sensor; 
    int motor_out=0; 
    int motor_buffer;

     motor_buffer = motor_out*2;

     asm volatile(
	"or x30, x30, %0\n\t" 
	:
	:"r"(motor_buffer)
	:"x30"
	);

    while (1) {
         asm volatile(
	"andi %0, x30, 1\n\t"
	:"=r"(temp_sensor)
	:
	:
	);

        if (temp_sensor) {
            motor_out = 1;
            motor_buffer = motor_out*2;
            asm volatile(
		"or x30, x30, %0\n\t" 
		:
		:"r"(motor_buffer)
		:"x30"
		);
        } else {
            motor_out = 0;
            motor_buffer = motor_out*2;
            asm volatile(
		"or x30, x30, %0\n\t" 
		:
		:"r"(motor_buffer)
		:"x30"
		);
        }
    }
    return 0;
}

	
```

# Assembly Code

```

out:     file format elf32-littleriscv


Disassembly of section .text:

00010054 <main>:
   10054:	fe010113          	addi	sp,sp,-32
   10058:	00812e23          	sw	s0,28(sp)
   1005c:	02010413          	addi	s0,sp,32
   10060:	fe042623          	sw	zero,-20(s0)
   10064:	fec42783          	lw	a5,-20(s0)
   10068:	00179793          	slli	a5,a5,0x1
   1006c:	fef42423          	sw	a5,-24(s0)
   10070:	fe842783          	lw	a5,-24(s0)
   10074:	00ff6f33          	or	t5,t5,a5
   10078:	001f7793          	andi	a5,t5,1
   1007c:	fef42223          	sw	a5,-28(s0)
   10080:	fe442783          	lw	a5,-28(s0)
   10084:	02078263          	beqz	a5,100a8 <main+0x54>
   10088:	00100793          	li	a5,1
   1008c:	fef42623          	sw	a5,-20(s0)
   10090:	fec42783          	lw	a5,-20(s0)
   10094:	00179793          	slli	a5,a5,0x1
   10098:	fef42423          	sw	a5,-24(s0)
   1009c:	fe842783          	lw	a5,-24(s0)
   100a0:	00ff6f33          	or	t5,t5,a5
   100a4:	fd5ff06f          	j	10078 <main+0x24>
   100a8:	fe042623          	sw	zero,-20(s0)
   100ac:	fec42783          	lw	a5,-20(s0)
   100b0:	00179793          	slli	a5,a5,0x1
   100b4:	fef42423          	sw	a5,-24(s0)
   100b8:	fe842783          	lw	a5,-24(s0)
   100bc:	00ff6f33          	or	t5,t5,a5
   100c0:	fb9ff06f          	j	10078 <main+0x24>


```


```
Number of different instructions: 9
List of unique instructions:
addi
andi
sw
lw
slli
or
j
beqz
li
```
  


## Reference
* https://github.com/kunalg123
* https://github.com/The-OpenROAD-Project/OpenSTA.git
* https://github.com/kunalg123
* https://www.vsdiat.com
* https://github.com/SakethGajawada/RISCV-GNU



