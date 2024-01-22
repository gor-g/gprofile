# gprofile

A command line tool to crop out square profile pictures from an image using the biggest face detected in the image (Assuming that people take their pictures while standing in the foreground). 

## Install

To install on Debain based distros, download `gprofile.deb` 
```bash
sudo dpkg -i path/to/gprofile.deb
```

## Maintenance note

The Haar cascade face detector is taken from https://github.com/opencv/opencv/tree/4.x/data/haarcascades . The XML is converted into a C array to improve portability. To use the latest XML file from OpenCV `data` you can download it from the above link, then convert it in to a C array with the command 

```bash
xxd -i haarcascade_frontalface_default.xml > haarcascade.hpp
```

## TODO

Add filters for:
- Color improvement.
- Skin imperfection removal.

Propose a manual selection when multiple faces are detected. 
