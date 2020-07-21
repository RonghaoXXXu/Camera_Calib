//------------------------开始检验！---------------------------------
    cout<<"开始检验！"<<endl;
    double total_err = 0.0;         /* 所有图像的平均误差的总和 */
    double err = 0.0;               /* 每幅图像的平均误差 */
    cout << "每幅图像的标定误差：\n";

    for (int i = 0; i<image_count; i++)
    {
         vector<Point3f> tempPointSet = object_points_seq[i];

         /* 通过得到的摄像机内外参数，对空间的三维点进行重新投影计算，得到新的投影点 */
         projectPoints(tempPointSet, rvecsMat[i], tvecsMat[i], cameraMatrix, distCoeffs, check_points_buf);

         /* 计算新的投影点和旧的投影点之间的误差*/
         vector<Point2f> tempImagePoint = image_points_seq[i];
         Mat tempImagePointMat = Mat(1, tempImagePoint.size(), CV_32FC2);
         Mat check_points_bufMat = Mat(1, check_points_buf.size(), CV_32FC2);

         for (size_t j = 0; j < tempImagePoint.size(); j++)
         {
             check_points_bufMat.at<Vec2f>(0, j) = Vec2f(check_points_buf[j].x, check_points_buf[j].y);
             tempImagePointMat.at<Vec2f>(0, j) = Vec2f(tempImagePoint[j].x, tempImagePoint[j].y);
         }
         err = norm(check_points_bufMat, tempImagePointMat, NORM_L2);
         total_err += err /= point_counts[i];
         cout << "第" << i + 1 << "幅图像的平均误差：" << err << "像素" << endl;
    }
//------------------------图片矫正！---------------------------------
    cout<<"图片矫正！"<<endl;
    Mat mapx = Mat(Imgs[0].size(), CV_32FC1);
    Mat mapy = Mat(Imgs[0].size(), CV_32FC1);
    Mat R = Mat::eye(3, 3, CV_32F);      //单位矩阵
    //计算出对应的映射表
    initUndistortRectifyMap(cameraMatrix, distCoeffs, R, cameraMatrix, Imgs[0].size(), CV_32FC1, mapx, mapy);
    //第三个参数R，可选的输入，是第一和第二相机坐标之间的旋转矩阵；
    //第四个参数newCameraMatrix，输入的校正后的3X3摄像机矩阵；
    //第五个参数size，摄像机采集的无失真的图像尺寸；
    //第六个参数m1type，定义map1的数据类型，可以是CV_32FC1或者CV_16SC2；
    //第七个参数map1和第八个参数map2，输出的X / Y坐标重映射参数；

    for (size_t i = 0; i!= Imgs.size(); i++)
    {
        Mat imageSource = Imgs[i];
        Mat newimage = Imgs[i].clone();
        Mat newimage1 = Imgs[i].clone();

        //方法一：使用initUndistortRectifyMap和remap两个函数配合实现。
        //initUndistortRectifyMap用来计算畸变映射，remap把求得的映射应用到图像上。



        remap(imageSource, newimage, mapx, mapy, INTER_LINEAR);
        //第五个参数interpolation，定义图像的插值方式；
        //第六个参数borderMode，定义边界填充方式；

        //方法二：使用undistort函数实现
        undistort(imageSource, newimage1, cameraMatrix, distCoeffs);
        //第五个参数newCameraMatrix，默认跟cameraMatrix保持一致；

        //输出图像
        string str = "/home/feyker/Pictures/CC-Result/" + to_string(i + 1) + ".jpg";
        string str1 = "/home/feyker/Pictures/CC-Result/" + to_string(i + 1) + "N.jpg";
        //string str = "d:\\" + to_string(i + 1) + ".jpg";
        imwrite(str, newimage);
        imwrite(str1, newimage1);
    }
    cout << "Hello World!" << endl;
    fout << "相机内参数矩阵：" << endl;
    fout << cameraMatrix << endl << endl;
    fout << "畸变系数：\n";
    fout << distCoeffs << endl << endl << endl;





立体匹配算法。
SGBM：
    sgbm->setP1(8 * cn*sgbmWinSize*sgbmWinSize);
    sgbm->setP2(32 * cn*sgbmWinSize*sgbmWinSize);
    sgbm->setMinDisparity(0);
    sgbm->setNumDisparities(numberOfDisparities);
    sgbm->setUniquenessRatio(10);
    sgbm->setSpeckleWindowSize(100);
    sgbm->setSpeckleRange(32);
    sgbm->setDisp12MaxDiff(1);

    sgbm->compute(rectifyImageL,rectifyImageR,disparity_L);
    disparity_L.convertTo(disparity_L,CV_32F,1.0/16);
    cvNormalize(&disparity_L,&dis8U_L,0, 255, CV_8UC1, NULL);

    sgbm->setMinDisparity(-numberOfDisparities);
    sgbm->setNumDisparities(numberOfDisparities);
    sgbm->compute(rectifyImageL,rectifyImageR,disparity_R);
    disparity_R.convertTo(disparity_R,CV_32F,1.0/16);
    cvNormalize(&disparity_R,&dis8U_R,0, 255, CV_8UC1, NULL);


    cv_show("disparityL",dis8U_L);
    cv_show("disparityR",dis8U_R);




OnMouse
 namedWindow("disparity", CV_WINDOW_AUTOSIZE);
    // 创建SAD窗口 Trackbar
    createTrackbar("BlockSize:\n", "disparity", &blockSize, 8, stereo_match);
    // 创建视差唯一性百分比窗口 Trackbar
    createTrackbar("UniquenessRatio:\n", "disparity", &uniquenessRatio, 50, stereo_match);
    // 创建视差窗口 Trackbar
    createTrackbar("NumDisparities:\n", "disparity", &numDisparities, 16, stereo_match);
    //鼠标响应函数setMouseCallback(窗口名称, 鼠标回调函数, 传给回调函数的参数，一般取0)
    setMouseCallback("disparity", onMouse, 0);
