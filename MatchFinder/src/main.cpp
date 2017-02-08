// sensorFile.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iomanip>

#include "keyPoint.h"
#include "imageHelper.h"
#include "scannedScene.h"
#include "globalAppState.h"

int main(int argc, char* argv[])
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	//_CrtSetBreakAlloc(1042);
	try {
		const std::string fileNameDescGlobalApp = "zParametersDefault.txt";
		GAS::loadGlobalAppState(fileNameDescGlobalApp);
		std::cout << std::endl;

		const std::string srcPath = GAS::get().s_path;
		Directory rootDir(srcPath);
		std::cout << "found " << rootDir.getDirectories().size() << " scenes " << std::endl;

		for (size_t dirIdx = 0; dirIdx < rootDir.getDirectories().size(); dirIdx++) {
			const std::string& s = rootDir.getDirectories()[dirIdx];
			if (s == "archive") continue;

			std::cout << "Loading Scene: " << s << std::endl;
			const std::string path = srcPath + "/" + s;
			 
			ScannedScene ss(path, s);
			ss.findKeyPoints();
			ss.matchKeyPoints();
			//ss.saveMatches("test.txt");

			ss.visulizeMatches(3);

			if (GAS::get().s_maxNumScenes > 0 && dirIdx + 1 >= GAS::get().s_maxNumScenes) break;
		}

	}
	catch (const std::exception& e)
	{
		MessageBoxA(NULL, e.what(), "Exception caught", MB_ICONERROR);
		exit(EXIT_FAILURE);
	}
	catch (...)
	{
		MessageBoxA(NULL, "UNKNOWN EXCEPTION", "Exception caught", MB_ICONERROR);
		exit(EXIT_FAILURE);
	}
	
	std::cout << "<press key to continue>" << std::endl;
	getchar();
	return 0;
}

