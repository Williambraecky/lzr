load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "dac",
    srcs=[
        "dac.cpp",
        "dac.hpp",
        "etherdream.cpp",
        "etherdream.hpp",
    ],
    deps=[
        "//liblzr/core",
        "//vendored/libetherdream:etherdream",
    ],
    visibility = ["//visibility:public"],
)