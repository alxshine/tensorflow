#!/bin/bash

bazel build --config=dbg --per_file_copt=+tensorflow/core/common_runtime/eager/execute.cc@-g --local_ram_resources=2048 //tensorflow/tools/pip_package:build_pip_package