import socket
import random
import time
import json

def generate_pixel_data():
    # Generate a list of pixel data objects
    pixels = []
    for _ in range(random.randint(5, 10)):  # random number of pixels per value
        pixel = {
            "pixel_depth": round(random.uniform(0, 100), 2),
            "pixel_pos_x": round(random.uniform(0, 1920), 2),
            "pixel_pos_y": round(random.uniform(0, 1080), 2)
        }
        pixels.append(pixel)
    return pixels

def generate_data():
    # Generate a list of value objects, each with a 'pixels' array
    values = []
    for _ in range(8):  # 8 value objects
        value = {
            "pixels": generate_pixel_data()
        }
        values.append(value)
    radarData = [random.randint(0, 3999) for _ in range(8)]
    payload = {
        "values": values,
        "radarData": radarData,
        "timestamp": int(time.time() * 1000) - 80
    }
    return payload

if __name__ == "__main__":
    HOST = "localhost"
    PORT = 8001
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((HOST, PORT))
            while True:
                payload = generate_data()
                print("Sending payload:", payload)
                s.sendall(json.dumps(payload).encode('utf-8'))
                time.sleep(0.040)  # 20 milliseconds
    except KeyboardInterrupt:
        print("Stopped sending data.")
    except Exception as e:
        print("Error:", e)