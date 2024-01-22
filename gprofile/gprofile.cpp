#include <opencv2/opencv.hpp>
#include "haarcascade.hpp"

cv::Mat cropLargestFace(const std::string& imagePath, int size) {
    // Load the Haar cascade
    cv::FileStorage fs;
    fs.open(cv::String(reinterpret_cast<const char*>(haarcascade_frontalface_default_xml), haarcascade_frontalface_default_xml_len), cv::FileStorage::READ | cv::FileStorage::MEMORY);
    cv::CascadeClassifier faceCascade;
    faceCascade.read(fs.getFirstTopLevelNode());

    // Read the image
    cv::Mat img = cv::imread(imagePath);
    if (img.empty()) {
        std::cout << "Error: the image has been not loaded." << std::endl;
        return cv::Mat();
    }

    // Convert the image to grayscale
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

    // Detect faces
    std::vector<cv::Rect> faces;
    faceCascade.detectMultiScale(gray, faces, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

    // Find the largest face
    auto largestFace = std::max_element(faces.begin(), faces.end(), [](const cv::Rect& a, const cv::Rect& b) {
        return a.area() < b.area();
    });

    // Calculate the size of the new rectangle
    int maxDimension = std::max(largestFace->width, largestFace->height) * 2.0;
    cv::Rect newRect(largestFace->x + largestFace->width / 2 - maxDimension / 2,
                    largestFace->y + largestFace->height / 2 - maxDimension / 2,
                    maxDimension, maxDimension);

    // Make sure the new rectangle is within the bounds of the image
    newRect &= cv::Rect(0, 0, img.cols, img.rows);

    // Crop the image to the new rectangle
    cv::Mat croppedImage = img(newRect);

    // After cropping the image to the new rectangle, resize it to the specified size
    if (croppedImage.cols > size || croppedImage.rows > size) {
        cv::resize(croppedImage, croppedImage, cv::Size(size, size));
    }

    // Return the cropped image
    return croppedImage;
}

int main(int argc, char* argv[]) {
    // Initialize the input image path, output image path, and size with their default values
    std::string inputImagePath;
    std::string outputImagePath = "output.jpg";
    int size = 512;

    // Parse the arguments
    for (int i = 1; i < argc; i += 2) {
        if (i + 1 < argc) { // Make sure we haven't finished parsing already
            if (std::string(argv[i]) == "--input") {
                inputImagePath = argv[i + 1];
            } else if (std::string(argv[i]) == "--output") {
                outputImagePath = argv[i + 1];
            } else if (std::string(argv[i]) == "--size") {
                size = std::stoi(argv[i + 1]);
            } else {
                std::cout << "Unknown argument: " << argv[i] << std::endl;
                return 1;
            }
        }
    }

    // Check if the input image path was provided
    if (inputImagePath.empty()) {
        std::cout << "Usage: " << argv[0] << " --input <input_image> [--output <output_image>] [--size <size>]" << std::endl;
        return 1;
    }

    // Call the function
    cv::Mat croppedFace = cropLargestFace(inputImagePath, size);

    // Save the cropped image
    cv::imwrite(outputImagePath, croppedFace);

    return 0;
}