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

int main() {
    while (1) {
        temp_monitor();   //continuous running of hardware
    }
    return 0;
}

// Function to monitor temperature level and control the motor
void temp_monitor() {
 
    int temp_sensor;
    int motor_out=0; 
    int motor_buffer;
    motor_buffer = motor_out*2;
     asm(
	"or x30, x30, %0\n\t" 
	:"=r"(motor_buffer));
    
    asm(
	"andi %0, x30, 1\n\t"
	:"=r"(temp_sensor)); //getting the input from sensor
    

    while (1) {
       
        if (temp_sensor) {
           
            motor_out = 1;
            motor_buffer = motor_out*2;
            asm(
		"or x30, x30, %0\n\t" 
		:"=r"(motor_buffer));
        } else {            
            motor_out = 0;
            motor_buffer = motor_out*2;
            asm(
		"or x30, x30, %0\n\t" 
		:"=r"(motor_buffer));
        }
    }
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
add
sw
auipc
jalr
j
lw
sll
or
and
beqz

```



## Reference
* https://github.com/kunalg123
* https://github.com/The-OpenROAD-Project/OpenSTA.git
* https://github.com/kunalg123
* https://www.vsdiat.com
* https://github.com/SakethGajawada/RISCV-GNU



