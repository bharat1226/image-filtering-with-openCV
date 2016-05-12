# image-filtering-with-openCV
This project implements to:
- load images from a directory   (images)
- load a filter from a text file (filter.txt)
- apply the filter to each image
- save each output image into another directory (output)

---

This project code will rely on the OpenCV and Boost libraries ONLY  

Text file filter.txt is loaded that contains the filter mask which is applied to images.  
This file will have the following format:  

    <rows> <columns>  
    <H/ L>  
    <mask values>  

For example, a (3 by 3) Gaussian filter would look like this:

    3 3  
    L  
    1 2 1  
    2 4 2  
    1 2 1

The &lt;H/L&gt; part will either be H = high-pass filter or L = low-pass filter.  

Assumption:  the filters have odd-numbered sides.

The directory path program will save the processed images (e.g., dstDir)  

    imageFiltering ./images ./filter.txt ./output  
    
OpenCV functions are implemented in this project for filtering
