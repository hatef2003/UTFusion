import socket
import random
import time
import json

def generate_data():
    data = [random.randint(0, 3999) for _ in range(8)]
    timestamp = int(time.time())
    payload = {
        "values": data,
        "timestamp": timestamp
    }
    return payload

if __name__ == "__main__":
    HOST = "localhost"
    PORT = 8000
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((HOST, PORT))
            while True:
                payload = generate_data()
                print("Sending payload:", payload)
                s.sendall(json.dumps(payload).encode('utf-8'))
                time.sleep(0.02)  # 20 milliseconds
    except KeyboardInterrupt:
        print("Stopped sending data.")
    except Exception as e:
        print("Error:", e)