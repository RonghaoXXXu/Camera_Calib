#ifndef CALIB_H
#define CALIB_H

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


namespace calib {
//------------------------相机标定!--------------------------
    vector<Mat> Imgs_R;
    vector<Mat> Imgs_L;

    int image_count = 26;  /* 图像数量 */
    Size board_size = Size(4,5);    /* 标定板上每行、列的内角点数 */
    Size image_size;
    double patlen= 50.0 ; /* 标定板方格宽度（mm）*/

    vector<Point2f> imageR_points_buf;  /* 缓存角点及保存亚像素处理*/
    vector<vector<Point2f>> imageR_points_seq; /* 保存亚像素处理角点组 */

    vector<Point2f> imageL_points_buf;  /* 缓存角点及保存亚像素处理*/
    vector<vector<Point2f>> imageL_points_seq; /* 保存亚像素处理角点组 */

    vector<Point3f> object_points_buf;
    vector<vector<Point3f>> object_points_seq;

    Mat cameraMatrix_L=Mat(3,3,CV_32FC1,Scalar::all(0));/* 摄像机内参数矩阵 */
    Mat cameraMatrix_R=Mat(3,3,CV_32FC1,Scalar::all(0));
    Mat distCoeffs_L=Mat(1,5,CV_32FC1,Scalar::all(0)); /* 摄像机的5个畸变系数：k1,k2,p1,p2,k3 */
    Mat distCoeffs_R=Mat(1,5,CV_32FC1,Scalar::all(0));

    Mat Rec,T,E,F;//双目相机关系

    vector<Mat> rvecsMat_L;  /*L图像的旋转向量 */
    vector<Mat> tvecsMat_L; /*L图像的平移向量 */
    vector<Mat> rvecsMat_R;  /*R图像的旋转向量 */
    vector<Mat> tvecsMat_R; /*R图像的平移向量 */


    int Stereo_Calib();
//---------------------图像矫正及显示！--------------------------
    Mat Rl,Rr,Pl,Pr,Q,R;
    Mat mapLx, mapLy, mapRx, mapRy;     //映射表

    Mat grayImageL;
    Mat grayImageR;  //可以更换为摄像头实时采取的图像
    Mat rectifyImageL, rectifyImageR; //矫正图像gray统平台，优化资源部署，包括RTOS、Linux、Android、安全OS等；

    Mat disImg_L,disImg_R; //展示rgb纠正图像,£££立体匹配

    Rect validROI_L;    //图像校正之后，会对图像进行裁剪，这里的validROI就是指裁剪之后的区域
    Rect validROI_R;

    Mat canvas, canvasPart; //显示画布

    Rect ROI_L,ROI_R;

    int  Stereo_correct(Mat rgbImageL,Mat rgbImageR);
    void Stereo_display();
//---------------------立体匹配及测距！--------------------------

    Point origin;         //鼠标按下的起始点
    Rect  selection;      //定义矩形选框
    bool  selectObject = false;    //是否选择对象

    int numberOfDisparities =((image_size.width/8)+15) & -16;
    int SADWindowSize =9;
    int sgbmWinSize =SADWindowSize >0? SADWindowSize :3;
    int cn= 1;//gray

    Ptr<StereoBM> bm = StereoBM::create(16,4);

    Mat xyz;
    Mat disparity = Mat(image_size,CV_16S);
    Mat dis8U;

    void onMouse(int event, int x, int y, int, void*);
    void Stereo_match(int, void*);
    double  Stereo_distance(Rect ROI,Point pos);

//------------------------------------------------------------
    void cv_show(string name,Mat img);
    void Stereo_ALL(Mat rgbImageL,Mat rgbImageR,Rect ROI,Point pos);
}

void calib::Stereo_ALL(Mat rgbImageL, Mat rgbImageR, Rect ROI, Point pos){
    Stereo_Calib();
    Stereo_correct(rgbImageL,rgbImageR);
    Stereo_display();
    Stereo_match(0,0);
    Stereo_distance(ROI,pos);
}


void calib::onMouse(int event, int x, int y, int, void *){
        if (selectObject)
        {
            selection.x = MIN(x, origin.x);
            selection.y = MIN(y, origin.y);
            selection.width = std::abs(x - origin.x);
            selection.height = std::abs(y - origin.y);
        }

        switch (event)
        {
        case EVENT_LBUTTONDOWN:   //鼠标左按钮按下的事件
            origin = Point(x, y);
            selection = Rect(x, y, 0, 0);
            selectObject = true;
            cout << origin << "in world coordinate is: " << xyz.at<Vec3f>(origin) << endl;
            break;
        case EVENT_LBUTTONUP:    //鼠标左按钮释放的事件
            selectObject = false;
            if (selection.width > 0 && selection.height > 0)
                break;
        }
}

void calib::Stereo_match(int, void*){

    /*sgbm->setPreFilterCap(63);
    sgbm->setBlockSize(sgbmWinSize);
    sgbm->setP1(8*cn*sgbmWinSize*sgbmWinSize);
    sgbm->setP2(32*cn*sgbmWinSize*sgbmWinSize);
    sgbm->setMinDisparity(0);
    sgbm->setNumDisparities(numberOfDisparities);
    sgbm->setUniquenessRatio(10);
    sgbm->setSpeckleWindowSize(100);
    sgbm->setSpeckleRange(32);
    sgbm->setDisp12MaxDiff(-1);
    sgbm->setMode(StereoSGBM::MODE_SGBM);


    sgbm->compute(rectifyImageL,rectifyImageR,disparity);*/

    bm->setBlockSize(16);     //SAD窗口大小，5~21之间为宜
    bm->setROI1(validROI_L);
    bm->setROI2(validROI_R);
    bm->setPreFilterCap(31);
    bm->setMinDisparity(0);  //最小视差，默认值为0, 可以是负值，int型
    bm->setNumDisparities(64);//视差窗口，即最大视差值与最小视差值之差,窗口大小必须是16的整数倍，int型
    bm->setTextureThreshold(10);
    bm->setUniquenessRatio(12);//uniquenessRatio主要可以防止误匹配
    bm->setSpeckleWindowSize(100);
    bm->setSpeckleRange(32);
    bm->setDisp12MaxDiff(-1);
    bm->compute(rectifyImageL, rectifyImageR, disparity);//输入图像必须为灰度图*/




}

double calib::Stereo_distance(Rect ROI,Point pos)
{

    disparity.convertTo(dis8U, CV_8U, 255 / (numberOfDisparities*16.));
    reprojectImageTo3D(disparity, xyz, Q, true);
    xyz = xyz * 16;

    rectangle(dis8U,ROI,Scalar(0, 0, 255), 3, 8);

    cout << pos << "in world coordinate is: " << xyz.at<Vec3f>(pos) << endl;
    cout <<"Distance: "<< (double)xyz.at<Vec3f>(pos)[2] <<endl;
    cv_show("disparity",dis8U);

    return (double)xyz.at<Vec3f>(pos)[2];
}

void calib::Stereo_display(){

    double port;
    int w, h;

    port = 600. / MAX(image_size.width, image_size.height);

    w = cvRound(image_size.width * port);
    h = cvRound(image_size.height * port);

    canvas.create(h, w * 2, CV_8UC3);

    canvasPart = canvas(Rect(0, 0, w, h));
    resize(disImg_L, canvasPart, canvasPart.size(), 0, 0, INTER_AREA);
    //ROI_L=Rect(cvRound(validROI_L.x*port), cvRound(validROI_L.y*port),cvRound(validROI_L.width*port), cvRound(validROI_L.height*port));
    //rectangle(canvasPart, ROI_L, Scalar(0, 0, 255), 3, 8);


    canvasPart = canvas(Rect(w, 0, w, h));
    resize(disImg_R, canvasPart, canvasPart.size(), 0, 0, INTER_AREA);
    //ROI_R=Rect(cvRound(validROI_R.x*port), cvRound(validROI_R.y*port),cvRound(validROI_R.width*port), cvRound(validROI_R.height*port));
    //rectangle(canvasPart, ROI_R, Scalar(0, 0, 255), 3, 8);

    for (int i = 0; i < canvas.rows; i += 16)
        line(canvas, Point(0, i), Point(canvas.cols, i), Scalar(0, 255, 0), 1, 8);

    cv_show("rectified", canvas);

}

int calib::Stereo_correct(Mat rgbImageL,Mat rgbImageR)
{
    Rodrigues(Rec, R, noArray());

    stereoRectify(cameraMatrix_L, distCoeffs_L, cameraMatrix_R, distCoeffs_R,image_size, Rec, T, Rl,
           Rr, Pl, Pr, Q, CALIB_ZERO_DISPARITY, -1, image_size, &validROI_L , &validROI_R);

    initUndistortRectifyMap(cameraMatrix_L, distCoeffs_L, Rl, Pl, image_size, CV_32FC1, mapLx, mapLy);
    initUndistortRectifyMap(cameraMatrix_R, distCoeffs_R, Rr, Pr, image_size, CV_32FC1, mapRx, mapRy);

    cvtColor(rgbImageL, grayImageL, CV_BGR2GRAY);
    cvtColor(rgbImageR, grayImageR, CV_BGR2GRAY);

    remap(grayImageL, rectifyImageL, mapLx, mapLy, INTER_LINEAR);//GRAY
    remap(grayImageR, rectifyImageR, mapRx, mapRy, INTER_LINEAR);

    cvtColor(rectifyImageL,disImg_L, CV_GRAY2BGR);
    cvtColor(rectifyImageR,disImg_R, CV_GRAY2BGR);

    return 0;
}

int calib::Stereo_Calib()
{


//--------------------------开始提取角点！---------------------------------
    std::cout<<"开始提取角点！"<<endl;



    for(int i=0;i<image_count;i++){

        char nameL[64];
        char nameR[64];
        sprintf(nameL,"/home/feyker/Pictures/right/right00%.2d.jpg",i);
        sprintf(nameR,"/home/feyker/Pictures/left/left00%.2d.jpg",i);

        Mat Img_L=imread(nameL);
        Mat Img_R=imread(nameR);
        Imgs_L.push_back(Img_L);
        Imgs_R.push_back(Img_R);

        cvtColor(Img_L, Img_L, CV_BGR2GRAY);
        cvtColor(Img_R, Img_R, CV_BGR2GRAY);

        image_size=Img_L.size();

        findChessboardCorners(Img_L,board_size,imageL_points_buf);
        findChessboardCorners(Img_R,board_size,imageR_points_buf);

        find4QuadCornerSubpix(Img_L,imageL_points_buf,Size(3,3));
        cornerSubPix(Img_L,imageL_points_buf,Size(3,3),Size(-1,-1),
                    TermCriteria(CV_TERMCRIT_ITER + CV_TERMCRIT_EPS, 30, 0.01));
        find4QuadCornerSubpix(Img_R, imageR_points_buf,Size(3,3));
        cornerSubPix(Img_R, imageR_points_buf,Size(3,3),Size(-1,-1),
                    TermCriteria(CV_TERMCRIT_ITER + CV_TERMCRIT_EPS, 30, 0.01));

        imageL_points_seq.push_back(imageL_points_buf);
        imageR_points_seq.push_back(imageR_points_buf);

        for (int i = 0; i < board_size.height; i++) {
            for (int j = 0; j < board_size.width; j++) {
                /* 假设标定板放在世界坐标系中z=0的平面上, 且均相同。*/
                object_points_buf.push_back(Point3f((float)j,(float)i,0)* calib::patlen);
            }
        }
        object_points_seq.push_back(object_points_buf);
        vector<Point3f>().swap(object_points_buf);

        std::cout<<"第"<< i+1 <<"组图片提取完毕！"<<endl;
    }

//-----------------------------开始标定！------------------------------
    cout<<"开始标定！"<<endl;
    calibrateCamera(object_points_seq,imageL_points_seq,
                    image_size,cameraMatrix_L,distCoeffs_L,rvecsMat_L,tvecsMat_L, CV_CALIB_FIX_K3);
    calibrateCamera(object_points_seq,imageR_points_seq,
                    image_size,cameraMatrix_R,distCoeffs_R,rvecsMat_R,tvecsMat_R, CV_CALIB_FIX_K3);

    double rms= stereoCalibrate(object_points_seq,imageL_points_seq,imageR_points_seq,cameraMatrix_L,
                    distCoeffs_L,cameraMatrix_R,distCoeffs_R,image_size,Rec,T,E,F,true);

    cout << "Stereo Calibration done with RMS error = " << rms << endl;
    cout<<"双目相机标定结束！"<<endl;

    return 0;

}

void calib::cv_show(string name,Mat img){
    imshow(name,img);
    waitKey(0);
}




#endif // CALIB_H
