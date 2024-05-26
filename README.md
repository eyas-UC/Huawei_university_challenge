<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
<!--[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url] -->
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedInEyas][linkedin-eyas-shield]][linkedin-eyas-url]
[![LinkedInKhaled][linkedin-khaled-shield]][linkedin-khaled-url]


<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary>Table of Contents</summary>
  <ol>
      <li><a href="#about-the-project">About The Project</a>
      <li><a href="#Implementation">Implementation</a></li>
      <li><a href="#installation">Installation</a></li>
      <li><a href="#contributing">Contributing</a></li>
      <li><a href="#license">License</a></li>
      <li><a href="#contact">Contact</a></li>
      <li><a href="#acknowledgements">Acknowledgements</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

Huawei University Challenge in its first first version was focusing on “Real-Time Intelligent and Automotive Applications”: automotive embedded software is becoming more and more crucial to guarantee low fuel consumption, respect of pollution parameters, or a longer life-time of mechanical components. In this content, Huawei introduces this challenge to open the participation to the broad audience from different backgrounds and experiences to accommodate these skills on a real-time application that may improve an existing challenge or add a new feature that does not exist (https://tree.it/huawei-italy-university-challenge/).

<p align="center">
  <img src="/Images/huawei_challange.png" />
</p>

## Implementation

We developed a neural network on a real-time embedded system based on Erika (RTOS) that capable to distinguish the existence of an object (car). The real application we tried to reflect is an autonomous vehicle that has the capabilities to recognize its surrender (i.e. a real-time surveillance camera) with high sensitivity. Because of compatibility, we used a series of car images as a prototype of the real-time system. Nevertheless, the gyroscope which is available on the embedded system has been used for some functionality.

The dataset which we used was extracted by [(GTI) of Universidad Politécnica de Madrid (UPM) research group](file:///C:/Users/kalee/Desktop/car_camera_front_view/Vehicle_database_OwnCollection.html) from a video sequences. The images have 64x64 and are cropped from sequences of 360x256 pixels recorded in highways of Madrid, Brussels and Turin.

## Dependencies 

The neural network has been trained using Python 3.6. The parameters (weight & bias) of the trained neural network have been deployed in STM32F429 using C. The unclassified images (test set) are sent via virtual COMM to the STM to decide (based on the fitted model) either the image containing a car or not and display the result on the screen.


## Installation

The database is open for use of other researchers and can be downloaded [here](http://www.gti.ssr.upm.es/~jal/download.html)

<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

[![YouTube](http://i.ytimg.com/vi/C0ur-UBjmIw/hqdefault.jpg)](https://www.youtube.com/watch?v=C0ur-UBjmIw)

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.



<!-- CONTACT -->
## Contact

Eyas Ali - [@LinkedIn](https://www.linkedin.com/in/eyas-ali/)
Khaled Alamin - [@LinkedIn](https://www.linkedin.com/in/khaled-alamin/)
<!--Project Link: [https://github.com/your_username/repo_name](https://github.com/your_username/repo_name)-->


<!-- ACKNOWLEDGEMENTS -->
## Acknowledgements
* [GitHub Emoji Cheat Sheet](https://www.webpagefx.com/tools/emoji-cheat-sheet)
* [Img Shields](https://shields.io)
* [Choose an Open Source License](https://choosealicense.com)
* [GitHub Pages](https://pages.github.com)
* [Animate.css](https://daneden.github.io/animate.css)
* [Loaders.css](https://connoratherton.com/loaders)
* [Slick Carousel](https://kenwheeler.github.io/slick)
* [Smooth Scroll](https://github.com/cferdinandi/smooth-scroll)
* [Sticky Kit](http://leafo.net/sticky-kit)
* [JVectorMap](http://jvectormap.com)
* [Font Awesome](https://fontawesome.com)



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/othneildrew/Best-README-Template.svg?style=for-the-badge
[contributors-url]: https://github.com/KhaledAlamin/Huawei_embedded_dnn/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/othneildrew/Best-README-Template.svg?style=for-the-badge
[forks-url]: https://github.com/KhaledAlamin/Huawei_embedded_dnn/network/members
[stars-shield]: https://img.shields.io/github/stars/othneildrew/Best-README-Template.svg?style=for-the-badge
[stars-url]: https://github.com/KhaledAlamin/Huawei_embedded_dnn/stargazers
[issues-shield]: https://img.shields.io/github/issues/othneildrew/Best-README-Template.svg?style=for-the-badge
[issues-url]: https://github.com/KhaledAlamin/Huawei_embedded_dnn/issues
[license-shield]: https://img.shields.io/github/license/othneildrew/Best-README-Template.svg?style=for-the-badge
[license-url]: https://github.com/KhaledAlamin/Huawei_embedded_dnn/blob/main/LICENSE.txt
[linkedin-khaled-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-khaled-url]: https://www.linkedin.com/in/khaled-alamin/
[linkedin-eyas-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-eyas-url]: https://www.linkedin.com/in/EyasAli/
