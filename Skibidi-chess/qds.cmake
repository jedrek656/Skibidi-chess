### This file is automatically generated by Qt Design Studio.
### Do not change

add_subdirectory(Skibidi)
add_subdirectory(SkibidiContent)
add_subdirectory(App)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
	Skibidiplugin
	SkibidiContentplugin)