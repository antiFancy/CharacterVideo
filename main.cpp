#include"Cvideo.h"

#include<Windows.h>

using namespace std;
int main()
{
	CONSOLE_FONT_INFOEX cfie;
	cfie.cbSize = sizeof(cfie);
	cfie.dwFontSize.Y = 9;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &cfie);
	string path;
	cout << "��Ƶ·��:";
	cin >> path;
	Cvideo video(path.c_str());
	video.GetFrame();
	Cdata data(video.Vcount);
	int count = 1;
	while (1)
	{
		cout << "��������:" << count<<"/"<<video.Vcount << endl;
		//cv::namedWindow("video", cv::WINDOW_NORMAL);
		if (count == video.GetSize()-1)break;
		data.indata(video.Oframe(count),count);
		//Sleep(100);
		count++;
		system("cls");
		//cv::waitKey(NULL);
		//cv::destroyWindow("video");
	}
	cout << "�������!" << endl;
	data.ShowData(video.Vcount);
	return 0;

}