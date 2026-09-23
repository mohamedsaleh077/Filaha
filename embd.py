import time
import serial

value = "0"

def get_value():
    return value.split(",")

def get_soil_data():
    PORT = "/dev/ttyACM0"
    BAUD_RATE = 9600
    global value   

    try:
        # Serial timeout lets readline() yield control back to the loop
        arduino = serial.Serial(PORT, BAUD_RATE, timeout=1)
        print(f"Connected to Arduino on {PORT}")
        time.sleep(2)

        while True:
            # Read directly; timeout handles waiting
            raw_data = arduino.readline()
            if raw_data:
                line = raw_data.decode("utf-8", errors="ignore").strip()
                if line:
                    value = line
                    print(f"Updated sensor value: {value}")  # Debug print to confirm receipt

    except serial.SerialException as e:
        print(f"Serial Error on {PORT}: {e}")
    except Exception as e:
        print(f"Unexpected Error: {e}")
    finally:
        if "arduino" in locals() and arduino.is_open:
            arduino.close()
            print("Serial port closed.")