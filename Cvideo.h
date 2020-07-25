#pragma once
#ifndef CVIDEO_H
#define CVIDEO_H
#include<opencv2/opencv.hpp>
#include<vector>
#include<string>
#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/photo/photo_c.h>
#include<opencv/cv.h>
#include<opencv/highgui.h>
//#include<cv.h>
#include<Windows.h>
#include<opencv2/video/tracking_c.h>
#include<opencv2/objdetect/objdetect_c.h>
class Cvideo
{
private:
	cv::VideoCapture video;
	std::vector<cv::Mat> Vframe;
public:
	//Cvideo();
	int Vcount;
	Cvideo(const char* path);
	bool GetFrame();
	cv::Mat Oframe(int count);
	int GetSize();
};
/************************************************************/
class Cdata
{
	int sum = 1;
	int _Width=0;
	int _Height=0;
private:
	std::vector<std::vector<std::string>> Vdata;
public:
	Cdata(int a);
	void indata(cv::Mat data,int a);
	void ShowData(int count);
};
class screenshot
{
	HBITMAP hBmp;
	HBITMAP hOld;
public:
	std::vector<HBITMAP> bmp;
	std::vector<cv::Mat> Sshot;
	void screen();
	bool HBitmapToMat(HBITMAP& _hbmp);
};
#endif