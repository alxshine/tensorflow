set print thread-events off

set breakpoint pending on
b EagerExecutor::SyncExecute(tensorflow::EagerNode*)

run ~/test.py
c 24
p node->DebugString()

b tensorflow/core/common_runtime/threadpool_device.cc:169
c