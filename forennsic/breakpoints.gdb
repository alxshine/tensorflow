set print thread-events off

set breakpoint pending on
b EagerExecutor::SyncExecute(tensorflow::EagerNode*)

run ~/test.py
c 24
p node->DebugString()

b tensorflow/core/common_runtime/threadpool_device.cc:169
c

python
depth = lambda: len(gdb.execute('where', to_string=True).splitlines())

initial_depth = depth()
line_count = 0

print("Starting stepwise execution")

while depth() >= initial_depth:
  gdb.execute('si', to_string=True)
  line_count += 1
  if line_count % 10 == 0:
    print(line_count)

print("Function finished, line count:")
print(line_count)
end