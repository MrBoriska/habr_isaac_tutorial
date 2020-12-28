load("//engine/build:isaac.bzl", "isaac_app", "isaac_cc_module")
#load("//bzl:module.bzl", "isaac_app", "isaac_cc_module")

isaac_cc_module(
    name = "myapp_components",
    srcs = [
        "MyPingPong.cpp",
    ],
    hdrs = [
        "MyPingPong.hpp",
    ],
    visibility = ["//visibility:public"],
    deps = [],
)

isaac_app(
    name = "myapp",
    modules = [
        "//packages/myapp:myapp_components",
        "sight"
    ],
)