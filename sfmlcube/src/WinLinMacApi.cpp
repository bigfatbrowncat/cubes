// Global includes/methods

#include <sstream>
#include <string>

#include "Logger.h"
#include "WinLinMacApi.h"

using namespace std;

string simpleLocateResource(const string& path, const string& filename)
{
	stringstream ss;
	ss << path << "/" << filename;

	stringstream ss2;
	ss2 << "assuming resource is in the current directory: " << ss.str();
	sfmlcubes::Logger::DEFAULT.logInfo(ss2.str());

	return ss.str();
}


#ifdef __APPLE__
// MacOS X includes/methods

#include </usr/include/sys/syslimits.h>

#include <CoreFoundation/CFBundle.h>

string WinLinMacApi::locateResource(const string& path, const string& filename)
{
	string res = "";
	CFBundleRef mainBundle = CFBundleGetMainBundle();
	if (mainBundle)
	{
		stringstream ss;
		ss << "locating resource " << filename << "; path: " << path;
		sfmlcubes::Logger::DEFAULT.logInfo(ss.str());

		CFStringRef cfFileName = CFStringCreateWithCString(NULL, filename.c_str(), kCFStringEncodingASCII);
		CFStringRef cfPath = CFStringCreateWithCString(NULL, path.c_str(), kCFStringEncodingASCII);

		CFURLRef resourceURL = CFBundleCopyResourceURL(mainBundle, cfFileName, NULL, cfPath);
		if (resourceURL)
		{
			char fileurl[PATH_MAX + 1];
			if (CFURLGetFileSystemRepresentation(resourceURL, true, (UInt8*)fileurl, PATH_MAX))
			{
				stringstream ss;
				ss << "resource found in " << fileurl;
				sfmlcubes::Logger::DEFAULT.logInfo(ss.str());

				res = fileurl;
			}
			else
			{
				res = simpleLocateResource(path, filename);

				stringstream ss;
				ss << "resource not found. Trying " << res;
				sfmlcubes::Logger::DEFAULT.logInfo(ss.str());
			}
			CFRelease(resourceURL);
		}
		else
		{
			res = simpleLocateResource(path, filename);

			stringstream ss;
			ss << "resource not found. Trying " << res;
			sfmlcubes::Logger::DEFAULT.logInfo(ss.str());
		}
		CFRelease(cfFileName);
		CFRelease(cfPath);
	}
	else
	{
		sfmlcubes::Logger::DEFAULT.logInfo("smpl");		// If bundle isn't found, just try to load the resource
		// from the current directory
		res = simpleLocateResource(path, filename);
	}
	return res;
}

void WinLinMacApi::setMainWindowIcon(const sf::Window& win)
{
	// We do nothing here for OS X cause it loads the icon from the bundle
}

#elif __WIN32__

// Win32 includes/methods
#include <windows.h>
#include <direct.h>
#define GetCurrentDir _getcwd

BOOL FileExists(string szPath)
{
  DWORD dwAttrib = GetFileAttributes(szPath.c_str());

  return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
         !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

string WinLinMacApi::locateResource(const string& path, const string& filename)
{
	char szAppPath[MAX_PATH] = "";
	char szAppDirectory[MAX_PATH]= "";

	if (!GetModuleFileName(0, szAppPath, MAX_PATH - 1))
	{
		sfmlcubes::Logger::DEFAULT.logWarning("can't get our executable's filename");

		// Trying to locate the resource locally...
		return simpleLocateResource(path, filename);
	}

	strncpy(szAppDirectory, szAppPath, strrchr(szAppPath, '\\') - szAppPath);
	szAppDirectory[MAX_PATH - 1] = '\0';				// For sure...

	stringstream ss;
	ss << szAppDirectory << "/" << path << "/" << filename; 	// We are in Windows, but here we should use slash cause of objloader

	if (!FileExists(ss.str()))
	{
		{
			stringstream ss2;
			ss2 << "can't find " << ss.str();
			sfmlcubes::Logger::DEFAULT.logInfo(ss2.str());
		}

		// Trying to locate the resource locally...
		return simpleLocateResource(path, filename);
	}

	return ss.str();
}

void WinLinMacApi::setMainWindowIcon(const sf::Window& win)
{
    // Loading our icon from the resource
	HINSTANCE handle = ::GetModuleHandle(NULL);
	HICON icon = ::LoadIcon(handle, "MainIcon");

	// Here we are assuming that we're in Windows, so sf::WindowHandle is HWND
	HWND hwnd = win.getSystemHandle();

	stringstream ss;
	ss << "module: " <<handle << ", icon: " << icon << ", hwnd: " << hwnd;
	sfmlcubes::Logger::DEFAULT.logInfo(ss.str());


	// Setting the icon for the window
	::SetClassLong(hwnd, GCL_HICON, (LONG) icon);
}

#endif
