BuildProject({
    projectName = "CreepEngine",
    projectType = "binary",
    debugEvent = function()
        add_defines("_DEBUG")
    end,
    releaseEvent = function()
        add_defines("NDEBUG")
    end,
    exception = true
})
add_defines("NOMINMAX", "UNICODE", "m128_f32=vector4_f32", "m128_u32=vector4_u32")
add_files("**.cpp")
add_includedirs("./","./assimp")
add_linkdirs("../dll")
add_syslinks("User32", "kernel32", "Gdi32", "Shell32", "DXGI", "D3D12", "D3DCompiler","assimp-vc143-mtd")
after_build(function(target)
    src_path = "shader/"
    os.cp(src_path .. "*", target:targetdir() .. "/shader/")
    os.cp("dll/" .. "*", target:targetdir() .. "/")
    os.cp("model/" .. "*", target:targetdir() .. "/model/")
end)