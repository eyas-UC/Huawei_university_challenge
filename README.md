<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Thanks again! Now go create something AMAZING! :D
-->

# Huawei_embedded_dnn

**to predict we need parameters (W and b) in addition to the inputs.
in our case w and b are known matrices and can be entered or hard stored in the stm32

in our model layers_dims = [4096, 6,8, 4, 1]


linear_activation_forward(activation = "relu")->linear_forward(X,W1,b1)--->Z1----activation(relu)--->A1
linear_activation_forward(activation = "relu")->linear_forward(A1,W2,b2)--->Z2----activation(relu)--->A2
linear_activation_forward(activation = "relu")->linear_forward(A2,W3,b)--->Z3----activation(relu)--->A3
linear_activation_forward(activation = "sigmoid")->linear_forward(A3,W4,b)--->Z----activation(sigmoid)--->A4

X  = image_matrix_input----- dim---->(4096, xxx)
W1  = (6, 4096)
linear_forward()
{W1*X+b}
W1*X-----dim-----> (6, 4096)*(4096, xxx)
xxx ---->training samples

in the case of one pic at a time xxx =1
(6, 4096)*(4096, 1)----> (6,1)------>dim(Z1)


A3 = predicted_output

Z1 = mat_add(mat_mul(X,W) ,b)
A1 = relu(Z1) // i think we should do a for loop to relu the whole matrix of Z1


implemntation

- receive X 
mult W1,X 
add b

get Z1
get A1


<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]



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

[!Huawei University Challenge](C:/Users/kalee/Desktop/huawei.png)



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



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.



<!-- CONTACT -->
## Contact


Khaled Alamin - [@LinkedIn](https://www.linkedin.com/in/khaled-alamin/)
Eyas Elhadi

Project Link: [https://github.com/your_username/repo_name](https://github.com/your_username/repo_name)



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
