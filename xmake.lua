add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate", {outputdir = ".vscode"})

set_project("NewNotepad")

if is_plat("windows") then
    set_languages("cxxlatest")

    -- bruh
    --add_defines("_WIN32_WINNT=0x0601")

    add_cxflags("/Zc:__cplusplus")
    add_cxflags("/Zc:preprocessor")

    add_cxflags("/permissive-")
    add_ldflags("/subsystem:windows")
    add_ldflags("user32.lib")
    add_ldflags("gdi32.lib")
else
    set_languages("cxx20")
end

add_requires("simpleini")

set_warnings("allextra")

if is_mode("debug") then
    add_defines("DEBUG")
end
if is_mode("release") then
    add_defines("NDEBUG")

    if is_plat("windows") then
        --add_cxflags("/favor:AMD64")
        --add_cxflags("/O2")
        --add_cxflags("/arch:AVX2")
        --add_cxflags("/fp:fast")
        --add_cxflags("/GL")
        --add_cxflags("/Qfast_transcendentals")
        --add_cxflags("/Qpar")
    else
    end
end

target("NewNotepad")
    set_kind("binary")

    add_packages("simpleini")

    add_includedirs("include")

    add_headerfiles("include/**.hpp")

    add_files("src/**.cpp")

    after_build(function (target)
        import("core.project.config")
        os.cp(path.join("config", "*"), path.join(config.buildir(), config.plat(), config.arch(), config.mode()))
    end)
    after_install(function (target)
        import("core.project.config")
        os.cp(path.join("config", "*"), target.installdir())
    end)
