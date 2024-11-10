#include <iostream>
#include <vector>
#include <omp.h> //OpenMP library
#include <opencv2/opencv.hpp> //image processing library OpenCV

using namespace std;
using namespace cv;

// Function to perform edge detection on an image using the Canny edge detection technique
Mat edgeDetection(const Mat &image) {
    Mat edges;
    Canny(image, edges, 100, 200); //using threshold 100, 200 for edge detection
    return edges;
}

vector<Point> getStarCoordinates(const Mat &edges, int threshold) {// functions to store located //coordinates of stars from canny algorithms in a vector 
    vector<Point> starCoords;  // Vector to store the coordinates of the detected stars
    // Loop through every pixel in the image
    for (int y = 0; y < edges.rows; y++) {
        for (int x = 0; x < edges.cols; x++) {
            if (edges.at<uchar>(y, x) > threshold) { // If the pixel value is greater than the threshold, //consider it as a star 
                starCoords.push_back(Point(x, y));
            }
        }
    }
    return starCoords;
}

Mat parallelPixelAveraging(const vector<Mat> &images) {// Function to average the pixel values of //multiple images
    // Create an empty image of the same size as the input images
    Mat averagedImage = Mat::zeros(images[0].size(), images[0].type());
    int numImages = images.size();

#pragma omp parallel for // processing them parallely
    for (int y = 0; y < averagedImage.rows; y++) {
        for (int x = 0; x < averagedImage.cols; x++) {
            Vec3d sum = Vec3d(0, 0, 0); // Initialize a vector to store the sum of pixel values for all images
            for (const Mat &img : images) {
                Vec3b pixel = img.at<Vec3b>(y, x);
                sum[0] += pixel[0]; //get the blue channel value
                sum[1] += pixel[1]; //get the green channel value
                sum[2] += pixel[2]; //get the red channel value
            }
            averagedImage.at<Vec3b>(y, x) = Vec3b(static_cast<uchar>(sum[0] / numImages), // averaging //all 3 channels
                                                  static_cast<uchar>(sum[1] / numImages),
                                                  static_cast<uchar>(sum[2] / numImages));
        }
    }

    return averagedImage;
}

int main() {
    double start, end;
    start = omp_get_wtime(); // Start timer
    vector<Mat> images;
    vector<Mat> colorImages;
    for (int i = 791; i <= 797; i++) { // load images to process {
        Mat img = imread("raw_data/IMG_0" + to_string(i) + ".jpg", IMREAD_COLOR);
        colorImages.push_back(img); // Add the color image to the colorImages vector
        Mat grayImg;
        cvtColor(img, grayImg, COLOR_BGR2GRAY); // Convert the color image to grayscale
        images.push_back(grayImg);              // Add the grayscale image to the images vector {using grayscale for easier processing}
    }

    vector<Mat> edgeImages(images.size()); // Vector to store edge-detected images
#pragma omp parallel for
    for (int i = 0; i < images.size(); i++) {
        edgeImages[i] = edgeDetection(images[i]); // edge detection on each image
    }

    vector<vector<Point>> allStarCoords(images.size()); // vector to store coordinates of each image	
#pragma omp parallel for
    for (int i = 0; i < edgeImages.size(); i++) {
        allStarCoords[i] = getStarCoordinates(edgeImages[i], 220);//using threshold 220
    }

    Mat finalImage = parallelPixelAveraging(colorImages);
    imwrite("final_output_ with_openmp.jpg", finalImage);
    cout << "Final image saved as 'final_output_ with_openmp.jpg'." << endl;
    end = omp_get_wtime(); // end timer
    cout << "Total execution time: " << end - start << " seconds" << endl;
    return 0;
}
