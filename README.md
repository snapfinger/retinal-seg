# Retinal-Vessel-Segmentaion
**Part 1: top-hat transformation**

Two definitions:													
- top-hat: the difference between the original image and its opening														
- opening: first erosion and then dilation

In this code, the top-hat is implemented by min-max filter, i.e. erosion is min filter, dilation is max filter			

Command: tophat if=inputFileName of=outputFileName s=structureSize          
(s=10 works fine (at least on first case))

Reference Paper:
Rossant, Florence, et al. "A morphological approach for vessel segmentation in eye fundus images, with quantitative evaluation." Journal of Medical Imaging and Health Informatics 1.1 (2011): 42-49.
