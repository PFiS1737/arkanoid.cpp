---@diagnostic disable: param-type-mismatch

add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate", { outputdir = "build", lsp = "clangd" })

set_policy("build.always_update_configfiles", true)
set_policy("run.autobuild", true)

set_project("arkanoid.cpp")
set_version("1.0.0")
set_languages("c++20")

add_requires("allegro", { system = true })

target("arkanoid.cpp", function()
	set_kind("binary")

	add_files("src/**.cpp")
	add_headerfiles("src/**.hpp")

	add_cxxflags("-Wall", "-Wextra", "-pedantic")

	add_packages("allegro")
end)
