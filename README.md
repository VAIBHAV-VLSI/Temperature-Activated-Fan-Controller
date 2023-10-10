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

void temp_monitor();

int temp_sensor; 
int motor_out=0; 
int motor_buffer;
int main() {

     motor_buffer = motor_out*2;
     asm volatile(
	"or x30, x30, %0\n\t" 
	:
	:"r"(motor_buffer)
	:"x30"
	);

    while (1) {
        temp_monitor();
    }
    return 0;
}

// Function to sense the temprature and control the fan motor.



void temp_monitor()  {
 
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
	


```

# Assembly Code

```
Disassembly of section .text:

00000000 <main>:
   0:	ff010113          	add	sp,sp,-16
   4:	00112623          	sw	ra,12(sp)
   8:	00812423          	sw	s0,8(sp)
   c:	01010413          	add	s0,sp,16
  10:	000007b7          	lui	a5,0x0
  14:	0007a783          	lw	a5,0(a5) # 0 <main>
  18:	00179713          	sll	a4,a5,0x1
  1c:	000007b7          	lui	a5,0x0
  20:	00e7a023          	sw	a4,0(a5) # 0 <main>
  24:	000007b7          	lui	a5,0x0
  28:	0007a783          	lw	a5,0(a5) # 0 <main>
  2c:	00ff6f33          	or	t5,t5,a5

00000030 <.L2>:
  30:	00000097          	auipc	ra,0x0
  34:	000080e7          	jalr	ra # 30 <.L2>
  38:	ff9ff06f          	j	30 <.L2>

0000003c <temp_monitor>:
  3c:	ff010113          	add	sp,sp,-16
  40:	00812623          	sw	s0,12(sp)
  44:	01010413          	add	s0,sp,16
  48:	001f7713          	and	a4,t5,1
  4c:	000007b7          	lui	a5,0x0
  50:	00e7a023          	sw	a4,0(a5) # 0 <main>
  54:	000007b7          	lui	a5,0x0
  58:	0007a783          	lw	a5,0(a5) # 0 <main>
  5c:	02078a63          	beqz	a5,90 <.L4>
  60:	000007b7          	lui	a5,0x0
  64:	00100713          	li	a4,1
  68:	00e7a023          	sw	a4,0(a5) # 0 <main>
  6c:	000007b7          	lui	a5,0x0
  70:	0007a783          	lw	a5,0(a5) # 0 <main>
  74:	00179713          	sll	a4,a5,0x1
  78:	000007b7          	lui	a5,0x0
  7c:	00e7a023          	sw	a4,0(a5) # 0 <main>
  80:	000007b7          	lui	a5,0x0
  84:	0007a783          	lw	a5,0(a5) # 0 <main>
  88:	00ff6f33          	or	t5,t5,a5
  8c:	02c0006f          	j	b8 <.L6>

00000090 <.L4>:
  90:	000007b7          	lui	a5,0x0
  94:	0007a023          	sw	zero,0(a5) # 0 <main>
  98:	000007b7          	lui	a5,0x0
  9c:	0007a783          	lw	a5,0(a5) # 0 <main>
  a0:	00179713          	sll	a4,a5,0x1
  a4:	000007b7          	lui	a5,0x0
  a8:	00e7a023          	sw	a4,0(a5) # 0 <main>
  ac:	000007b7          	lui	a5,0x0
  b0:	0007a783          	lw	a5,0(a5) # 0 <main>
  b4:	00ff6f33          	or	t5,t5,a5

000000b8 <.L6>:
  b8:	00000013          	nop
  bc:	00c12403          	lw	s0,12(sp)
  c0:	01010113          	add	sp,sp,16
  c4:	00008067          	ret



```


```
Number of different instructions: 14
List of unique instructions:
ret
jalr
li
nop
lw
sw
auipc
sll
or
j
beqz
and
lui
add

```



## Reference
* https://github.com/kunalg123
* https://github.com/The-OpenROAD-Project/OpenSTA.git
* https://github.com/kunalg123
* https://www.vsdiat.com
* https://github.com/SakethGajawada/RISCV-GNU



