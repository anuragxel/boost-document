#include "Document.hpp"
#include "Document.cpp"

SAL_IMPLEMENT_MAIN_WITH_ARGS(argc, argv)
{
	boost::filesystem::path pth(argv[1]);
	open(pth);
}