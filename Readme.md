# ONVIF Implementation Project for Jetson Nano

This project is an implementation of the ONVIF protocol for Jetson Nano, with the aim of discovering, connecting, and receiving video data from ONVIF-compliant cameras. The project includes a C/C++ client application that communicates with the cameras using the ONVIF protocol.

## Prerequisites

- Jetson Nano development kit with JetPack installed
- ONVIF-compliant cameras connected to the network
- ONVIF client library (such as ONVIF Device Manager) installed on the Jetson Nano

## Installation and Usage

1. Clone the repository to your local machine: `git clone https://github.com/tin-nguyen-31k17/ONVIF-Implementation-Project-for-Jetson-Nano.git`
2. Navigate to the project directory: `cd ONVIF-Implementation-Project-for-Jetson-Nano`
3. Compile the client application: `make`
4. Run the client application: `./ONVIF-FPT`

# Run
- ./OnvifPVR configFile.txt
- ./OnvifPVR IP 192.168.1.1
  - Look for the IP of ONVIF cameras on local network.
- ./OnvifPVR rtsp://@192.168.15.2:554/onvif1 udp
  - Runs OnvifPVR for just one camera, udp if the the stream is udp.

The client application will automatically discover any ONVIF-compliant cameras on the network and display their details, including their IP addresses, MAC addresses, and ONVIF profiles. You can then choose to connect to a camera and receive video data from it.

## Configuration

The client application can be configured using the `config.ini` file, which is located in the project directory. This file contains the following options:

- `log_level`: the log level to use for the application (options are `DEBUG`, `INFO`, `WARN`, `ERROR`, and `FATAL`)
- `discovery_timeout`: the timeout (in seconds) for ONVIF discovery requests
- `username` and `password`: the credentials to use for connecting to the ONVIF devices

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.

## Acknowledgments

This project was inspired by the ONVIF Device Manager project and uses the ONVIF client library provided by that project. Special thanks to the developers of ONVIF Device Manager for their contributions to the ONVIF community.

## Contributing

If you have any suggestions, bug reports, or feature requests, please feel free to open an issue or submit a pull request. We welcome contributions from the community and will review them as soon as possible.
