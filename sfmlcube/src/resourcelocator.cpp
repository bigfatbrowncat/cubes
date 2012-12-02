#ifdef __APPLE__

#include </usr/include/sys/syslimits.h>
#include <sstream>
#include "CoreFoundation/CFBundle.h"
#include "resourcelocator.h"
#include "Logger.h"

CFBundleRef mainBundle;
char fileurl[PATH_MAX + 1];

bool initializeBundle()
{
	mainBundle = CFBundleGetMainBundle();
	if (mainBundle)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void finalizeBundle()
{
	CFRelease(mainBundle);
}

char* locateResource(const char* path, const char* filename)
{
	stringstream ss;
	ss << "locating resource " << filename << "; path: " << path;
	sfmlcubes::Logger::DEFAULT.logInfo(ss.str());

	CFStringRef cfFileName = CFStringCreateWithCString(NULL, filename, kCFStringEncodingASCII);
	CFStringRef cfPath = CFStringCreateWithCString(NULL, path, kCFStringEncodingASCII);

	CFURLRef resourceURL = CFBundleCopyResourceURL(mainBundle, cfFileName, NULL, cfPath);
	if (!resourceURL)
	{
		throw 1523;
	}

	CFRelease(cfFileName);
	CFRelease(cfPath);

	if (!CFURLGetFileSystemRepresentation(resourceURL, true, (UInt8*)fileurl, PATH_MAX))
	{
		throw 1524;
	}

	CFRelease(resourceURL);

	return fileurl;
}

#else

bool initializeBundle()
{
	// Do nothing
}

char* locateResource(const char* filename)
{
	return filename;
}

#endif
