#include <stdexcept>
#include <iostream>
#include <filesystem>

#include "Application.h"
#include "Utils/Logger.hpp"

int main()
{
	{
		try
		{
			std::cout << "Current path is " << std::filesystem::current_path() << std::endl;
			Application app({800, 600, "Vulkan App"});
			app.run();
		}
		catch (const std::exception& e)
		{
			LOG_ERROR(e.what());
			std::cout << "App failed somehow...\n";
			return EXIT_FAILURE;
		}
	}
	LOG_SUCCESS("Succesfully closed application!");
	std::cout << "Press ENTER to close...";
	std::cin.get();
	return EXIT_SUCCESS;	
}