#ifndef COMMON_H
#define COMMON_H

#define EnableSmartPointer
#ifdef EnableSmartPointer
	#include <memory>
	#define DECLARE_POINTER_OF(CLASS) typedef std::shared_ptr<CLASS> CLASS##Ptr;
	#define DECLARE_WEAK_POINTER_OF(CLASS) typedef std::weak_ptr<CLASS> CLASS##WeakPtr;
	#define IS_AVAILABLE_WEAK_POINTER(Ptr) (!Ptr.expired())
	#define ENABLE_THIS_OF(CLASS) public std::enable_shared_from_this<CLASS>
	#define THIS shared_from_this()
	#define THIS_OF(CLASS) dynamic_pointer_cast<CLASS>(shared_from_this())
#else
	#define DECLARE_POINTER_OF(CLASS) typedef CLASS* CLASS##Ptr;
	#define DECLARE_WEAK_POINTER_OF(CLASS) typedef CLASS* CLASS##WeakPtr;
	#define IS_AVAILABLE_WEAK_POINTER(Ptr) (Ptr)
	class NULLCLASS{};
	#define	ENABLE_THIS_OF(CLASS) NULLCLASS
	#define THIS this
	#define THIS_OF(CLASS) this
#endif

#define DEF_MAKEFUN_OF(CLASS) static CLASS##Ptr Make##CLASS() { return CLASS##Ptr(new CLASS()); }

#define Assert(CONDITION)\
	if (!CONDITION)\
	{\
		printf("assert(%s) fail at file %s line %d\n",#CONDITION,__FILE__,__LINE__);\
		getchar();\
		exit(-1);\
	}

#define LOG(...)\
	printf("[LOG] ");\
	printf(__VA_ARGS__);\
	printf("\n");
#define WARNING(...)\
	printf("[WARNING] ");\
	printf(__VA_ARGS__);\
	printf("\n");
#define ERR(...)\
	printf("[ERR] ");\
	printf(__VA_ARGS__);\
	printf("\n");

#include <stdarg.h>
#include <string>
static std::string GenStr(char* format,...)
{
	va_list arg_ptr;
	va_start(arg_ptr,format);
	char buf[1024];
	vsprintf(buf,format,arg_ptr);
	return buf;
}

#include <stdio.h>
#include <string>
static std::string GetStrFromFile(std::string filename)
{
	FILE* fp;
	if (!(fp=fopen(filename.c_str(),"r")))
		return "";
	char buffer[10240];
	int i=0;
	do
		buffer[i]=fgetc(fp);
	while(buffer[i++]!=EOF);
	buffer[i-1]='\0';
	return buffer;
}
#endif