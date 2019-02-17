// ch341_spi_shiftreg.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

static void DumpByteArray(BYTE *b, int n){
	int i=0;
	for(int i=0;i<n;i++){
		printf("Index=%d, Value=0x%x\r\n",i,(unsigned)b[i]);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int  N = 2;
	BYTE ioBuf[2] = {0xaa,0x55}; // 1010 1010
	int ret = EXIT_SUCCESS;
	HANDLE h341 = NULL;
	ULONG iDevIndex = 0; // first device

	printf("CH341 SPI shift register example\r\n");

	printf("CH341 version: %lu\r\n", CH341GetVersion( ));

	printf("Device %lu name is '%s'\r\n",iDevIndex,CH341GetDeviceName(iDevIndex));

	printf("Opening device# %lu\r\n", iDevIndex);
	h341 = CH341OpenDevice( iDevIndex);
	if (h341 == NULL){
		printf("OpenDevice(iDevIndex=%lu) failed\r\n",iDevIndex);
		ret = EXIT_FAILURE;
		goto exit0;
	}


	// 0x80 send MSB bit first on SPI
	if (!CH341SetStream(iDevIndex,0x80)){
			printf("CH341SetStream failed\r\n");
			ret = EXIT_FAILURE;
			goto exit1;
	}

	// This call is actually necessary to make SPI work!!!!
	// set D0=CS0,D1=CS2,D2=CS3,D3=CLK,D4=?,D5=DOUT,D7=DIN
	if (! CH341Set_D5_D0 (iDevIndex,0x3f,0x0)){
			printf("CH341Set_D5_D0 failed\r\n");
			ret = EXIT_FAILURE;
			goto exit1;
	}

	while(1){
		ioBuf[0]=0xaa;ioBuf[1]=0x55;
		printf("Sending to SPI:\r\n");
		DumpByteArray(ioBuf,2);
		if (!CH341StreamSPI4(iDevIndex,0,2,ioBuf)){
			printf("CH341StreamSPI4 failed\r\n");
			ret = EXIT_FAILURE;
			goto exit1;
		}
		printf("SPI returned back data:\r\n");
		DumpByteArray(ioBuf,2);
		Sleep(10);
		break; // comment it out to have stream of data...
	}


exit1:
	CH341CloseDevice(iDevIndex);
exit0:
	return ret;
}

