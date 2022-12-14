#include <velcro.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	/* code */
	uint8_t msg0[14] = {0x8d, 0x4c, 0xa5, 0xc0, 0x20, 0x24, 0x22, 0xf1, 0x28, 0x38, 0x20, 0xf3, 0x24, 0x04};
	//                               ERROR---v
	uint8_t msg1[14] = {0x8d, 0x4c, 0xa5, 0xc1, 0x20, 0x24, 0x22, 0xf1, 0x28, 0x38, 0x20, 0xf3, 0x24, 0x04};
	uint8_t msg2[7] = {0x5d, 0x3c, 0x48, 0xc8, 0xad, 0x3d, 0xf9};
	uint8_t msg3[7] = {0x5d, 0x3c, 0x48, 0xc9, 0xad, 0x3d, 0xf9};

	uint32_t res;
	res = modesChecksum( msg0, 8*14);
	printf("CRC: %08x\n", res);
	res = modesChecksum( msg1, 8*14);
	printf("CRC: %08x\n", res);
	res = modesChecksum( msg2, 8*7);
	printf("CRC: %08x\n", res);
	res = modesChecksum( msg3, 8*7);
	printf("CRC: %08x\n", res);
	return 0;
}
