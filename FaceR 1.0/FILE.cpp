#include"stdafx.h"
#include "FILE.h"
using namespace std;
using namespace cv;

FileManager::FileManager()
{}

FileManager::~FileManager()
{}

bool FileManager::initial(void)
{
	makeDir("./user");

	string filename = "./user/persons.log";
	fstream fin(filename, ios::in);
	int count;
	string scount;

	if (!fin.is_open())
		return false;
	getline(fin, scount);
	count = atoi(scount.c_str());
	while (count > 0)
	{
		string temp;
		getline(fin, temp);
		pids.push_back(temp);
		count--;
	}
	fin.close();
	return true;
}

bool FileManager::close(void)
{
	string filename = "./user/persons.log";
	fstream fout(filename, ios::out);
	int count = pids.size();

	if (!fout.is_open())
		return false;
	fout << count << endl;
	count--;
	while (count >= 0)
	{
		string tmp = pids[count];
		fout << tmp << std::endl;
		count--;
	}
	fout.close();
	return true;
}

bool FileManager::makeDir(string Dir)
{
	if (_mkdir(Dir.c_str()) == 0)
	{
		std::cout << "Create folder success!" << std::endl;
		return true;
	}
	else
		return false;
}

bool FileManager::writeInfo(personalInfo &stuInfo)
{
	stuInfo.perDir = "./user/" + string(stuInfo.sid);
	string filename = stuInfo.perDir + "/" + stuInfo.sid + ".person";

	if (makeDir(stuInfo.perDir))
	{
		std::cout << "Add a new person!" << std::endl;
		stuInfo.num_spic = 0;
		stuInfo.num_epic = 0;
		pids.push_back(stuInfo.sid);
		if (!makeDir(stuInfo.perDir + "/sources"))
			return false;
		if (!makeDir(stuInfo.perDir + "/egifaces"))
			return false;
	}

	fstream fout(filename.c_str(), ios::out);

	if (!fout.is_open())
		return false;
	fout << stuInfo.sid << std::endl;
	fout << stuInfo.num_spic << std::endl;
	fout << stuInfo.num_epic << std::endl;
	fout << stuInfo.name << std::endl;
	fout.close();
	return true;
}

bool FileManager::getStuinfo(personalInfo &stuInfo, string &sid)
{
	string filename = "./user/" + sid + "/" + sid + ".person";
	fstream fin(filename, ios::in);

	if (!fin.is_open())
		return false;

	string temp;

	getline(fin, stuInfo.sid);
	getline(fin, temp);
	cout << temp << endl;
	stuInfo.num_spic = atoi(temp.c_str());
	getline(fin, temp);
	stuInfo.num_epic = atoi(temp.c_str());
	getline(fin, stuInfo.name);
	stuInfo.perDir = "./user/" + sid;

	return true;
}

bool FileManager::transferImage(string &sourceFile, string &targetFile)
{
	if (sourceFile.empty())
		return false;
	if (targetFile.empty())
		return false;
	fstream filein(sourceFile.c_str(), ios::in | ios::binary);
	if (!filein.is_open())
		return false;
	filein.seekg(0, ios::end);
	int file_length = filein.tellg();
	filein.seekg(0, ios::beg);
	imageBuffer = new char[file_length + 1];
	filein.read(imageBuffer, file_length);
	filein.close();

	fstream fileout(targetFile.c_str(), ios::out | ios::binary);
	if (!fileout.is_open())
	{
		delete[] imageBuffer;
		return false;
	}
	fileout.write(imageBuffer, file_length);
	fileout.close();
	delete[] imageBuffer;
	return true;
}

bool FileManager::generateSourceCSV(personalInfo &stuInfo, vector<string> filetypes)
{
	getStuinfo(stuInfo, stuInfo.sid);
	string filename = stuInfo.perDir + "/sources/source.csv";
	fstream fout(filename, ios::out | ios::app);
	if (!fout.is_open())
		return false;
	for (int i = 0; i < filetypes.size(); i++)
	{
		char tempNum[3];
		_itoa_s(stuInfo.num_spic - filetypes.size() + i, tempNum, 10);
		string outContent = stuInfo.perDir + "/sources/" + string(tempNum) + "." + filetypes.at(i) + ";" + string(stuInfo.sid);
		fout << outContent << endl;
	}
	fout.close();
	return true;
}

bool FileManager::generateEgiFaceCSV(personalInfo &stuInfo, string filetype)
{
	getStuinfo(stuInfo, stuInfo.sid);
	string filename = stuInfo.perDir + "/egifaces/egi.csv";
	fstream fout(filename, ios::out | ios::app);
	if (!fout.is_open())
		return false;
	char tempNum[3];
	_itoa_s(stuInfo.num_epic - 1, tempNum, 10);
	string outContent = stuInfo.perDir + "/egifaces/" + string(tempNum) + "." + filetype + ";" + string(stuInfo.sid);
	fout << outContent << endl;
	fout.close();
	return true;
}

bool FileManager::loadImages(personalInfo &stuInfo, vector<string> fileRoutes)
{
	int start = stuInfo.num_spic;
	int ri = fileRoutes.size();
	vector<string> filetypes;

	for (int i = 0; i < ri; i++)
	{
		string fileRoute = fileRoutes.at(i);
		int pos = fileRoute.size() - 1;
		string fileType;
		do
		{
			fileType += fileRoute[pos];
			pos--;
		} while (fileRoute[pos] != '.');
		reverse(fileType.begin(), fileType.end());
		char snum[3];
		_itoa_s(start + i, snum, 10);
		string targetFile = stuInfo.perDir + "/sources/" + string(snum) + "." + fileType;
		transferImage(fileRoute, targetFile);
		filetypes.push_back(fileType);
	}
	stuInfo.num_spic += ri;
	if (!writeInfo(stuInfo))
		return false;
	if (!generateSourceCSV(stuInfo, filetypes))
		return false;
	return true;
}

void FileManager::getSourcesCsvRoute(string &sourceCSVRoute, personalInfo &stuInfo)
{
	sourceCSVRoute = stuInfo.perDir + "/sources/source.csv";
}

void FileManager::getEgiFaceCsvRoute(string &egifacesCSVRoute, personalInfo &stuInfo)
{
	egifacesCSVRoute = stuInfo.perDir + "/egifaces/egi.csv";
}

bool FileManager::getPersonIndex(vector<string> &personIDs)
{
	fstream fin("./user/persons.log", ios::in);

	if (!fin.is_open())
		return false;

	int ri;
	string temp;

	personIDs.clear();
	fin >> temp;
	ri = atoi(temp.c_str());
	for (ri = ri - 1; ri >= 0; ri--)
	{
		string tmp;
		fin >> tmp;
		personIDs.push_back(tmp);
		pids.push_back(tmp);
	}
	return true;
}

bool FileManager::writeMATtoSource(personalInfo &stuInfo, Mat &source)
{
	char tempNum[3];
	_itoa_s(stuInfo.num_spic, tempNum, 10);
	string fileName = stuInfo.perDir + "/sources/" + string(tempNum) + ".jpg";
	stuInfo.num_spic++;
	if (!writeInfo(stuInfo))
		return false;
	IplImage savedImage = IplImage(source);
	cvSaveImage(fileName.c_str(), &savedImage);
	vector<string> tempFileType;
	tempFileType.push_back("jpg");
	generateSourceCSV(stuInfo, tempFileType);
	return true;
}

bool FileManager::writeMATtoEgiFace(personalInfo &stuInfo, Mat &egiface)
{
	char tempNum[3];
	_itoa_s(stuInfo.num_epic, tempNum, 10);
	string fileName = stuInfo.perDir + "/egifaces/" + string(tempNum) + ".jpg";
	stuInfo.num_epic++;
	if (!writeInfo(stuInfo))
		return false;
	IplImage savedImage = IplImage(egiface);
	cvSaveImage(fileName.c_str(), &savedImage);
	generateEgiFaceCSV(stuInfo, "jpg");
}

/*
bool FileManager::loadImages_test(vector<string> fileRoutes)
{
int start = 10;
int ri = fileRoutes.size();
for (int i = 0; i < ri; i++)
{
string fileRoute = fileRoutes.at(i);
int pos = fileRoute.size() - 1;
string fileType;
do
{
fileType += fileRoute[pos];
pos--;
} while (fileRoute[pos] != '.');
reverse(fileType.begin(), fileType.end());
char snum[3];
_itoa_s(start + i, snum, 10);
string targetFile = "./user/" + string(snum) + "." + fileType;
transferImage(fileRoute, targetFile);
}
return true;
}
*/
