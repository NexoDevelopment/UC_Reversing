typedef Handle uint32_t;

Handle UCOpen() {

	OSMutex *uc_mutex = 0x101c9b40;
	OSInitMutex(uc_mutex);
	OSLockMutex(uc_mutex);

	//Unknown part text+30 -> text+50

	uint32_t *buf_pool = 0x100523b0;

	int addr = 0x101c9b80; // arg1
	int mode = 4; // ? Not sure
	int size = 0x1000; //arg3
	int arg4 = *(0x100523b0 + 8) 
	int arg5 = 1;

	int ret = IPCBufPoolCreate(addr, mode, size, arg4, arg5);

	if(ret) {

		try_open_module();

	} else {

		int addr = 0x10209b80;
		int mode = 1;
		int size = 0x80;
		int arg4 = *(0x100523b0 + 16);
		int arg5 = 1; 

		int ret = IPCBufPoolCreate(addr, mode, size, arg4, arg5);

		if(buf_pool[1]) {

			if(!try_open_module()) {
				buf_pool[1] = 1;
			}

		}

	}

}

int UCClose(Handle handle) {
	IOS_Close(handle);
}

void try_open_module() {

	OSUnlockMutex(uc_mutex);

	if(buf_pool[0] != 1) {
		return uc_mutex;
	} else {
		return IOS_Open("/dev/usr_cfg", 0);
	}
}