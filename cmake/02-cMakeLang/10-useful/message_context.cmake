cmake_minimum_required(VERSION 3.26)

function(foo)
  list(APPEND CMAKE_MESSAGE_CONTEXT "foo")
  message("foo message")
endfunction()

list(APPEND CMAKE_MESSAGE_CONTEXT "top")

message("Before `foo`")
foo()
message("After `foo`")
