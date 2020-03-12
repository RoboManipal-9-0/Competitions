from smbus import SMBus
from time import sleep
refreshInterval=0.25
addr=0x08
bus=SMBus(1)
while (1):
	try:
		dataRec=bus.read_i2c_block_data(addr,0x61) # Hex for 'a' is 0x61
		numRec=int(dataRec[0])*256+int(dataRec[1])
		print("Ultrasonic 1 distance:",numRec)
		dataRec=bus.read_i2c_block_data(addr,0x62) # Hex for 'b' is 0x62
		numRec=int(dataRec[0])*256+int(dataRec[1])
		print("Ultrasonic 2 distance:",numRec)
		dataRec=bus.read_i2c_block_data(addr,0x63) # Hex for 'c' is 0x63
		numRec=int(dataRec[0])
		print("LSA 1 value:",numRec)
		dataRec=bus.read_i2c_block_data(addr,0x64) # Hex for 'd' is 0x64
		numRec=int(dataRec[0])
		print("LSA 2 value:",numRec)
		dataRec=bus.read_i2c_block_data(addr,0x65) # Hex for 'e' is 0x65
		yaw=(1-dataRec[0])*(int(dataRec[1])*256+int(dataRec[2]))/100.0
		pitch=(1-dataRec[3])*(int(dataRec[4])*256+int(dataRec[5]))/100.0
		roll=(1-dataRec[6])*(int(dataRec[7])*256+int(dataRec[8]))/100.0
		print("Yaw:",yaw,"; Pitch:",pitch,"; Roll:",roll)
		sleep(refreshInterval)
	except TimeoutError:
		print("Connection timed out, retrying...")
	except OSError:
		print("Error connecting to Arduino, retrying...")
	except KeyboardInterrupt:
		print("Detected keyboard interrupt. Exiting!")
		quit()
