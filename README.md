# Depth-Car
**Depth-Car** _A four wheel drive car with _monocular depth estimation.__

![](media/DSC01407.JPG)

<p align="center"><a href="https://github.com/KozhaAkhmet/depth-car/wiki">
<strong> Read the docs » </strong></a></p>

## About the Project

Depth Car is an autonomous car with Monocular depth estimation using MiDAS, TensorFlow Lite and OpenCV on The Raspberry Pi 4, written in C++.

This project uses Midas Depth Estimation as a core part of the project. So it is recommended to have basic knowledge about it. 
There is an example repository that explains the model and installation steps. The repository is available at [Midas Cpp Example](https://github.com/KozhaAkhmet/MiDaS-v2.1-small-cpp).

The detection uses a simple algorithm, which extracts a particular layer from the calculated estimation and stores it as a binary image. The robot then calculates whether to move left or right by calculating and analyzing the number of pixels on the image.

The aim of the project is to achieve a simple yet fast solution suitable to run on Raspberry Pi 4+ devices using C++ only. This project is developed as my bachelor's degree graduation project **"Making an Autonomous Car with Depth Estimation"**.  

## Results

This project is tested on Raspberry Pi 4 Model B with 4 GB RAM with the 64-bit Ubuntu 22.04 without overclocking. Used a 3A power supply. Here are the results:

| Device         | RAM  | OS     | Multithread(All) Performance | Single Thread Performance |
| -------------- | ---- | ------ | ---------------------------- | ------------------------- |
| Raspberry Pi 4 | 4 GB | Ubuntu | ~ 2.3 FPS                   | ~ 0.91 FPS                |

![](media/Video%20Edit.gif)

## Installation

You can follow the instructions in [docs](https://github.com/KozhaAkhmet/depth-car/wiki/Software-Installation)

## License
Licensed under the [GNU General Public License](https://github.com/KozhaAkhmet/depth-car/blob/main/LICENSE).

## Contact

**Depth-Car** _A four wheel drive car with _monocular depth estimation.__

<i>Developed by <a href="https://github.com/KozhaAkhmet">Kozha Akhmet Abdramanov</a>

* Robot Car with Depth Estimation Source Code: 
[KozhaAkhmet/depth-car](https://github.com/KozhaAkhmet/depth-car)
* Midas in C++ Source Code: 
[KozhaAkhmet/MiDaS-v2.1-small-cpp](https://github.com/KozhaAkhmet/MiDaS-v2.1-small-cpp)

Feel free to contact me from my email address: [kozha.akhmt@gmail.com](mailto:kozha.akhmt@gmail.com).

