#include <stdexcept>
#include <iostream>

#include "Application.h"
#include "Utils/logger.hpp"

int main()
{
	try
	{
		Application app;
		app.run();
	}
	catch (const std::exception& e)
	{
		LOG_ERROR(e.what());
		return EXIT_FAILURE;
	}

	LOG_SUCCESS("Succesfully closed application!");
	return EXIT_SUCCESS;
}