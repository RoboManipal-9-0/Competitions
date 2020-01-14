from smbus import SMBus
addr=0x08
bus = SMBus(1)
while (1):
	choice=int(input("1 > ON ; 2 > OFF ; 3 > Receive String ; 4 > Receive Number ; 5 > Send String ;; "))
	if choice == 1:
		bus.write_byte(addr,0x31) # Hex for '1' is 0x31
	elif choice==2:
		bus.write_byte(addr,0x30) # Hex for '0' is 0x30
	elif choice==3:
		dataRec=bus.read_i2c_block_data(addr,0x73) # Hex for 's' is 0x73
		for i in range (0,len(dataRec)):
			if not dataRec[i]==255:
				print(chr(dataRec[i]),end='')
		print()
	elif choice==4:
		dataRec=bus.read_i2c_block_data(addr,0x75) # Hex for 'u' is 0x75
		numRec=int(dataRec[0])*256+int(dataRec[1])
		print("Ultrasonic distance:",numRec)
	elif choice==5:
		dataSend=[72,101,108,108,111,32,65,114,100,117,105,110,111,33] # Message is 'Hello Arduino!'
		bus.write_i2c_block_data(addr,0x72,dataSend) # Hex for 'r' is 0x72
