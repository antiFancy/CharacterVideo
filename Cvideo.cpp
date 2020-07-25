#include "Cvideo.h"

Cvideo::Cvideo(const char* path)
{
	video.open(path);
	if (!video.isOpened())
	{
		std::cout << "视频读取失败!" << std::endl;
		getchar();
		exit(0);
	}
}

bool Cvideo::GetFrame()
{
	int count = 0;
	while(true)
	{
		Vframe.resize(count+1);
		video >> Vframe[count];
		if (Vframe[count].empty())
		{
			return true;
		}
		count++;
		Vcount++;
	}
	return false;
}

cv::Mat Cvideo::Oframe(int count)
{
    return Vframe[count];
}

int Cvideo::GetSize()
{
	return Vframe.size();
}

Cdata::Cdata(int a)
{
	Vdata.resize(a);
}

void Cdata::indata(cv::Mat data,int a)
{
	Vdata.resize(a * (data.rows) / 10);
	for (size_t row1 = 0; row1 < data.rows; row1 += 10)
	{
		//std::cout << Vdata[col1] << std::endl;
		//std::cout << Vdata[0][0] << std::endl;
		for (size_t col1 = 0; col1 < data.cols; col1 += 10)
		{
			cv::Scalar color = data.at<cv::Vec3b>(row1, col1);//Vec3b
			if (color[0] >= 0 && color[0] <= 25)
			{
				Vdata[a].push_back("@@");
			}
			else if (color[0] >= 25 && color[0] <= 50)
			{
				Vdata[a].push_back("##");
			}
			else if (color[0] >= 50 && color[0] <= 75)
			{
				Vdata[a].push_back("%%");
			}
			else if (color[0] >= 75 && color[0] <= 100)
			{
				Vdata[a].push_back("??");
			}
			else if (color[0] >= 100 && color[0] <= 125)
			{
				Vdata[a].push_back("==");
			}
			else if (color[0] >= 125 && color[0] <= 150)
			{
				Vdata[a].push_back("++");
			}
			else if (color[0] >= 150 && color[0] <= 175)
			{
				Vdata[a].push_back("::");
			}
			else if (color[0] >= 175 && color[0] <= 200)
			{
				Vdata[a].push_back("--");
			}
			else
			{
				Vdata[a].push_back("..");
			}
			//std::cout << Vdata[col1] << std::endl;
		}
		//sum++;
		Vdata[a].push_back("\n");
	}
}

void Cdata::ShowData(int count)
{
	std::cout<<"总量>>>>" << count <<">>>>回车继续!"<< std::endl;
	getchar();
	getchar();
	
	system("cls");
	screenshot ScShot;
	for (int ix = 0; ix < count; ix++)
	{
		for (int jx = 0; jx < Vdata[ix].size(); jx++)
		{
			std::cout << Vdata[ix][jx];
		}
		ScShot.screen();
		ScShot.HBitmapToMat(ScShot.bmp[ix]);
		system("cls");
	}
	int Vwidth = GetSystemMetrics(SM_CXSCREEN);
	int Vheight = GetSystemMetrics(SM_CYSCREEN);
	//std::cout << "生成中>>>>";
	cv::VideoWriter _writer;
	_writer.open("C:/Users/Fancy/Desktop/out.mp4", /*cv::VideoWriter::fourcc('M', 'J', 'P', 'G')*/-1, 15.0, cv::Size(Vwidth, Vheight), true);
	for (int i = 0; i < ScShot.Sshot.size(); i++)
	{
		std::cout << "生成中>>>>";
		std::cout << i << "/"<< ScShot.Sshot.size() << std::endl;
		_writer.write(ScShot.Sshot[i]);
		system("cls");
		//cv::waitKey(25);
	}
	std::cout << "Width:" << Vwidth << std::endl << "Height:" << Vheight << std::endl;
	std::cout << "out complete!" << std::endl;
}

void screenshot::screen()
{
	HDC hScreen = CreateDC(L"DISPLAY", NULL, NULL, NULL);
	HDC hCompDC = CreateCompatibleDC(hScreen);
	int sWidth = GetSystemMetrics(SM_CXSCREEN);
	int sHeight = GetSystemMetrics(SM_CYSCREEN);
	hBmp = CreateCompatibleBitmap(hScreen, sWidth, sHeight);
	hOld = (HBITMAP)SelectObject(hCompDC, hBmp);
	BitBlt(hCompDC, 0, 0, sWidth, sHeight, hScreen, 0, 0, SRCCOPY);
	SelectObject(hCompDC, hOld);
	bmp.push_back(hBmp);
	DeleteDC(hScreen);
	DeleteDC(hCompDC);

}

bool screenshot::HBitmapToMat(HBITMAP& _hbmp)
{
	BITMAP bmp;
	GetObject(_hbmp, sizeof(BITMAP), &bmp);
	int nChannels = bmp.bmBitsPixel == 1 ? 1 : bmp.bmBitsPixel / 8;
	int depth = bmp.bmBitsPixel == 1 ? IPL_DEPTH_1U : IPL_DEPTH_8U;
	cv::Mat v_mat;
	v_mat.create(cvSize(bmp.bmWidth, bmp.bmHeight), CV_MAKETYPE(CV_8U, nChannels));
	GetBitmapBits(_hbmp, bmp.bmHeight * bmp.bmWidth * nChannels, v_mat.data);
	Sshot.push_back(v_mat);
	return TRUE;
}
