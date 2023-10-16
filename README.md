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

vaibhav.o:     file format elf32-littleriscv


Disassembly of section .text:

00010094 <main>:
   10094:	ff010113          	add	sp,sp,-16
   10098:	00112623          	sw	ra,12(sp)
   1009c:	00812423          	sw	s0,8(sp)
   100a0:	01010413          	add	s0,sp,16
   100a4:	000117b7          	lui	a5,0x11
   100a8:	1447a783          	lw	a5,324(a5) # 11144 <motor_out>
   100ac:	00179713          	sll	a4,a5,0x1
   100b0:	80e1a423          	sw	a4,-2040(gp) # 11148 <motor_buffer>
   100b4:	8081a783          	lw	a5,-2040(gp) # 11148 <motor_buffer>
   100b8:	00ff6f33          	or	t5,t5,a5
   100bc:	008000ef          	jal	100c4 <temp_monitor>
   100c0:	ffdff06f          	j	100bc <main+0x28>

000100c4 <temp_monitor>:
   100c4:	ff010113          	add	sp,sp,-16
   100c8:	00812623          	sw	s0,12(sp)
   100cc:	01010413          	add	s0,sp,16
   100d0:	001f7713          	and	a4,t5,1
   100d4:	000117b7          	lui	a5,0x11
   100d8:	14e7a023          	sw	a4,320(a5) # 11140 <__DATA_BEGIN__>
   100dc:	000117b7          	lui	a5,0x11
   100e0:	1407a783          	lw	a5,320(a5) # 11140 <__DATA_BEGIN__>
   100e4:	02078663          	beqz	a5,10110 <temp_monitor+0x4c>
   100e8:	000117b7          	lui	a5,0x11
   100ec:	00100713          	li	a4,1
   100f0:	14e7a223          	sw	a4,324(a5) # 11144 <motor_out>
   100f4:	000117b7          	lui	a5,0x11
   100f8:	1447a783          	lw	a5,324(a5) # 11144 <motor_out>
   100fc:	00179713          	sll	a4,a5,0x1
   10100:	80e1a423          	sw	a4,-2040(gp) # 11148 <motor_buffer>
   10104:	8081a783          	lw	a5,-2040(gp) # 11148 <motor_buffer>
   10108:	00ff6f33          	or	t5,t5,a5
   1010c:	0240006f          	j	10130 <temp_monitor+0x6c>
   10110:	000117b7          	lui	a5,0x11
   10114:	1407a223          	sw	zero,324(a5) # 11144 <motor_out>
   10118:	000117b7          	lui	a5,0x11
   1011c:	1447a783          	lw	a5,324(a5) # 11144 <motor_out>
   10120:	00179713          	sll	a4,a5,0x1
   10124:	80e1a423          	sw	a4,-2040(gp) # 11148 <motor_buffer>
   10128:	8081a783          	lw	a5,-2040(gp) # 11148 <motor_buffer>
   1012c:	00ff6f33          	or	t5,t5,a5
   10130:	00000013          	nop
   10134:	00c12403          	lw	s0,12(sp)
   10138:	01010113          	add	sp,sp,16
   1013c:	00008067          	ret



```


```
Number of different instructions: 13
List of unique instructions:
jal
sll
j
ret
sw
li
lui
beqz
nop
add
lw
or
and
```



## Reference
* https://github.com/kunalg123
* https://github.com/The-OpenROAD-Project/OpenSTA.git
* https://github.com/kunalg123
* https://www.vsdiat.com
* https://github.com/SakethGajawada/RISCV-GNU



