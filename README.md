# Mountain Climber Tracking Device

## Overview
This project aims to provide a protective and secure system for mountain climbers who traverse long distances in challenging terrains. Climbers often face health and accident-related risks, requiring timely and accurate information. Additionally, poor signal conditions in remote areas make it difficult to seek assistance from relief groups. This tracking device is designed to address these challenges by ensuring the safety of climbers and rescue teams through real-time health monitoring and communication features.

## Features
- **Health Monitoring:**
  - Tracks the climber's heartbeat level and alerts if it falls outside the healthy range.
  - Sends a danger signal if an abnormal heartbeat is detected without the climber's knowledge.
  
- **Emergency Assistance:**
  - Automatically transmits the climber's heartbeat level, location, and environmental conditions (temperature and humidity) to the rescue team if help is needed.
  - Allows climbers to manually stop distress signals if they can manage the situation independently.
  
- **Connectivity in Remote Areas:**
  - Designed to work in areas with poor signal reception.
  - Future plans include integrating satellite connectivity (e.g., Starlink) for seamless communication.
  
- **Future Enhancements:**
  - Blood oxygen level and body temperature monitoring for better health assessment.
  - Improved communication and data transmission technologies.

## Hardware & Technologies Used
- **Sensors:** Heartbeat sensor, temperature sensor, humidity sensor, GPS module
- **Communication Module:** LoRaWAN, Satellite connectivity (planned for future versions)
- **Microcontroller:** Arduino / Raspberry Pi
- **Power Supply:** Rechargeable battery with solar charging capability (if applicable)

## Installation & Usage
1. **Hardware Setup:**
   - Assemble the sensors and microcontroller into the wearable device (e.g., backpack-mounted system).
   - Ensure proper connectivity between sensors and the processing unit.

2. **Software Configuration:**
   - Upload the firmware to the microcontroller using Arduino IDE / Python.
   - Configure the emergency signal transmission settings.

3. **Testing & Deployment:**
   - Test the device in controlled environments before field deployment.
   - Verify signal transmission, heartbeat monitoring, and environmental condition reporting.

## Future Goals
- Enhance real-time tracking with improved GPS accuracy.
- Develop a mobile application for climbers and rescue teams.
- Implement AI-based risk prediction based on collected health and environmental data.



## License
This project is licensed under the MIT License - see the LICENSE file for details.



