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



## Physical Implementation Process

In the realm of integrated circuit (IC) design, the process of converting a logical design description into a tangible, fabricable form is known as physical design. This intricate transformation entails the translation of high-level design abstractions into a detailed representation, encompassing the arrangement and interconnection of physical components on a semiconductor substrate.

### 1. Defining Chip Space: Floorplanning
Outline the overall chip area and allocate space for distinct functional blocks.
Account for power grid planning, I/O placement, and the definition of the chip boundary.

### 2. Power Distribution Strategy: Power Planning
Formulate a robust power distribution network to guarantee a stable and ample power supply to all components.
Address power grid topology, voltage drop, and current density considerations.

### 3. Strategic Component Placement: Placement
Strategically position logic cells and other components within the predefined chip area.
Optimize for variables such as signal delays, power consumption, and thermal considerations, leveraging algorithms for enhanced performance and minimized wirelength.

### 4. Clock Synchronization: Clock Tree Synthesis (CTS)
Design and enhance the clock distribution network for synchronous operation.
Minimize skew and jitter in the clock signals.

### 5. Efficient Connection Establishment: Routing
Establish physical connections (metal traces) among placed components.
Consider wirelength, signal integrity, and congestion, employing detailed routing algorithms for efficient and manufacturable metal layers.

### 6. Adherence Check: Physical Verification
Scrutinize the design for compliance with design rules and constraints.
Conduct checks for spacing, width, overlap, and other manufacturing constraints, ensuring alignment with the foundry's specifications.

### 7. Parasitic Effects Modeling: Extraction
Model the parasitic effects of interconnects, including resistance and capacitance.
Extraction tools generate a more precise representation of the circuit's behavior.

### 8. Timing Characteristics Evaluation: Timing Analysis
Assess and optimize the timing characteristics of the design.
Verify setup and hold times, clock-to-q delays, and overall performance, with iterative optimization as necessary to meet timing constraints.

### 9. Signal Quality Assurance: Signal Integrity Analysis
Analyze and rectify issues related to signal quality, such as crosstalk and noise.
Ensure signals reach their destinations with minimal distortion.

### 10. Validation and Refinement: Physical Testing and Debugging
Simulate and test the physical design to guarantee functionality.
Address and refine the design through debugging if required.



## Synthesis

Synthesis in EDA tools is primarly of two steps.
- RTL is converted into a generic gate level netlist.
- Technology mapping is done and generic level netlist is converted to standard netlist.
  
To synthesize the code run the following command

```
run_synthesis
```

<img width="1375" alt="a" src="https://github.com/VAIBHAV-VLSI/Temperature-Activated-Fan-Controller/assets/140998525/92bcbd93-0c74-47c1-96c9-7634d3756d3f">



#### Results after Synthesis
![a-1](https://github.com/VAIBHAV-VLSI/Temperature-Activated-Fan-Controller/assets/140998525/81a275d2-1d5f-48de-977d-7ea4c6959699)


## Floorplan

In the process of ASIC design, floorplanning is crucial for planning the silicon area and creating a robust Power Distribution Network (PDN). The floorplan defines the physical layout of the chip, including core utilization, aspect ratio, margins, and pin configurations. Additionally, it involves strategies such as creating power rings, power straps, macro placement, and blockages to ensure a legalized GDS file.

### Floorplan Environment Variables:

- **FP_CORE_UTIL**: Floorplan core utilization, specifying the percentage of the chip's core area that will be utilized.

- **FP_ASPECT_RATIO**: Floorplan aspect ratio, defining the ratio of the chip's width to its height.

- **FP_CORE_MARGIN**: Core to die margin area, specifying the margin between the core area and the chip boundary.

- **FP_IO_MODE**: Defines pin configurations.
  - 1: Equidistant pin configuration.
  - 0: Non-equidistant pin configuration.

- **FP_CORE_VMETAL**: Vertical metal layer for the core.

- **FP_CORE_HMETAL**: Horizontal metal layer for the core.

Note: Metal layer values are typically one more than specified in the file.

### Power Planning Strategies:

- **Power Rings**: Rings around the edges of the chip connected to the pads to distribute power uniformly.

- **Power Straps**: Higher metal layers used to bring power to the middle of the chip, reducing IR drop and electro-migration problems.

#### Floorplan Command:

To run the floorplan using these environment variables and switches, use the following command:

```
run_floorplan
```

<img width="1375" alt="b" src="https://github.com/VAIBHAV-VLSI/Temperature-Activated-Fan-Controller/assets/140998525/f3577434-4cb6-4fa5-869c-2ecc92c36e06">


- Post the floorplan run, a .def file will have been created within the results/floorplan directory. We may review floorplan files by checking the floorplan.tcl.
- To view the floorplan: Magic is invoked after moving to the results/floorplan directory,then use the floowing command:

```
magic -T /home/vaibhavtiwari/Desktop/sky130A.tech lef read /home/vaibhavtiwari/OpenLane/designs/processor_project/runs/RUN_2023.11.13_10.50.18/tmp/merged.nom.lef def read wrapper.def &

```

![b-2](https://github.com/VAIBHAV-VLSI/Temperature-Activated-Fan-Controller/assets/140998525/53dcea41-17be-47ce-9323-4f7a9f927843)


#### Core area(post floorplan)
![b-3](https://github.com/VAIBHAV-VLSI/Temperature-Activated-Fan-Controller/assets/140998525/72ebcc21-0199-47d8-a39b-ff026bc36ad8)


#### Die area(post floorplan)
![b-4](https://github.com/VAIBHAV-VLSI/Temperature-Activated-Fan-Controller/assets/140998525/05253a6a-1135-43b3-9ad7-bbe4f0cac131)



# Placement Stage in OpenLANE

The placement stage in OpenLANE involves placing standard cells on floorplan rows, aligned with the sites defined in the technology LEF file. The placement is performed in two steps: Global Placement and Detailed Placement.

- Global Placement: Global placement attempts to find an optimal position for all cells, even if they may initially overlap and not align with the rows defined in the floorplan. The optimization during global placement focuses on reducing half-parameter wire length.

- Detailed Placement:  Detailed placement takes the result of global placement and legalizes the positions of cells, adhering to the preferences established during global placement. This step ensures that the final placement is both optimal and adheres to specific design rules.

#### Running Placement:

To run the placement process, use the following command:

```
run_placement
```
<div align="center">
	<img width="1422" alt="c" src="https://github.com/VAIBHAV-VLSI/Temperature-Activated-Fan-Controller/assets/140998525/e2f62f68-c11a-4aa7-9071-3411b9b9fee3">

</div>

- Post placement: the design can be viewed on magic within results/placement directory. Run the follwing command in that directory:

  ```
  magic -T /home/vaibhavtiwari/Desktop/sky130A.tech lef read /home/vaibhavtiwari/OpenLane/designs/processor_project/runs/RUN_2023.11.13_10.50.18/tmp/merged.nom.lef def read wrapper.def &

  ```

  <div align="center">
	![c-2](https://github.com/VAIBHAV-VLSI/Temperature-Activated-Fan-Controller/assets/140998525/227f47df-954e-43f1-8519-624e0e88d5c2)
 
</div>

## Clock Tree Synthesis (CTS) in OpenLANE

Clock Tree Synthesis (CTS) is a crucial step in the OpenLANE ASIC flow, designed to create an optimized clock distribution network for delivering the clock to all sequential elements on the chip. The primary goal is to achieve minimal clock skew across the entire chip, and H-trees are commonly employed as a network topology to fulfill this objective.

#### Purpose of CTS:

The main purposes of building a clock tree are:
- Enabling the clock input to reach every sequential element on the chip.
- Ensuring zero clock skew, minimizing the time delay between different parts of the clock network.

#### H-Tree Methodology:

H-trees are a common methodology followed in CTS due to their effectiveness in minimizing skew. The H-tree structure involves a hierarchical distribution of the clock signal, branching out from a central point to cover different regions of the chip.

#### Running CTS:

To perform Clock Tree Synthesis in OpenLANE, use the following command:

```
run_cts
```
### Timing reports
<div align="center">
![c-3](https://github.com/VAIBHAV-VLSI/Temperature-Activated-Fan-Controller/assets/140998525/b09bbaae-b4b4-44ce-89e8-86443eb0b982)
</div>

### Area Report
<div align="center">
![c-4](https://github.com/VAIBHAV-VLSI/Temperature-Activated-Fan-Controller/assets/140998525/42632986-505c-42e1-85ec-543d4efeab22)
</div>

### Power Report
<div align="center">
![c-5](https://github.com/VAIBHAV-VLSI/Temperature-Activated-Fan-Controller/assets/140998525/838c1601-57a3-49e3-b48b-61a290a38ce7)
</div>

## Routing in OpenLANE

Routing in OpenLANE involves implementing the interconnect system between standard cells using the remaining available metal layers after Clock Tree Synthesis (CTS) and Power Distribution Network (PDN) generation. The routing is performed on routing grids to ensure minimal Design Rule Check (DRC) errors.

OpenLANE utilizes the TritonRoute tool for routing, and the process consists of two stages:

#### Global Routing:
Global routing divides the routing region into rectangular grids, represented as coarse 3D routes using the Fastroute tool.

#### Detailed Routing:
Detailed routing uses finer grids and routing guides to implement the physical wiring. TritonRoute, another tool in the OpenLANE flow, is responsible for this stage.

#### Features of TritonRoute:
- Honoring pre-processed route guides.
- Assumes that each net satisfies inter-guide connectivity.
- Utilizes a Mixed-Integer Linear Programming (MILP) based panel routing scheme.
- Employs an intra-layer parallel and inter-layer sequential routing framework.

#### Running Routing in OpenLANE:

To run the routing process, use the following command:

```
 run_routing
```

- Layout in magic tool post routing: the design can be viewed on magic within results/routing directory. Run the follwing command in that directory:

  ```
  magic -T /home/vaibhavtiwari/Desktop/sky130A.tech lef read /home/vaibhavtiwari/OpenLane/designs/processor_project/runs/RUN_2023.11.13_10.50.18/tmp/merged.nom.lef def read wrapper.def &

  ```
 ### Layout after Routing 
<div align="center">  
	
![c-6](https://github.com/VAIBHAV-VLSI/Temperature-Activated-Fan-Controller/assets/140998525/5bb933e4-fe2a-4a0f-8ff0-a33d151008ff)
![c-7](https://github.com/VAIBHAV-VLSI/Temperature-Activated-Fan-Controller/assets/140998525/56f73633-f0db-4ca8-8842-ebec1e6b41d5)

</div>

### Post Routing Timing report
<div align="center">
![c-8](https://github.com/VAIBHAV-VLSI/Temperature-Activated-Fan-Controller/assets/140998525/f0c3f6a1-6ecc-4453-9efa-bc756b86bbdb)
</div>



### Post Routing Area report
<div align="center">
![c-9](https://github.com/VAIBHAV-VLSI/Temperature-Activated-Fan-Controller/assets/140998525/68cc0a8c-aeb8-4f65-8a3f-faf3639bdb1d)
</div>


### Post Routing Power report
<div align="center">
![c-10](https://github.com/VAIBHAV-VLSI/Temperature-Activated-Fan-Controller/assets/140998525/00c9bfed-f85e-4a40-9055-bf51b86fc96e)
</div>


## Performance calculation
- Clock period : 100ns
- setup slack  : 28.33ns

```
                              1
Max Performance =  ------------------------    = 13.95 MHz
                     clock period - slack(setup)
```

## Summary of Commands

```
cd Desktop/OpenLane/ 

./flow.tcl -interactive
package require openlane 0.9
prep -design project
run_synthesis
run_floorplan
run_placement
run_cts
gen_pdn
run_routing
run_magic
run_magic_spice_export
run_magic_drc
run_antenna_check


```















## References

* https://github.com/SakethGajawada/RISCV_GNU
* https://circuitdigest.com/microcontroller-projects/interfacing-ir-sensor-module-with-arduino
* https://chat.openai.com/

## Acknowledgement

* Kunal Ghosh, VSD Corp. Pvt. Ltd.
* Mayank Kabra, Founder Chipcron Pvt.Ltd    
* Dinesh,MTech, IIITB.
* Amit Bharadhwaj, MTech, IIITB.
  


