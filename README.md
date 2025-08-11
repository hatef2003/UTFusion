# UTFusion - Sensor Fusion Project

## Project Purpose
UTFusion is a **Qt-based C++ application** designed to perform sensor fusion between **camera** and **radar** data.  
The primary goal is to correlate data from these two different sensor types to obtain a **more accurate** and **robust** understanding of the environment.  

This project uses **mock servers** to simulate sensor data, making it a good platform for developing and testing fusion algorithms **without the need for physical hardware**.

---

## Features Overview
- **Multi-Sensor Integration**: Fuses data from simulated camera and radar sensors.  
- **Mock Data Servers**: Includes TCP servers to mock radar, camera, and object detection data streams.  
- **Coordinate Transformation**: Converts 2D pixel coordinates to 3D world coordinates.  
- **Synchronization**: Buffers and synchronizes data based on timestamps to process related data points together.  
- **Modular Design**: Fusion logic, data handling, and sensor interfaces are separated into different classes for extensibility.  

---

## Dependencies and Installation

This project is built with the **Qt framework**.

- **Qt 6.x** (Download from [Qt Official Website](https://www.qt.io/download))
    - During installation, select:
        - `Qt Core`
        - `Qt Gui`
        - `Qt Network`
- **C++17 Compiler** (e.g., GCC, Clang, MSVC)

---

## How to Build and Run the Project

### Building with Qt Creator
1. Open the `UTFusion.pro` file in **Qt Creator**.
2. Configure with a Qt 6 kit (e.g., `Desktop Qt 6.6.3 MinGW 64-bit`).
3. Build the project: **Build > Build Project "UTFusion"**.
4. Run the application: **Build > Run**.

### Building from the Command Line
(Provide your platform-specific `qmake` / `cmake` commands here if needed.)

---

## Running the Application
After building, the executable will be located in a directory like:  
`build/Desktop_Qt_6_6_3_MinGW_64_bit-Debug/debug/`

When running, the application starts **three TCP servers**:

| Server Name             | Port |
|-------------------------|------|
| MockRadarData           | 8000 |
| MockImageReceiver       | 8080 |
| ErfanMocker (Object Detection) | 8001 |

To see the fusion in action, you must send data to these ports from another application (e.g., a Python script).

---

## Directory and File Structure

UTFusion.pro # Main qmake project file
main.cpp # Application entry point
globals.h # Global constants

FusionUtils/
fusion.h/.cpp # Main fusion logic
pixel2world.h/.cpp # 2D pixel → 3D world transformation
distance_calculator.h/.cpp # Distance utilities
buffer.h/.cpp # Circular buffer for synchronized data
datacontainer.h/.cpp # Data buffer management

mockradardata.h/.cpp # TCP server simulating radar data
mockimagereceiver.h/.cpp # TCP server simulating camera data
erfanmocker.h/.cpp # TCP server simulating object detection data
fuse.h/.cpp # Fusion orchestration class
sensorwrapper.h/.cpp # Placeholder class

css
Copy code

---

## File Interconnections Diagram (Mermaid)

```mermaid
graph TD
    A[main.cpp] --> B[Fuse]
    B --> C[FusionUtils/fusion.cpp]
    B --> D[MockRadarData]
    B --> E[MockImageReceiver]
    B --> F[ErfanMocker]
    C --> G[Pixel2World]
    C --> H[DistanceCalculator]
    B --> I[Buffer]
    I --> J[DataContainer]
Notes / Improvements
Real Sensor Integration: Replace mock classes with actual hardware interfaces for real-world usage.

const_cast Usage: Avoid unsafe usage in main.cpp; prefer storing QImage by value or using QSharedPointer<QImage>.

Incomplete Fusion Implementation: Clarify relationship between Fuse and Fusion classes; resolve commented-out references in .pro file.

Error Handling: Improve TCP server handling for disconnections and malformed data.

Configuration: Replace hardcoded server ports with configurable options (command-line or config file).