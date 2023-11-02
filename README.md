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

#include<stdio.h>

int main()
{
int i,j;
int motor_buffer,Result1,mask;
int temp_sensor,motor_out;



//for (int j=0; j<15;j++) 

while (1)
{

/*if(j < 7)
		 motor_buffer = 1;
	else
		 motor_buffer =0;
			
*/

			
//  asm code to read sensor value

	asm volatile(
		"or x30, x30, %1\n\t"
		"andi %0, x30, 0x01\n\t"
		: "=r" (temp_sensor)                             // input
		: "r"  (motor_buffer)                        // storing input
		: "x30"
		);



//if condition logic
if  (motor_buffer)
	{
	mask=0xFFFFFFFD;
	
	  //printf(" \n");
	
	motor_out=1;
	
	asm volatile(
            "and x30,x30, %0\n\t"     
            "ori x30, x30,2"               
            :
            :"r"(mask)
            :"x30"
            );
            
            asm volatile(
	    	"addi %0, x30, 0\n\t"
	    	:"=r"(Result1)
	    	:
	    	:"x30"
	    	);
    	  //printf("Result1 = %d\n",Result1);
    	
	

	}
else
	{
	
	mask=0xFFFFFFFD;
	
	motor_out=0;
	
	
	asm volatile( 
            "and x30,x30, %0\n\t"     
            "ori x30, x30,0"            
            :
            :"r"(mask)
            :"x30"
        );
        asm volatile(
	    	"addi %0, x30, 0\n\t"
	    	:"=r"(Result1)
	    	:
	    	:"x30"
	    	);
	   //printf("Result1 = %d\n",Result1);

	}
      //printf("motor_out=%d \n", motor_buffer); 
}

return 0;
}

	
```

# Assembly Code

```

out:     file format elf32-littleriscv


Disassembly of section .text:

00010054 <main>:
   10054:	fd010113          	addi	sp,sp,-48
   10058:	02812623          	sw	s0,44(sp)
   1005c:	03010413          	addi	s0,sp,48
   10060:	fec42783          	lw	a5,-20(s0)
   10064:	00ff6f33          	or	t5,t5,a5
   10068:	001f7793          	andi	a5,t5,1
   1006c:	fef42423          	sw	a5,-24(s0)
   10070:	fec42783          	lw	a5,-20(s0)
   10074:	02078663          	beqz	a5,100a0 <main+0x4c>
   10078:	ffd00793          	li	a5,-3
   1007c:	fef42223          	sw	a5,-28(s0)
   10080:	00100793          	li	a5,1
   10084:	fef42023          	sw	a5,-32(s0)
   10088:	fe442783          	lw	a5,-28(s0)
   1008c:	00ff7f33          	and	t5,t5,a5
   10090:	002f6f13          	ori	t5,t5,2
   10094:	000f0793          	mv	a5,t5
   10098:	fcf42e23          	sw	a5,-36(s0)
   1009c:	fc5ff06f          	j	10060 <main+0xc>
   100a0:	ffd00793          	li	a5,-3
   100a4:	fef42223          	sw	a5,-28(s0)
   100a8:	fe042023          	sw	zero,-32(s0)
   100ac:	fe442783          	lw	a5,-28(s0)
   100b0:	00ff7f33          	and	t5,t5,a5
   100b4:	000f6f13          	ori	t5,t5,0
   100b8:	000f0793          	mv	a5,t5
   100bc:	fcf42e23          	sw	a5,-36(s0)
   100c0:	fa1ff06f          	j	10060 <main+0xc>

```


```
Number of different instructions: 11
List of unique instructions:
addi
andi
sw
lw
and
ori
mv
or
j
beqz
li
```

## The simulation commands and outputs are as follows:

```bash
riscv64-unknown-elf-gcc -march=rv64i -mabi=lp64 -ffreestanding -o out file.c
spike pk out
```

## Spike Output:
![Screenshot from 2023-10-25 18-51-28](https://github.com/VAIBHAV-VLSI/Temperature-Activated-Fan-Controller/assets/140998525/a9ad7484-5021-4e24-8a3c-4aa1d778a715)
  
## Functional Verification:
![1](https://github.com/VAIBHAV-VLSI/Temperature-Activated-Fan-Controller/assets/140998525/67b6725c-b6d1-46b4-9f7b-1e832e17b9ff)
![2](https://github.com/VAIBHAV-VLSI/Temperature-Activated-Fan-Controller/assets/140998525/661a67de-b046-4237-b4c5-0c6b4446284e)

## GLS

GLS typically stands for "Gate Level Simulation." It is a method used in digital design and verification to simulate the behavior of the synthesized netlist or gate-level representation of a design. This simulation verifies that the logical functionality of the gate-level design matches the intended behavior described in the RTL (Register Transfer Level) design.
Below are the commands used for Netlist generation(Logic Synthesis)

```
read_liberty -lib sky130_fd_sc_hd__tt_025C_1v80_256.lib 
read_verilog processor.v 
synth -top wrapper
dfflibmap -liberty sky130_fd_sc_hd__tt_025C_1v80_256.lib 
abc -liberty sky130_fd_sc_hd__tt_025C_1v80_256.lib
write_verilog synth_processor_test.v

```

command to run gls simulation

```

iverilog -o test synth_processor_test.v testbench.v sky130_sram_1kbyte_1rw1r_32x256_8.v sky130_fd_sc_hd.v primitives.v

```


<b>Highlighted the wrapper module after netlist created</b>
<div>
	<img width="684" alt="Screenshot 2023-11-02 at 9 50 59 PM" src="https://github.com/VAIBHAV-VLSI/Temperature-Activated-Fan-Controller/assets/140998525/4185c69f-fc86-428b-8532-aa117b740a87">
</div>

<b>GLS SImulation results</b>
<div>
	<img width="1469" alt="Screenshot 2023-11-02 at 9 30 06 PM" src="https://github.com/VAIBHAV-VLSI/Temperature-Activated-Fan-Controller/assets/140998525/240f0b95-d2bd-40e3-a446-8749d1d771ad">

</div>

<div>
		<img width="1469" alt="Screenshot 2023-11-02 at 9 51 28 PM" src="https://github.com/VAIBHAV-VLSI/Temperature-Activated-Fan-Controller/assets/140998525/c8ca2a17-af58-4496-ae6f-c19836fc3d7d">

</div>





## References

* https://github.com/SakethGajawada/RISCV_GNU
* https://circuitdigest.com/microcontroller-projects/interfacing-ir-sensor-module-with-arduino
* https://chat.openai.com/

## Acknowledgement

* Kunal Ghosh, VSD Corp. Pvt. Ltd.
* Mayank Kabra, Founder Chipcron Pvt.Ltd    
* Nitesh Sharma, IIITB
  


