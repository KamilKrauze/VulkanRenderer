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
	std::cout << "Press ENTER to close...";
	std::cin.get();
	return EXIT_SUCCESS;
}