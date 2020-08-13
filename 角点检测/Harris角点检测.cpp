Mat img = imread("D:\\1\\2.jpg");
imshow("src", img);
Mat result = img.clone();
Mat gray;
cvtColor(img, gray, CV_BGR2GRAY);

Mat dst;
Mat corner_img;
cornerHarris(gray, corner_img, 2, 3, 0.04);
imshow("corner", corner_img);
threshold(corner_img, dst, 0.005, 255, CV_THRESH_BINARY);
imshow("dst", dst);

int rowNumber = gray.rows;  //获取行数
int colNumber = gray.cols;  //获取每一行的元素
cout<<rowNumber<<endl;
cout<<colNumber<<endl;
cout<<dst.type()<<endl;


for(int i = 0; i<rowNumber; i++)
{
   for(int j = 0; j<colNumber; j++)
   {
       if(dst.at<float>(i, j) == 255)
       {
           circle(result, Point(j, i), 5, Scalar(0, 0, 255), 2, 8);
       }
   }
}

imshow("result", result);
waitKey(0);

