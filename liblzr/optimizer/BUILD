load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "etherdream",
    srcs=[
        "optimizer.cpp",
        "optimizer.hpp",
        "optimizer_compile_paths.cpp",
        "optimizer_find_paths.cpp",
        "optimizer_path.cpp",
        "optimizer_reorder_paths.cpp",
    ],
    deps = [
        "//liblzr/core",
    ],
    visibility = ["//visibility:public"],
)