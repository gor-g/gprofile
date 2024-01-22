# gprofile

A command line tool to out square profile pictures from an image using the biggest face detected in the image (Assuming that people take their pictures while standing in the foreground). 



The Haar cascade face detector is taken from https://github.com/opencv/opencv/tree/4.x/data/haarcascades . The XML is converted into a C array to improve portability. To use the latest XML file from OpenCV `data` you can download it from the above link, then convert it in to a C array with the command 

```bash
xxd -i haarcascade_frontalface_default.xml > haarcascade.hpp
```

