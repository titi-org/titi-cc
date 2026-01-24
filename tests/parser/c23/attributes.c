// Test C23 attributes [[ ]]

// nodiscard attribute
[[nodiscard]] int must_check() {
  return 42;
}

// deprecated attribute
[[deprecated]] int old_function() {
  return 0;
}

// maybe_unused attribute
[[maybe_unused]] static int unused_var = 10;

// noreturn attribute
[[noreturn]] void abort_program() {
  while (1)
    ;
}

// Multiple attributes
[[nodiscard, deprecated("use new_api instead")]] int legacy_api() {
  return -1;
}

// Scoped attribute (gnu::pure - not using const as it's a keyword)
[[gnu::pure]] int pure_function(int x) {
  return x * 2;
}
