#include <cassert>
#include <cstdlib>
#include <iostream>
#include "include/config.hpp"
#include "include/logger.hpp"

using namespace pg_ai::config;

void test_env_vars_no_config() {
  std::cout << "Testing environment variables without config file..."
            << std::endl;

  // Ensure no config file is loaded by pointing to a non-existent file
  // The loadConfig logic will try to read this, fail, use defaults, and then
  // check env vars
  std::string non_existent_config = "definitely_does_not_exist.config";

  // Set environment variables
  setenv("OPENAI_API_KEY", "sk-test-openai-key-no-config", 1);
  setenv("ANTHROPIC_API_KEY", "sk-test-anthropic-key-no-config", 1);

  // Load config
  bool loaded = ConfigManager::loadConfig(non_existent_config);
  // Note: loadConfig returns true even if file fails but defaults/env works,
  // or it might return true because it "handled" the missing file by using
  // defaults. Let's check the actual values.

  // Check OpenAI key and auto-configured defaults
  auto openai_config = ConfigManager::getProviderConfig(Provider::OPENAI);
  assert(openai_config != nullptr);
  assert(openai_config->api_key == "sk-test-openai-key-no-config");
  assert(openai_config->default_model.name ==
         "gpt-4o");  // Check default model was set
  std::cout << "OpenAI API key and defaults loaded correctly from env."
            << std::endl;

  // Check Anthropic key and auto-configured defaults
  auto anthropic_config = ConfigManager::getProviderConfig(Provider::ANTHROPIC);
  assert(anthropic_config != nullptr);
  assert(anthropic_config->api_key == "sk-test-anthropic-key-no-config");
  assert(anthropic_config->default_model.name ==
         "claude-3-5-sonnet-20241022");  // Check default model was set
  std::cout << "Anthropic API key and defaults loaded correctly from env."
            << std::endl;

  // Clean up
  unsetenv("OPENAI_API_KEY");
  unsetenv("ANTHROPIC_API_KEY");
}

int main() {
  // Disable logging for clean output
  pg_ai::logger::Logger::setLoggingEnabled(false);

  test_env_vars_no_config();

  std::cout << "All tests passed!" << std::endl;
  return 0;
}
