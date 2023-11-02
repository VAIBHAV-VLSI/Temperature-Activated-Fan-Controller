



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






	

