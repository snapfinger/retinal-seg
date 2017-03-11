# Retinal-Vessel-Segmentaion
**Part 1: top-hat transformation**

Two definitions:													
- top-hat: the difference between the original image and its opening														
- opening: first erosion and then dilation

In this code, the top-hat is implemented by min-max filter, i.e. erosion is min filter, dilation is max filter							
