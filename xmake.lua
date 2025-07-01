add_rules("mode.debug", "mode.release")

set_project("arkanoid.cpp")
set_version("1.0.0")
set_languages("c++23")

add_requires("allegro", { system = true })

target("arkanoid.cpp", function()
	set_kind("binary")
	set_toolchains("clang")

	add_files("src/**.cpp", "src/**.cppm", "configs.cppm")

	add_cxxflags("-Wall", "-Wextra", "-pedantic")

	if is_mode("debug") then
		add_cxxflags("-g")
		add_defines("DEBUG")
	else
		add_cxxflags("-O3")
	end

	add_packages("allegro")
end)
