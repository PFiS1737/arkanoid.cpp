---@diagnostic disable: param-type-mismatch

add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate", { outputdir = "build", lsp = "clangd" })

set_project("arkanoid.cpp")
set_version("1.0.0")
set_languages("c++23")

add_requires("allegro", { system = true })

target("arkanoid.cpp", function()
	set_kind("binary")
	set_toolchains("clang")

	add_files("src/**.cpp", "src/**.cppm", "configs.cppm")

	add_cxxflags("-Wall", "-Wextra", "-pedantic")

	add_packages("allegro")
end)
